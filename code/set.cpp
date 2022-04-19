#include "set.h"
#include "node.h"

int Set::Node::count_nodes = 0;  // initialize total number of existing nodes to zero

/*****************************************************
 * Implementation of the member functions             *
 ******************************************************/

// Used for debug purposes -- static member function
// Return number of existing nodes
int Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

// Default constructor, O(1) (assigning 0 to the data member)
Set::Set() : head{ new Node() }, tail{ new Node(0,nullptr,head) }, counter{ 0 } { head->next = tail; }

// Conversion constructor, insert at head, O(1)
Set::Set(int n) : Set{} // call default constructor 
{
    insert_node(head,n);
}

// Constructor to create a Set from a sorted vector v, //O(n)
Set::Set(const std::vector<int>& v) : Set{} { 
	//insert all elements of v into the set, backwards

	for(auto i = v.rbegin(); i != v.rend(); ++i) {
		insert_node(head,*i);
	}
	
}

// Make the set empty, O(n)
void Set::make_empty() {
    Node* p = head->next;

	//the loop is O(n)
    while (p->next) {
        Node* pNext = p->next;
		//remove function is O(1)
        remove_node(p);
        p = pNext;
    }
}

// Destructor
Set::~Set() {
	// O(n) , see above. 
    make_empty();
	delete head; //deallocate, O(1)
	delete tail; //deallocate, O(1)
    head = nullptr;
	tail = nullptr;
}

// Copy constructor, O(n)
Set::Set(const Set& source) : Set{} {  // create an empty list
    Node* temp = source.head->next;
    Node* p = head;
    
	//copy all values from source, forwards
	while (temp != source.tail) {
		insert_node(p,temp->value);
		temp = temp->next;
        p = p->next;
	}
}


// Copy-and-swap assignment operator
Set& Set::operator=(Set source) {
	
	// O(1)
	if (this == &source) {
		return *this;
	}
    std::swap(head, source.head); // swap the head pointers, O(1)
	std::swap(tail, source.tail); // swap the tail pointers, O(1)
	std::swap(counter, source.counter); // swap the counter, O(1)

    return *this;
}

// Test set membership
bool Set::is_member(int val) const {
	// worst case: O(n)
	// best case: O(1)
	// space : O(1)
    Node* temp = head->next;
	while (temp != tail) {
		if (temp->value == val) {
			return true;
		}
		temp = temp->next;
	
	}
    return false;  // remove this line
}

// Test whether a set is empty
bool Set::is_empty() const {
    return (counter == 0);
}

// Return number of elements in the set
size_t Set::cardinality() const {
    return counter;
}

// Return true, if the set is a subset of b, otherwise false
// a <= b iff every member of a is a member of b
bool Set::less_than(const Set& b) const {
    //best case O(1)
    //worst case O(n)
	//space O(1)

	Node* S1 = head->next;
	Node* S2 = b.head->next;

	while (S1 != tail && S2 != b.tail) {
		if (S1->value < S2->value) {
			return  false;
		}

		if (S1->value > S2->value) {
			S2 = S2->next;
		}
		else {
			S1 = S1->next;
			S2 = S2->next;
		}
	}

	return S1 == tail;
}

// Modify *this such that it becomes the union of *this with Set S
// Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S) {
    // Best case: O(1)
    // Worst case: O(n) 
	// Space: O(n)

    Node* thisPtr = head;
    Node* sPtr = S.head->next;

	while (sPtr != S.tail) {
		
		if(sPtr->value < thisPtr -> next -> value || thisPtr ->next == tail) {
			
			insert_node(thisPtr, sPtr->value);
			sPtr = sPtr->next;
			
		} else if (sPtr->value == thisPtr->next->value) {
			
			sPtr = sPtr->next;
		} else {
		
		thisPtr = thisPtr->next;
		}
	} 
	
	return *this;
	
}

// Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S) {
    // intersection is  {1,2,3} (lhs) * {2,3,4} (rhs) results {2,3}
    // S1 *= S2 gives S1 = S1 * S2
	// Best case time complexity: O(1)
	// Worst case time complexity: O(n+m)
	// Space complexity: O(1)

	Node* S1 = head;
	Node* S2 = S.head;
	
	while (S1->next != tail && S2->next != S.tail) { // O(S1+S2)
		if (S1->next->value == S2->next->value ) {
			S1 = S1->next;
			S2 = S2->next;
			
		} else if (S1->next->value < S2->next->value) {   // if S1 < S2, remove the value from S1.
			remove_node(S1->next);
			S1 = S1->next; // advance the smaller set.
			
		} else {
			remove_node(S1->next); // if S1 > S2, remove the value from S1.
			S2 = S2->next; // advance the smaller set.
			
		}
	}
    return *this;
}

// Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S) {
	// Best case: O(1)
	// Worst case: O(m+n)
	// Space complexity: O(1)
	
    Node* S1 = head;
    Node* S2 = S.head;
	
	while (S1 -> next != tail && S2->next != S.tail) { // O(S1+S2)
		
        if (S1->next->value < S2->next->value) { // if S1 < S2, value does not exist in S1.
			S1 = S1->next;
			
		} else if (S1->next->value == S2->next->value) { // if S1 == S2, remove the value from S1.
			remove_node(S1->next);
			
		} else {
			S2 = S2->next; // if S1 > S2, value does not exist in S2.
        }
	}
	return *this;
}

/* ******************************************** *
 * Private Member Functions -- Implementation   *
 * ******************************************** */

// If you add any private member functions to class Set then write the implementation here


void Set::write_to_stream(std::ostream& os) const {
    if (is_empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* temp{head->next};

        os << "{ ";
        while (temp != tail) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
}


// Insert a new Node storing val after the Node pointed by p
void Set::insert_node(Node* p, int val) {

    Node* newNode = new Node(val, p->next, p);
    p->next = newNode;
    ++counter;
}


// Remove the Node pointed by p
void Set::remove_node(Node* p) {

    if (is_empty()) {
		return;
	}
	
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	--counter;
}
