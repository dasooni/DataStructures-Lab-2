#pragma once

#include <iostream>
#include <vector>

/** Class to represent a Set of ints
 *
 * Set is implemented as a sorted doubly linked list
 * Sets should not contain repetitions, i.e.
 * two ints with the same value cannot belong to a Set
 *
 * All Set operations must have a linear complexity, in the worst case
 */
class Set {

public:
    // Default constructor: create an empty Set
    // IMPLEMENT before Lab1 HA
    Set();

    // Conversion constructor: Convert val into a singleton {val}
    // IMPLEMENT before Lab1 HA
    Set(int val);

    /** Constructor to create a Set from a sorted vector of ints
     *
     * Create a Set with all ints in sorted vector v
     * \param v sorted vector of ints
     *
     */
    // IMPLEMENT before Lab1 HA
    Set(const std::vector<int>& v);

    /** Copy constructor
     *
     * Create a new Set as a copy of Set b
     * \param b Set to be copied
     * Function does not modify Set b in any way
     *
     */
    // IMPLEMENT before Lab1 HA
    Set(const Set& b);

    /** Transform the Set into an empty set
     *
     * Remove all nodes from the list, except the dummy nodes
     *
     */
    // IMPLEMENT before Lab1 HA
    void make_empty();

    /** Destructor
     *
     * Deallocate all memory (Nodes) allocated for the list
     *
     */
    // IMPLEMENT before Lab1 HA
    ~Set();

    /** Assignment operator
     *
     * Assigns new contents to the Set, replacing its current content
     * \param source Set to be copied into Set *this
     * Call by valued is used. Thus, this function works also as move assignment operator
     *
     */
    // IMPLEMENT before Lab1 HA
    Set& operator=(Set source);

    /** Test whether val belongs to the Set
     *
     * This function does not modify the Set in any way
     * Return true if val belongs to the set, otherwise false
     *
     */
    // IMPLEMENT before Lab1 HA
    bool is_member(int val) const;

    /** Test whether the Set is empty
     *
     * This function does not modify the Set in any way
     * Return true if the set is empty, otherwise false
     *
     */
    bool is_empty() const;

    /** Count the number of values stored in the Set
     *
     * This function does not modify the Set in any way
     * Return number of elements in the set
     *
     */
    size_t cardinality() const;

    /** Modify Set *this such that it becomes the union of *this with Set S
     *
     * Set *this is modified and then returned
     *
     */
    // IMPLEMENT
    Set& operator+=(const Set& S);

    /** Modify Set *this such that it becomes the intersection of *this with Set S
     *
     * Set *this is modified and then returned
     *
     */
    // IMPLEMENT
    Set& operator*=(const Set& S);

    /** Modify Set *this such that it becomes the Set difference between Set *this and Set S
     *
     * Set *this is modified and then returned
     *
     */
    // IMPLEMENT
    Set& operator-=(const Set& S);

    /** Return number of existing nodes
     *
     * Used for debug purposes
     */
    static int get_count_nodes();

private:
    class Node;  // nested class defined in node.h

    Node* head;      // Pointer to the dummy header Node
    Node* tail;      // Pointer to the dummy tail Node
    size_t counter;  // number of values in the Set

    /* ************************** *
     * Private Member Functions    *
     * **************************  */

    /** Insert a new Node storing val after the Node pointed by p
     *
     * \param p pointer to a Node
     * \param val value to be inserted  after position p
     * Return *this
     *
     */
    // IMPLEMENT before Lab1 HA
    void insert_node(Node* p, int val);

    /** Remove the Node pointed by p
     *
     * \param p pointer to a Node
     * Return *this
     *
     */
    // IMPLEMENT before Lab1 HA
    void remove_node(Node* p);

    // Return true, if the set *this a subset of b, otherwise false
    // IMPLEMENT
    bool less_than(const Set& b) const;

    // Write set *this to stream os
    void write_to_stream(std::ostream& os) const;

    /* **************************** *
     * Overloaded operators         *
     * ***************************** */

    /** Overloaded operator<<
     *
     * \param os ostream object where the set b elements are written
     *
     */
    friend std::ostream& operator<<(std::ostream& os, const Set& b) {
        b.write_to_stream(os);
        return os;
    }

    /** Test whether Set S1 is a subset of Set S2
     *
     * S1 <= S2 iff every member of S1 is a member of S2
     * Return true, if S1 is a subset of S2, otherwise false
     *
     */
    friend bool operator<=(const Set& S1, const Set& S2) {
        return S1.less_than(S2);
    }

    /** Test whether Set S1 and S2 represent the same set
     *
     * S1 == S2, iff S1 <= S2 and S2 <= S1
     * Return true, if S1 stores the same elements as S2, otherwise false
     *
     */
    friend bool operator==(const Set& S1, const Set& S2) {
        // IMPLEMENT
        return (S1 <= S2 && S2 <= S1);
    }

    /** Test whether Set S1 and S2 represent different sets
     *
     * S1 != S2, iff (S1 == S2) is false
     * Return true, if S1 stores the same elements as Set S2, otherwise false
     *
     */
    friend bool operator!=(const Set& S1, const Set& S2) {
        return !(S1 <= S2 && S2 <= S1);
    }

    /** Test whether Set S1 is a strict subset of Set S2
     *
     * S1 < S2 iff S1 <= S2 but not S2 <= S1
     * Return true, if S1 is a strict subset of S2, otherwise false
     */
    friend bool operator<(const Set& S1, const Set& S2) {
        // IMPLEMENT

        return (S1 <= S2) && !(S2 <= S1);
    }

    /** Overloaded operator+: Set union S1+S2
     *
     * S1+S2 is the Set of elements in Set S1 or in Set S2 (without repeated elements)
     * Return a new Set representing the union of S1 with S2, S1+S2
     *
     */
    friend Set operator+(Set S1, const Set& S2) {
        return (S1 += S2);
    }

    /** Overloaded operator*: Set intersection S1*S2
     *
     * S1*S2 is the Set of elements in both Sets S1 and set S2
     * Return a new Set representing the intersection of S1 with S2, S1*S2
     *
     */
    friend Set operator*(Set S1, const Set& S2) {
        return (S1 *= S2);
    }

    /** Overloaded operator-: Set difference S1-S2
     *
     * S1-S2 is the Set of elements in Set S1 that do not belong to Set S2
     * Return a new Set representing the set difference S1-S2
     *
     */
    friend Set operator-(Set S1, const Set& S2) {
        return (S1 -= S2);
    }
};