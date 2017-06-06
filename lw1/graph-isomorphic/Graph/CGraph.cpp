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

// This function is a variation of DFSUytil() in http://www.geeksforgeeks.org/archives/18212
bool CGraph::IsCyclicUtil2(int v, bool visited[], bool *recStack, int &cycleCount)
{
    if (visited[v] == false)
    {
        visited[v] = true;
        recStack[v] = true;

        list<int>::iterator i;
        for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i)
        {
            if (!visited[*i] && IsCyclicUtil2(*i, visited, recStack, cycleCount))
            {
                cycleCount++;
                return true;
            }
            else if (recStack[*i])
            {
                cycleCount++;
                return true;
            }
        }
        cout << cycleCount << endl;
        cycleCount = 0;
    }
    recStack[v] = false; // remove the vertex from recursion stack
    return false;
}
// Returns true if the CGraph contains a cycle, else false.
// This function is a variation of DFS() in http://www.geeksforgeeks.org/archives/18212
int CGraph::GetGraphCycleCount()
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
    int cycleCount = 0;

    for (int i = 0; i < verticesCount; i++)
    {
        cycleCount = 0;
        IsCyclicUtil2(i, visited, recStack, cycleCount);
//        if (IsCyclicUtil(i, visited, recStack))
//        {
//            cycleCount++;
//            return true;
//        }
    }

    return -1;
//    return false;
}