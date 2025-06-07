#include "Node.hpp"
class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    bool empty() const;
    void insertFront(const int &e);
    void insertBack(const int &e);
    void deleteFront();
    void deleteBack();
    Node *begin() const;
    Node *end() const;
    friend class VectorLL;

private:
    Node *head;
};

LinkedList::LinkedList()
{
    head = nullptr;
}
LinkedList::~LinkedList()
{
    while (!empty())
    {
        deleteFront();
    }
    delete head;
}
bool LinkedList::empty() const
{
    return head == nullptr;
}
void LinkedList::insertFront(const int &e)
{
    Node *newNode = new Node;
    newNode->next = head;
    newNode->data = e;
    head = newNode;
};
void LinkedList::deleteFront()
{
    Node *temp = head;
    head = head->next;
    delete temp;
}
void LinkedList::insertBack(const int &e)
{
    // check is list is empty
    if (empty())
        insertFront(e);
    Node *newNode = new Node;
    newNode->data = e;
    Node *cur = head;
    for (; cur->next != nullptr; cur = cur->next)
        ;
    cur->next = newNode;
    newNode->next = nullptr;
}
void LinkedList::deleteBack()
{
    Node *cur = head;
    for (; cur->next->next != nullptr; cur = cur->next)
        ;
    Node *temp = cur->next->next;
    cur->next = nullptr;
    delete temp;
}
Node *LinkedList::begin() const
{
    return head;
}
Node *LinkedList::end() const
{
    return nullptr;
}

// Vector Class
class VectorLL
{
public:
    VectorLL();
    ~VectorLL();
    Node *begin() const;
    Node *end() const;
    class Iterator
    {
    public:
        int &operator*();
        bool operator==(Iterator &p);
        bool operator!=(Iterator &p);
        Iterator &operator++();
        Iterator &operator--();
        friend class VectorLL;

    private:
        Node *v;
        Iterator(Node *u);
        LinkedList L;
    };

private:
};
VectorLL::VectorLL()
{
    LinkedList L;
};