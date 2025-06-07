#include "Graph.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    //---TEST CASE 1
    Graph G;
    cout << "\n\nTEST CASE 1:\n"
         << endl;
    // adding 5 vertex: 1 - 6
    for (int i = 1; i < 7; i++)
    {
        G.addVertex(to_string(i));
    }
    // adding edges to the vertex
    G.addEdge("1", "2", 7);
    G.addEdge("1", "3", 9);
    G.addEdge("1", "6", 14);
    G.addEdge("2", "3", 10);
    G.addEdge("2", "4", 15);
    G.addEdge("3", "4", 11);
    G.addEdge("3", "6", 2);
    G.addEdge("4", "5", 6);
    G.addEdge("5", "6", 9);

    G.printGraph();
    cout << endl;

    cout << "Basic Test Run" << endl;
    vector<string> p;
    cout << "Shortest Path Length: " << G.shortestPath("1", "5", p) << endl;
    cout << "Shortest Path: ";
    for (auto &val : p)
    {
        cout << val << " ";
    }

    cout << "\n\nRemoving Vertex 3" << endl;
    G.removeVertex("3");
    G.printGraph();

    cout << "Shortest Path Length: " << G.shortestPath("1", "5", p) << endl;
    cout << "Shortest Path: ";
    for (auto &val : p)
    {
        cout << val << " ";
    }

    cout << "\n\nRemoving Edge ('5', '6', 9)" << endl;
    G.removeEdge("5", "6");
    G.printGraph();

    cout << "Shortest Path Length: " << G.shortestPath("1", "5", p) << endl;
    cout << "Shortest Path: ";
    for (auto &val : p)
    {
        cout << val << " ";
    }

    //---TEST CASE 2
    cout << "\n\n----------------------------\n\nTEST CASE 2:\n"
         << endl;
    Graph G2;
    // adding vertices
    G2.addVertex("BSN");
    G2.addVertex("LIB");
    G2.addVertex("ENB");
    G2.addVertex("MSC");
    G2.addVertex("CAS");
    G2.addVertex("SUB");
    G2.addVertex("SUN");
    // adding edges
    G2.addEdge("BSN", "LIB", 871);
    G2.addEdge("BSN", "CAS", 1672);
    G2.addEdge("BSN", "MSC", 2355);
    G2.addEdge("SUN", "SUB", 1265);
    G2.addEdge("LIB", "MSC", 1615);
    G2.addEdge("LIB", "SUN", 1847);
    G2.addEdge("ENB", "SUN", 2885);
    G2.addEdge("ENB", "CAS", 454);
    G2.addEdge("ENB", "LIB", 1078);

    G2.printGraph();

    // shortest Paths
    vector<string> p2;
    cout << "Shortest Path Length: " << G2.shortestPath("ENB", "SUN", p2) << endl;
    cout << "Shortest Path: ";
    for (auto &val : p2)
    {
        cout << val << " ";
    }
    cout << "\n"
         << endl;

    //---TEST CASE 3
    cout << "----------------------------\n\nTEST CASE 3:\n"
         << endl;
    // shortest Paths
    vector<string> p3;
    cout << "Shortest Path Length: " << G2.shortestPath("LIB", "CAS", p3) << endl;
    cout << "Shortest Path: ";
    for (auto &val : p3)
    {
        cout << val << " ";
    }
    cout << "\n"
         << endl;

    return 0;
}