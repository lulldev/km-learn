#include <iostream>
#include "Graph/CGraph.h"

using namespace std;

int main()
{
    // Create a graph given in the above diagram
    CGraph graph(4);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 2);
    graph.AddEdge(2, 0);
    graph.AddEdge(2, 3);
    graph.AddEdge(3, 3);

    if(graph.IsGraphHaveCycle())
    {
        cout << "Graph contains cycle";
    }
    else
    {
        cout << "Graph doesn't contain cycle";
    }

    return 0;
}
