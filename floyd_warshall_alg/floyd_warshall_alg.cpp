//
// Created by carpenter on 2/9/19.
//

#include <values.h>
#include "floyd_warshall_alg.h"

Floyd_Warshall_Shortest_Path::Floyd_Warshall_Shortest_Path(unsigned long numberOfNodes)
        : nodeCount{numberOfNodes},
          edgeSet{},
          minDistMatrix(numberOfNodes,
                        vector<double>(numberOfNodes, MAXDOUBLE)),
          successorMatrix(numberOfNodes,
                          vector<int>(numberOfNodes, -1))
{
}

void Floyd_Warshall_Shortest_Path::processEdge(const Edge& edgeToProcess)
{
    if (edgeToProcess.source != edgeToProcess.destination)
    {
        minDistMatrix[edgeToProcess.source][edgeToProcess.destination] = edgeToProcess.weight;
        successorMatrix[edgeToProcess.source][edgeToProcess.destination] = edgeToProcess.destination;
    }
}

void Floyd_Warshall_Shortest_Path::addEdgesAsSet(const vector<Edge>& edges)
{
    edgeSet = edges;
    
    auto edgeIter = edgeSet.begin();
    auto edgesEnd = edgeSet.end();
    
    if (!isEdgeSetZeroBased())
    {
        makeEdgeSetZeroBased();
    }
    
    while (edgeIter != edgesEnd)
    {
        processEdge(*edgeIter);
        ++edgeIter;
    }
    
    for (int vertex = 0; vertex < nodeCount; ++vertex)
    {
        minDistMatrix[vertex][vertex] = 0;
    }
}

void Floyd_Warshall_Shortest_Path::processGraph()
{
    for (int step = 0; step < nodeCount; ++step)
    {
        for (int source = 0; source < nodeCount; ++source)
        {
            for (int destination = 0; destination < nodeCount; ++destination)
            {
                double value = minDistMatrix[source][step] + minDistMatrix[step][destination];
                
                if (minDistMatrix[source][destination] > value)
                {
                    minDistMatrix[source][destination] = value;
                    successorMatrix[source][destination] = successorMatrix[source][step];
                }
            }
        }
    }
}

vector<vector<double>>& Floyd_Warshall_Shortest_Path::getMinDistMatrix()
{
    return minDistMatrix;
}

bool Floyd_Warshall_Shortest_Path::isEdgeSetZeroBased()
{
    auto edgeIter = edgeSet.begin();
    auto edgesEnd = edgeSet.end();
    
    while (edgeIter != edgesEnd)
    {
        if (edgeIter->source == 0 ||
            edgeIter->destination == 0)
        {
            return true;
        }
        
        ++edgeIter;
    }
    
    return false;
}

void Floyd_Warshall_Shortest_Path::makeEdgeSetZeroBased()
{
    auto edgeIter = edgeSet.begin();
    auto edgesEnd = edgeSet.end();
    
    while (edgeIter != edgesEnd)
    {
        (edgeIter->source)--;
        (edgeIter->destination)--;
        
        ++edgeIter;
    }
}

vector<int> Floyd_Warshall_Shortest_Path::getPathFromFirstToSecond(int u, int v)
{
    vector<int> path{};
    
    if (successorMatrix[u][v] == -1)
    {
        return path;
    }
    
    path.push_back(u);
    
    while (u != v)
    {
        u = successorMatrix[u][v];
        path.push_back(u);
    }
    
    return path;
}

