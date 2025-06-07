#include "GraphBase.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Edge::Edge(const string &x, const string &y, const unsigned long &z)
{
    start = x;
    end = y;
    distance = z;
}

void Edge::printEdge()
{
    cout << "(" << this->start << ", " << this->end << ", " << this->distance << ")";
}