#include <iostream>
#include "Graph/CGraph.h"

using namespace std;

int main()
{
    // Create a graph given in the above diagram
    CGraph graph(4);
    graph.AddEdge(0, 1);
    graph.AddEdge(1, 1);

    graph.GetGraphCycleCount();

    return 0;
}
