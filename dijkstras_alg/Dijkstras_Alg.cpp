//
// Created by carpenter on 2/11/19.
//

#include "Dijkstras_Alg.h"

Dijkstras_Alg::Dijkstras_Alg(unsigned long numberOfNodes)
        : openSet{},
          distanceTable(numberOfNodes, MAXDOUBLE),
          visitedTable(numberOfNodes, false),
          adjList(numberOfNodes, vector<adjListNode>()),
        
          predecessorTable(numberOfNodes, -1),
          edgeSet{},
          nodeCount{numberOfNodes}
{
}

void Dijkstras_Alg::compute(int sourceVertex)
{
    if (sourceVertex >= nodeCount ||
        sourceVertex < 0)
    {
        throw StartNodeProvidedIsNonExistentException();
    }
    
    distanceTable[sourceVertex] = 0;
    openSet.emplace(distanceTable[sourceVertex], sourceVertex);
    
    while (!openSet.empty())
    {
        auto currentNode = openSet.top();
        openSet.pop();
        
        processCurrentNode(currentNode.second);
    }
}

void Dijkstras_Alg::processCurrentNode(int name)
{
    for (auto& neighbor : adjList[name])
    {
        int neighborName = neighbor.first;
        
        double alternatePath = distanceTable[name] + neighbor.second;
        if (alternatePath < distanceTable[neighborName])
        {
            distanceTable[neighborName] = alternatePath;
            predecessorTable[neighborName] = name;
            
            openSet.emplace(distanceTable[neighborName], neighborName);
        }
    }
}

vector<int> Dijkstras_Alg::getPathFromStartToNode(int start, int end)
{
    compute(start);
    
    vector<int> backTracingPath;
    if (end <= predecessorTable.size())
    {
        int backTracingIndex = end;
        while (backTracingIndex != start &&
               backTracingIndex != -1)
        {
            backTracingPath.push_back(backTracingIndex);
            backTracingIndex = predecessorTable[backTracingIndex];
        }
        
        backTracingPath.push_back(backTracingIndex);
    }
    
    return std::move(vector<int>(backTracingPath.rbegin(),
                                 backTracingPath.rend()));
}

void Dijkstras_Alg::addEdges(const vector<Edge>& edges)
{
    edgeSet = edges;
    
    buildAdjacencyList();
}

vector<vector<adjListNode>>& Dijkstras_Alg::getAdjacencyList()
{
    return adjList;
}

priority_queue<node>& Dijkstras_Alg::getUnvisitedVertices()
{
    return openSet;
}

vector<double>& Dijkstras_Alg::getDistanceTable()
{
    return distanceTable;
}

vector<int>& Dijkstras_Alg::getPredecessorTable()
{
    return predecessorTable;
}

vector<bool>& Dijkstras_Alg::getVisitedTable()
{
    return visitedTable;
}

vector<Edge>& Dijkstras_Alg::getEdgeSet()
{
    return edgeSet;
}


void Dijkstras_Alg::buildAdjacencyList()
{
    for (auto& edge: edgeSet)
    {
        if (edge.weight < 0)
        {
            throw NegativeEdgeWeightsException();
        }
        
        adjList[edge.source].emplace_back(edge.destination, edge.weight);
    }
}

void Dijkstras_Alg::resetAll()
{
    resetVisitedTable();
    resetDistanceTable();
    resetPredecessorTable();
    resetOpenSet();
}

void Dijkstras_Alg::resetVisitedTable()
{
    auto newVisitedTable = vector<bool>(nodeCount, false);
    visitedTable.swap(newVisitedTable);
}

void Dijkstras_Alg::resetDistanceTable()
{
    auto newDistanceTable = vector<double>(nodeCount, MAXDOUBLE);
    distanceTable.swap(newDistanceTable);
}

void Dijkstras_Alg::resetPredecessorTable()
{
    auto newPredecessorTable = vector<int>(nodeCount, -1);
    predecessorTable.swap(newPredecessorTable);
}

void Dijkstras_Alg::resetOpenSet()
{
    auto newOpenSet = priority_queue<node>();
    openSet.swap(newOpenSet);
}