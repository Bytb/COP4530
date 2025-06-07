// Collaborated with Jadon Orr

#include <iostream>
#include <string>
#include "IntDList.hpp"
#include "IntDList_node.hpp"

using namespace std;

// DLList Functions
// Constructor
IntDLList::IntDLList()
{
    head = new IntDLLNode;
    tail = new IntDLLNode;
    head->next = tail;
    tail->prev = head;
}
// Destructor
IntDLList::~IntDLList()
{
    // will delete from the head of the list until it is empty
    while (!empty())
    {
        deleteFromHead();
    };
    delete head;
    delete tail;
}
// returns true if the next element after head is tail
bool IntDLList::empty() const
{
    return head->next == tail;
}

// add functions
void IntDLList::addToHead(int e)
{
    IntDLLNode *newNode = new IntDLLNode(e, head->next, head);
    head->next->prev = newNode;
    head->next = newNode;
}; // return its value
// insert node in order
void IntDLList::insertInOrder(int e)
{
    // will add to the head if list is empty
    if (empty())
    {
        addToHead(e);
    }
    else
    {
        IntDLLNode *cur = head->next;
        // iterates through list until cur is either tail or at the first element that is greater than e
        while (cur != tail && cur->info <= e)
            cur = cur->next;
        // adds element to tail is cur is at tail
        if (cur == tail)
            addToTail(e);
        else // if at first element greater than e
        {
            IntDLLNode *newNode = new IntDLLNode(e, cur, cur->prev);
            cur->prev->next = newNode;
            cur->prev = newNode;
        }
    };
};
// adds node to the tail of list
void IntDLList::addToTail(int e)
{
    IntDLLNode *newNode = new IntDLLNode(e, tail, tail->prev);
    tail->prev->next = newNode;
    tail->prev = newNode;
};

// delete functions
int IntDLList::deleteFromHead()
{
    // throws error if trying to delete node from an empty list
    if (empty())
        throw(ListEmpty());
    IntDLLNode *temp = head->next;
    int x = temp->info;
    head->next = temp->next;
    temp->next->prev = head;
    delete temp;
    return x; // returns the value of node deleted
}; // delete the head and return its value;
int IntDLList::deleteFromTail()
{
    // throws an error is trying to delete from an empty list
    if (empty())
        throw(ListEmpty());
    IntDLLNode *temp = tail->prev;
    int x = temp->info;
    tail->prev = temp->prev;
    temp->prev->next = tail;
    delete temp;
    return x; // returns value of deleted node
}; // delete the tail and return its value;
// deletes node with value e
void IntDLList::deleteNode(int e)
{
    // throws error if trying to delete from empty list
    if (empty())
        throw(ListEmpty());
    else
    {
        IntDLLNode *cur = head->next;
        // iterates until cur is at tail or at specified element
        while (cur != tail && cur->info != e)
        {
            cur = cur->next;
        };
        if (cur == tail)
            throw(ListEmpty()); // this is if trying to delete a node that is not in the list
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        delete cur;
    }
};

// string functions
bool IntDLList::isInList(int e) const
{
    // if list is empty then return false
    if (empty())
        return false;
    IntDLLNode *cur = head->next;
    // iterates until cur is tail or equal to the element
    while (cur != tail && cur->info != e)
    {
        cur = cur->next;
    };
    return cur != tail; // returns false is cur is the tail, else returns true
};
// prints all the elements of the list
void IntDLList::printAll() const
{
    // list is empty
    if (empty())
        throw(ListEmpty()); // thorws ListEmpty() if list is empty
    else
    {
        IntDLLNode *cur = head->next;
        while (cur != tail)
        {
            cout << cur->info; // prints the elements in the list
            cout << " ";
            cur = cur->next;
        }
    }
};
// adds all the elemnts together into one string variable
string IntDLList::addToString() const
{
    if (empty())
        throw(ListEmpty()); // throws the ListEmpty() exception if the list is empty
    else
    {
        string value = "";
        IntDLLNode *cur = head->next;
        // iterates until cur is tail
        while (cur != tail)
        {
            value += to_string(cur->info); // converts the data from int to string and concatenates it to the string output
            cur = cur->next;
        }
        return value; // returns the string
    }
}; // This method returns the string of the ordered integers