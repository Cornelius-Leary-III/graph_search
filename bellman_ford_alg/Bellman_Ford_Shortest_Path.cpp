//
// Created by carpenter on 2/9/19.
//

#include "Bellman_Ford_Shortest_Path.h"

Bellman_Ford_Shortest_Path::Bellman_Ford_Shortest_Path(unsigned long numberOfNodes)
        : nodeCount{numberOfNodes}, edgeSet{},
          distanceTable(numberOfNodes, MAXDOUBLE),
          predecessorTable(numberOfNodes, -1)
//          distanceTableSteppedThrough{},
//          predecessorTableSteppedThrough{}
//          distanceTable(numberOfNodes, vector<double>(numberOfNodes, MAXDOUBLE)),
//          predecessorTable(numberOfNodes, vector<int>(numberOfNodes, -1))
{
}

void Bellman_Ford_Shortest_Path::processGraph(int sourceVertex)
{
    auto edgesEnd = edgeSet.end();
    
    distanceTable[sourceVertex] = 0.0;
    
//    distanceTableSteppedThrough.push_back(distanceTable);
//    predecessorTableSteppedThrough.push_back(predecessorTable);
    
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
        
//        distanceTableSteppedThrough.push_back(distanceTable);
//        predecessorTableSteppedThrough.push_back(predecessorTable);
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

//vector<vector<double>>& Bellman_Ford_Shortest_Path::getSteppedThroughDistanceTable()
//{
//    return distanceTableSteppedThrough;
//}
//
//vector<vector<int>>& Bellman_Ford_Shortest_Path::getSteppedThroughPredecessorTable()
//{
//    return predecessorTableSteppedThrough;
//}

void Bellman_Ford_Shortest_Path::addEdges(const vector<Edge>& edges)
{
    edgeSet = edges;
    
    //    auto edgeIter = edgeSet.begin();
    //    auto edgesEnd = edgeSet.end();
    
    if (!isEdgeSetZeroBased())
    {
        makeEdgeSetZeroBased();
    }
    
    //    while (edgeIter != edgesEnd)
    //    {
    //        processEdge(*edgeIter);
    //        ++edgeIter;
    //    }
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

void Bellman_Ford_Shortest_Path::processEdge(const Edge& edgeToProcess)
{
    if (edgeToProcess.source != edgeToProcess.destination)
    {
        distanceTable[edgeToProcess.source] = edgeToProcess.weight;
        predecessorTable[edgeToProcess.source] = edgeToProcess.destination;
    }
}