// Collaborated with Jadon Orr

#pragma once
#include <string>
#include "IntDList.hpp"
#include "IntDList_node.hpp"

using namespace std;

// creating exception class for when list is empty
class ListEmpty : public exception
{
public:
    const char *what() const noexcept override
    {
        return "List is empty!"; // error message
    }
};

// DLList class
class IntDLList
{
public:
    // init function
    IntDLList();        // constructor
    ~IntDLList();       // destructor
    bool empty() const; // checks if list is empty

    // add functions
    void addToHead(int e);     // add node to the head of list
    void insertInOrder(int e); // inserts the node in order
    void addToTail(int e);     // adds node to the end of list

    // delete functions
    int deleteFromHead();   // delete the head and return its value;
    int deleteFromTail();   // delete the tail and return its value;
    void deleteNode(int e); // deletes the node with value e

    // string functions
    bool isInList(int e) const; // checks to see if element is in list
    void printAll() const;      // prints all the elements in the list
    string addToString() const; // This method returns the string of the ordered integers
private:
    IntDLLNode *head;
    IntDLLNode *tail;
};