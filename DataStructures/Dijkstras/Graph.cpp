#include "GraphBase.hpp"
#include "Graph.hpp"
#include <vector>
#include <string>
#include "Edge.hpp"
#include "Vertex.hpp"
#include "Map.hpp"
#include <iostream>

// Look up Vertex* by label
Vertex *Graph::getVertex(const string &label)
{
    for (auto &v : V_list)
        if (v.label == label)
            return &v;
    return nullptr;
}

void Graph::addVertex(std::string label)
{
    // will check to make sure that you cannot add duplicate vertex
    for (const Vertex &v : V_list)
        if (v.label == label)
            return;
    // adds vertex to the V_list
    V_list.push_back(Vertex(label));
};

void Graph::removeVertex(std::string label)
{
    // remove from v_list
    for (auto v = V_list.begin(); v != V_list.end();)
    {
        if (v->label == label)
        {
            v = V_list.erase(v); // erase returns the next valid iterator
        }
        else
        {
            ++v;
        }
    }
    // remove from all edge lists
    // A simplier way to do this would be to use the label.edgeList to create a list of all the connecting edges and then only check those edges
    for (Vertex &v : V_list)
    {
        for (auto e = v.EdgeList.begin(); e != v.EdgeList.end();)
        {
            if (e->start == label || e->end == label)
            {
                e = v.EdgeList.erase(e); // erase returns the next valid iterator
            }
            else
            {
                ++e;
            }
        }
    }
};

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
    if (label1 == label2)
        return;

    Vertex *v1 = nullptr;
    Vertex *v2 = nullptr;

    // Find the two vertices
    for (auto &v : V_list)
    {
        if (v.label == label1)
            v1 = &v;
        else if (v.label == label2)
            v2 = &v;
    }

    // Ensure both vertices exist
    if (!v1 || !v2)
        return;

    // Check if edge already exists
    for (const auto &e : v1->EdgeList)
    {
        if ((e.start == label1 && e.end == label2) || (e.start == label2 && e.end == label1))
            return;
    }

    // Add edge to both vertices
    v1->EdgeList.push_back(Edge(label1, label2, weight));
    v2->EdgeList.push_back(Edge(label2, label1, weight));
}

void Graph::removeEdge(std::string label1, std::string label2)
{
    for (Vertex &v : V_list)
    {
        if (v.label == label1 || v.label == label2)
        {
            for (auto e = v.EdgeList.begin(); e != v.EdgeList.end();)
            {
                if ((e->start == label1 && e->end == label2) || (e->start == label2 && e->end == label1))
                {
                    e = v.EdgeList.erase(e); // erase returns the next valid iterator
                }
                else
                {
                    ++e;
                }
            }
        }
    }
};

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path)
{
    //---ENSURING VERTICES EXIST---
    // ensuring edge cases
    if (startLabel == endLabel)
    {
        path.push_back(startLabel);
        return 0;
    }

    Vertex *start = nullptr;
    Vertex *end = nullptr;

    // Find the two vertices
    for (auto &v : V_list)
    {
        if (v.label == startLabel)
            start = &v;
        else if (v.label == endLabel)
            end = &v;
    }

    // Ensure both vertices exist
    if (!start || !end)
        return 0;

    //-----INITIALIZATION OF VECTORS----
    PQ Q;
    distance.clear(); // clearing the distance vector;
    parents.clear();  // clear distance vector
    vector<std::string> visited;
    // initialize the distance vector
    //  Init distances
    for (auto &v : V_list)
    {
        unsigned long dist = (v.label == startLabel) ? 0 : ULONG_MAX;
        distance.push_back(Map<string, unsigned long>(v.label, dist));
        if (v.label == startLabel)
        {
            Q.enQ(Map<Vertex *, unsigned long>(&v, 0));
            parents.push_back(Map<string, string>(v.label, "\0")); // no parent for start
        }
    }

    //-----MAIN LOOP OF CODE----
    while (!Q.empty())
    {
        auto node = Q.min();
        Q.deQ();

        Vertex *v = node.first;
        unsigned long dist = node.second;

        // Check if already visited
        bool alreadyVisited = false;
        for (const auto &label : visited)
        {
            if (label == v->label)
            {
                alreadyVisited = true;
                break;
            }
        }
        if (alreadyVisited)
            continue;
        visited.push_back(v->label);

        // create the distance metric
        for (auto &edge : v->EdgeList)
        {
            // check the total distance of the node against the distance in  distance vector
            string n = edge.end;
            unsigned long l = edge.distance;
            unsigned long total_dist = dist + l;

            // iterating through distance vector
            for (auto &d : distance)
            {
                // checking to see if entry at totalDist < Distance[Neighbor]
                if (d.first == n && total_dist < d.second)
                {
                    // updating Distance[Neighbor]
                    d.second = total_dist;
                    Q.enQ(Map<Vertex *, unsigned long>(getVertex(n), total_dist));

                    // Update or add parent
                    bool in_parents = false;
                    for (auto &p : parents)
                    {
                        if (p.first == n)
                        {
                            p.second = v->label;
                            in_parents = true;
                            break;
                        }
                    }
                    // if the node has not been added to parent vector already
                    if (!in_parents)
                    {
                        parents.push_back(Map<string, string>(n, v->label));
                    }
                }
            }
        }
    }

    //---RECONSTRUCT PATH---
    path.clear();
    string current = endLabel;
    while (current != "\0")
    {
        path.insert(path.begin(), current);
        bool found = false;
        for (auto &p : parents)
        {
            if (p.first == current)
            {
                current = p.second;
                found = true;
                break;
            }
        }
        if (!found)
            break; // no path
    }

    //---GET FINAL DISTANCE
    for (auto &d : distance)
    {
        if (d.first == endLabel)
            return d.second == ULONG_MAX ? 0 : d.second;
    }

    // incorrect path
    return 0;
};

void Graph::printGraph()
{
    cout << "Graph:" << endl;
    for (auto v : V_list)
    {
        v.printVertex();
    }
}

Graph::Graph()
{
    // constructor code
}

Graph::~Graph()
{
    // destructor code
}