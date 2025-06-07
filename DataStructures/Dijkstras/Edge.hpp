#pragma once
#include <string>

// This is the edge class, it wil contain the edge list struct
//   Node 1
//   Node 2
//  Distance between them
using namespace std;

class Edge
{
public:
    Edge(const string &x, const string &y, const unsigned long &z);
    void printEdge();
    string start;
    string end;
    unsigned long distance;
};