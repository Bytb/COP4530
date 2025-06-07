#pragma once

class Node
{
private:
    Node *next;
    int data;
    friend class Iterator;
    friend class VectorLL;
    friend class LinkedList;
};