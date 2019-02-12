//
// Created by carpenter on 2/11/19.
//

#include "Dijkstras_Alg.h"

Dijkstras_Alg::Dijkstras_Alg(unsigned long numberOfNodes)
        : unvisitedVertices{},
          distanceTable(numberOfNodes, MAXDOUBLE),
          predecessorTable(numberOfNodes, -1),
          edgeSet{},
          nodeCount{numberOfNodes}
{
    
}

void Dijkstras_Alg::compute(int sourceVertex)
{

}

void Dijkstras_Alg::addEdges(const vector<Edge>& edges)
{
    edgeSet = edges;
}

queue<int>& Dijkstras_Alg::getUnvisitedVertices()
{
    return unvisitedVertices;
}

vector<double>& Dijkstras_Alg::getDistanceTable()
{
    return distanceTable;
}

vector<int>& Dijkstras_Alg::getPredecessorTable()
{
    return predecessorTable;
}

vector<Edge>& Dijkstras_Alg::getEdgeSet()
{
    return edgeSet;
}










