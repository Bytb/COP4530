// an iterator allows you to move between positions in a ADT
// so basically you have to define a bunch of operators
#include "Node.hpp"

class NodeList
{ // node-based list
public:
    NodeList(); // default constructor
    ~NodeList();
    int size() const;   // return n
    bool empty() const; // if n == 0 return true

    // ITERATOR CLASS
    class Iterator
    { // an iterator for the list
    public:
        int &operator*();                         // reference to the intent
        bool operator==(const Iterator &p) const; // compare positions
        bool operator!=(const Iterator &p) const;
        Iterator &operator++(); // move to next position
        Iterator &operator--(); // move to previous position
        friend class NodeList;  // give NodeList access
    private:
        Node *v;           // pointer to the node
        Iterator(Node *u); // private constractor create from node
    };

    Iterator begin() const;         // beginning position
    Iterator end() const;           // (just beyond) last position
    void insertFront(const int &e); // insert at front
    void insertBack(const int &e);  // insert at rear
    // insert e before p
    void insert(const Iterator &p, const int &e);
    void eraseFront();             // remove first
    void eraseBack();              // remove last
    void erase(const Iterator &p); // remove p
private:                           // data members
    int n;                         // number of items
    Node *header;                  // head-of-list sentinel
    Node *trailer;                 // tail-of-list sentinel
};

/*
    NODE LIST FUNCTIONS
*/
// constructor
NodeList::NodeList()
{
    n = 0;             // initially empty
    header = new Node; // create sentinels
    trailer = new Node;
    header->next = trailer; // have them point to each other
    trailer->prev = header;
}
NodeList::~NodeList()
{
    while (!empty())
        eraseFront();
    delete header;
    delete trailer;
}
int NodeList::size() const { return n; }
bool NodeList::empty() const
{
    return (n == 0);
}
// begin position is first item
NodeList::Iterator NodeList::begin()
    const
{
    return Iterator(header->next);
}
// end position is just beyond last
NodeList::Iterator NodeList::end() const
{
    return Iterator(trailer);
}
// insert e before p
void NodeList::insert(const NodeList::Iterator &p, const int &e)
{
    Node *w = p.v;      // p's node
    Node *u = w->prev;  // p's predecessor
    Node *v = new Node; // new node to insert
    v->elem = e;
    v->next = w;
    w->prev = v; // link in v before w
    v->prev = u;
    u->next = v; // link in v after u
    n++;
}
// insert at front
void NodeList::insertFront(const int &e)
{
    insert(begin(), e);
}
// insert at rear
void NodeList::insertBack(const int &e)
{
    insert(end(), e);
}
// remove p
void NodeList::erase(const Iterator &p)
{
    Node *v = p.v;     // node to remove
    Node *w = v->next; // successor
    Node *u = v->prev; // predecessor
    u->next = w;
    w->prev = u; // unlink p
    delete v;    // delete this node
    n--;         // one fewer element
}
// remove first
void NodeList::eraseFront()
{
    erase(begin());
}
// remove last
void NodeList::eraseBack()
{
    erase(--end());
}

/*
    ITERATOR FUNCTION DEFINITIONS
*/
// constructor from Node*
NodeList::Iterator::Iterator(Node *u) { v = u; }
// reference to the element
int &NodeList::Iterator::operator*() { return v->elem; }
// compare positions
bool NodeList::Iterator::operator==(const Iterator &p) const
{
    return v == p.v;
}
bool NodeList::Iterator::operator!=(const Iterator &p) const
{
    return v != p.v;
}
// move to next position
NodeList::Iterator &NodeList::Iterator::operator++()
{
    v = v->next;
    return *this;
}
// move to previous position
NodeList::Iterator &NodeList::Iterator::operator--()
{
    v = v->prev;
    return *this;
}

/*
        MAIN FUNCTION
*/
int main()
{
    return 0;
}