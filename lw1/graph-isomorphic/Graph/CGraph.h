#include <iostream>
#include <list>
#include <limits.h>

class CGraph
{
public:
    CGraph(int verticesCount); // Constructor
    void AddEdge(int v, int w); // to add an edge to graph
    bool IsGraphHaveCycle(); // returns true if there is a cycle in this graph

private:
    int verticesCount; // No. of vertices
    std::list<int> *adjacencyList; // Pointer to an array containing adjacency lists
    bool IsCyclicUtil(int v, bool visited[], bool *rs); // used by isCyclic()
};