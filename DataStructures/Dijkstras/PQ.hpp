#include <vector>
#include "Edge.hpp"
#include <string>
#include <iostream>
#include "Map.hpp"
#include "Vertex.hpp"

using namespace std;

class PQ
{
public:
    PQ() { s = 0; };
    ~PQ() {};
    void printQ()
    {
        cout << "\tQ: ";
        for (auto &val : Q)
        {
            cout << "( " << val.first->label << " , " << val.second << " )\t";
        }
        cout << endl;
    };
    bool empty() { return (size() == 0) ? true : false; };
    int const size() { return s; };
    Map<Vertex *, unsigned long> const min() { return Q[0]; };
    int const deQ()
    {
        Q.erase(Q.begin());
        s--;
        return 0;
    };
    int const enQ(Map<Vertex *, unsigned long> const &m)
    {
        for (auto it = Q.begin(); it != Q.end(); ++it)
        {
            if (m.second < it->second)
            {
                Q.insert(it, m); // insert before the first larger element
                return 0;
            }
        }
        Q.push_back(m); // if m.first is larger than all existing elements
        s++;
        return 0;
    }

private:
    vector<Map<Vertex *, unsigned long>> Q;
    int s;
};
