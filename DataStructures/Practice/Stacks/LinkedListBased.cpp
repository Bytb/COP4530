#include <iostream>
using namespace std;

class ListEmpty : public exception
{
public:
    const char *what() const noexcept override
    {
        return "List is empty!";
    }
};

template <typename T>
class Node
{
public:
    Node(const T &e, Node *next)
    {
        this->data = e;
        this->next = next;
    }
    Node()
    {
        this->next = NULL;
    }

private:
    Node *next;
    T data;
    friend class SLinkedList;
};

template <typename T>
class SLinkedList
{
public:
    SLinkedList();
    ~SLinkedList();
    const T &pop();
    void push(const T &e);
    bool empty() const;
    const T &show_top() const;
    int size() const;

private:
    Node<T> *top;
    int n;
};

template <typename T>
SLinkedList<T>::SLinkedList()
{
    top = NULL;
    n = 0;
}

template <typename T>
const T &SLinkedList<T>::pop()
{
    if (empty())
        throw ListEmpty();
    else
    {
        Node *temp = top;
        T val = temp->data;
        top = top->next;
        delete temp;
        n--;
    }
    return val;
}

template <typename T>
void SLinkedList<T>::push(const T &e)
{
    Node *newNode = newNode(e, top->next);
    top = newNode;
    n++;
}
template <typename T>
bool SLinkedList<T>::empty() const
{
    return n == 0;
};

template <typename T>
const T &SLinkedList<T>::show_top() const
{
    if (empty())
        throw ListEmpty();
    else
        return top->data;
};

template <typename T>
int SLinkedList<T>::size() const
{
    return n;
};

int main()
{
    SLinkedList<int> stack = SLinkedList<int>();
    cout << stack.push(5) << endl;
    cout << stack.show_top() << endl;
    cout << stack.push(1) << endl;
    cout << stack.show_top() << endl;
    cout << stack.pop() << endl;
    cout << stack.show_top() << endl;
}