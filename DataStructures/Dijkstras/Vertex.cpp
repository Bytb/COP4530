#include "GraphBase.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Vertex::Vertex(const string &name)
{
    label = name;
}

void Vertex::printVertex()
{
    cout << this->label << ": { ";
    for (auto e : this->EdgeList)
    {
        e.printEdge();
        cout << " ";
    }
    cout << "}" << endl;
}