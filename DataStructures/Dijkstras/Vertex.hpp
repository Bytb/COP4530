#pragma once
#include <string>
#include <vector>
#include "Edge.hpp"

// This is the edge class, it wil contain the vertex list struct
//  Label
//  EdgeList
using namespace std;

class Vertex
{
public:
    Vertex(const string &name);
    void printVertex();

    string label;
    vector<Edge> EdgeList;
};