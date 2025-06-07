using namespace std;

template <typename E> // Base element type
class Position
{
private:
    Node<E> *v; // Assuming Node is also a templated class

public:
    Position(Node<E> *w);             // Constructor
    ~Position();                      // Destructor
    E &operator*();                   // Get element
    Position<E> parent() const;       // Get parent
    PositionList<E> children() const; // Get node's children (define PositionList)
    bool isRoot() const;              // Root node?
    bool isExternal() const;          // External node?
};

template <typename E>
class PositionList
{
private:
    vector << Position < E >> positions;

public:
    PositionList();
};

template <typename E> // base element type
class Tree
{
public:                             // public types
    class Position;                 // a node position
    class PositionList;             // a list of positions
    int size() const;               // number of nodes
    bool empty() const;             // is tree empty?
    Position root() const;          // get the root
    PositionList positions() const; // get positions of all nodes
};
