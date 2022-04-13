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

// Conversion constructor, O(1)
Set::Set(int n) : Set{} {  
	//insert n into the set, head?
    insert_node(head,n);
}

// Constructor to create a Set from a sorted vector v, //O(n)
Set::Set(const std::vector<int>& v) : Set{} { 
	//insert all elements of v into the set, backwards
	for (int i = v.size() - 1; i >= 0; i--) {
		insert_node(head,v[i]);
	}
}

// Make the set empty
void Set::make_empty() {
    Node* p = head->next;

    while (p->next) {
        Node* pNext = p->next;
        remove_node(p);
        p = pNext;
    }
}

// Destructor
Set::~Set() {
    make_empty();
	delete head;
	delete tail;
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
    
    std::swap(head, source.head);
	std::swap(tail, source.tail);
	std::swap(counter, source.counter);

    return *this;
}

// Test set membership
bool Set::is_member(int val) const {

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

    Node* rhs = head->next;

    while (rhs != tail) {
        if (!(b.is_member(rhs->value))) {
            return false;
        }
        rhs = rhs->next;

    }

    return true;  
}

// Modify *this such that it becomes the union of *this with Set S
// Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S) {
    // Best case: O(1)
    // Worst case: O(n) 

    Node* thisPtr = head;
    Node* sPtr = S.head->next;

	//while (thisPtr != tail && sPtr != S.tail) {
	//	if (thisPtr->value > sPtr->value) {
	//		insert_node(thisPtr, sPtr->value);
	//		sPtr = sPtr->next;
	//	} else if (thisPtr->value < sPtr->value) {
	//		thisPtr = thisPtr->next;
	//	} else {
	//		thisPtr = thisPtr->next;
	//		sPtr = sPtr->next;
	//	}
	//}

	//while (sPtr != S.tail) {
	//	insert_node(thisPtr, sPtr->value);
	//	sPtr = sPtr->next;
	//}

	//return *this;
	
	while (sPtr != S.tail) {
		
		if(sPtr->value < thisPtr -> next -> value || thisPtr ->next == tail) {
			
			insert_node(thisPtr, sPtr->value);
			sPtr = sPtr->next;
			
		} else if (sPtr->value == thisPtr->next->value) {
			
			sPtr = sPtr->next;
		} 

		thisPtr = thisPtr->next;
		
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
	
	while (S1->next != tail && S2->next != S.tail) {
		if (S1->next->value == S2->next->value ) {
			S1 = S1->next;
			S2 = S2->next;
			
		} else if (S1->next->value < S2->next->value) {
			remove_node(S1->next);
			S1 = S1->next;
			
		} else {
			remove_node(S1->next);
			S2 = S2->next;
			
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
	
	while (S1 -> next != tail && S2->next != S.tail) {
		
        if (S1->next->value < S2->next->value) {
			S1 = S1->next;
			
		} else if (S1->next->value == S2->next->value) {
			remove_node(S1->next);
			
		} else {
			S2 = S2->next;
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
	
    if (p && p->next && p ->prev) {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        --counter;
    }
	
}
