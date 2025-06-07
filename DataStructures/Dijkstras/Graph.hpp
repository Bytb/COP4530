#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include <vector>
#include <string>
#include "Map.hpp"
#include "PQ.hpp"

using namespace std;

class Graph : public GraphBase
{
public:
    Graph();
    ~Graph();

    void addVertex(std::string label) override;
    void removeVertex(std::string label) override;
    void addEdge(std::string label1, std::string label2, unsigned long weight) override;
    void removeEdge(std::string label1, std::string label2) override;
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) override;
    void printGraph();
    Vertex *getVertex(const string &label);

    vector<Vertex> V_list;
    vector<Map<string, unsigned long>> distance; // this will conain elements that look like (Vertex, distance)
    vector<Map<string, string>> parents;         // this will contain (Vertex, Vertex)
};

#endif
