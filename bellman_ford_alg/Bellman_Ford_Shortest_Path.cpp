//
// Created by carpenter on 2/9/19.
//

#include "Bellman_Ford_Shortest_Path.h"

Bellman_Ford_Shortest_Path::Bellman_Ford_Shortest_Path(unsigned long numberOfNodes)
        : nodeCount{numberOfNodes}, edgeSet{},
          distanceTable(numberOfNodes, MAXDOUBLE),
          predecessorTable(numberOfNodes, -1)
{
}

void Bellman_Ford_Shortest_Path::processGraph(int sourceVertex)
{
    auto edgesEnd = edgeSet.end();
    
    distanceTable[sourceVertex] = 0.0;
    
    int step = 0;
    while (step < distanceTable.size() - 1)
    {
        auto edgeIter = edgeSet.begin();
        while (edgeIter != edgesEnd)
        {
            if (distanceTable[edgeIter->source] != MAXDOUBLE &&
                (distanceTable[edgeIter->source] + edgeIter->weight) < distanceTable[edgeIter->destination])
            {
                distanceTable[edgeIter->destination] = distanceTable[edgeIter->source] + edgeIter->weight;
                predecessorTable[edgeIter->destination] = edgeIter->source;
            }
            ++edgeIter;
        }
        ++step;
    }
    
    auto edgeIter = edgeSet.begin();
    while (edgeIter != edgesEnd)
    {
        if ((distanceTable[edgeIter->source] + edgeIter->weight) < distanceTable[edgeIter->destination])
        {
            throw "Graph contains negative-weight cycle";
        }
        ++edgeIter;
    }
}

vector<double>& Bellman_Ford_Shortest_Path::getDistanceTable()
{
    return distanceTable;
}

vector<int>& Bellman_Ford_Shortest_Path::getPredecessorTable()
{
    return predecessorTable;
}

vector<Edge>& Bellman_Ford_Shortest_Path::getEdgeSet()
{
    return edgeSet;
}

void Bellman_Ford_Shortest_Path::addEdges(const vector<Edge>& edges)
{
    edgeSet = edges;
    
    if (!isEdgeSetZeroBased())
    {
        makeEdgeSetZeroBased();
    }
}

bool Bellman_Ford_Shortest_Path::isEdgeSetZeroBased()
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

void Bellman_Ford_Shortest_Path::makeEdgeSetZeroBased()
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