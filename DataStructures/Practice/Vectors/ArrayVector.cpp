#include <iostream>

using namespace std;

// A array based vector will double the size of the vector if it goes out of bounds
class Vector
{
public:
    Vector(int cap);
    ~Vector();
    int &operator[](const int &i);
    int &at(const int &i);
    void set(const int &i, const int &e);
    void insert(const int &i, const int &e);
    int &erase(const int &i);
    void reserve(const int &size);

private:
    int *V; // the array
    int capacity;
    int n;
};

Vector::Vector(int cap)
{
    V = new int[cap];
    n = 0;
}

void Vector::reserve(const int &size)
{
    // make bigger array
    int *B = new int[size];

    // move elements from old array to new one
    for (int i = 0; i < capacity; i++)
    {
        B[i] = V[i];
    }

    // return new array
    capacity = size;
    delete V;
    V = B;
}

int &Vector::at(const int &i)
{
    if (i >= n)
        cout << "Range Bound" << endl;
    return V[i];
}

void Vector::insert(const int &i, const int &e)
{
    if (n + 1 == capacity)
        reserve(capacity * 2);
    for (int j = n - 1; j >= i; j--)
    {
        V[j + 1] = V[j];
    }
    V[i] = e;
}

int &Vector::erase(const int &i)
{
    // check to see if there is an element at i
    if (i >= n)
        cout << "out of range" << endl;
    for (int j = i; j < n; j++)
    {
        V[j] = V[j + 1];
    }
}