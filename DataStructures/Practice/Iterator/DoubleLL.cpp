#include "Node.hpp"
class DoubleLL
{
public:
    // Node Functions
    DoubleLL();
    ~DoubleLL();
    int size() const;
    bool &empty() const {};

    // Iterator
    class Iterator
    {
    public:
        // operations
        int &operator*();
        bool operator==(const Iterator &p) const;
        bool operator!=(const Iterator &p) const;
        Iterator &operator++();
        Iterator &operator--();
        friend class DoubleLL;

    private:
        Node *v;
        Iterator(Node *u);
    };
    // Iterator Functions

private:
    Node *header;  // tail
    Node *trailer; // head
    int n;         // size
};

// Iterator Constructor and Destructor
DoubleLL::Iterator::Iterator(Node *u)
{
    v = u;
}
int &DoubleLL::Iterator::operator*()
{
    return v->elem;
}
bool DoubleLL::Iterator::operator==(const Iterator &p) const
{
    return v == p.v;
}
bool DoubleLL::Iterator::operator!=(const Iterator &p) const
{
    return v != p.v;
}
DoubleLL::Iterator &DoubleLL::Iterator::operator++()
{
    v = v->next;
    return *this;
}
DoubleLL::Iterator &DoubleLL::Iterator::operator--()
{
    v = v->prev;
    return *this;
}

/*
    ITERATOR FUNCTION DEFINITIONS
*/
// constructor from Node*
DoubleLL::Iterator::Iterator(Node *u)
{
    v = u;
}
// reference to the element
int &DoubleLL::Iterator::operator*() { return v->elem; }
// compare positions
bool DoubleLL::Iterator::operator==(const Iterator &p) const
{
    return v == p.v;
}
bool DoubleLL::Iterator::operator!=(const Iterator &p) const
{
    return v != p.v;
}
// move to next position
DoubleLL::Iterator &DoubleLL::Iterator::operator++()
{
    v = v->next;
    return *this;
}
// move to previous position
DoubleLL::Iterator &DoubleLL::Iterator::operator--()
{
    v = v->prev;
    return *this;
}