#include <iostream>

class Node
{
private:
    int data;
    Node *next;
    friend class Queue;
};

class Queue
{
public:
    Queue();
    ~Queue();
    void enqueue(const int &e);
    int deque();
    int size() const;
    const int &front() const;
    void empty() const;

private:
    Node *front;
    Node *rear;
    int n;
};

Queue::Queue()
{
    front =
        rear =
            n = 0;
}