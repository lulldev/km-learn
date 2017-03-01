#include "CGraph.h"

using namespace std;

CGraph::CGraph(int verticesCount)
{
    this->verticesCount = verticesCount;
    adjacencyList = new list<int>[verticesCount];
}

void CGraph::AddEdge(int v, int w)
{
    adjacencyList[v].push_back(w); // Add w to v’s list.
}

// This function is a variation of DFSUytil() in http://www.geeksforgeeks.org/archives/18212
bool CGraph::IsCyclicUtil(int v, bool visited[], bool *recStack)
{
    if (visited[v] == false) {
        // Mark the current node as visited and part of recursion stack
        visited[v] = true;
        recStack[v] = true;

        // Recur for all the vertices adjacencyListacent to this vertex
        list<int>::iterator i;
        for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i)
        {
            if (!visited[*i] && IsCyclicUtil(*i, visited, recStack))
            {
                return true;
            }
            else if (recStack[*i])
            {
                return true;
            }
        }

    }
    recStack[v] = false; // remove the vertex from recursion stack
    return false;
}

// Returns true if the CGraph contains a cycle, else false.
// This function is a variation of DFS() in http://www.geeksforgeeks.org/archives/18212
bool CGraph::IsGraphHaveCycle()
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    bool *visited = new bool[verticesCount];
    bool *recStack = new bool[verticesCount];

    for (int i = 0; i < verticesCount; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }

    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for (int i = 0; i < verticesCount; i++)
    {
        if (IsCyclicUtil(i, visited, recStack))
        {
            return true;
        }
    }

    return false;
}