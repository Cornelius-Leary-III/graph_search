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
    //    int vertex = 0;
    //    while (vertex < nodeCount)
    //    {
    //        openSet.push(vertex);
    //        ++vertex;
    //    }
}

void Dijkstras_Alg::compute(int sourceVertex)
{
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

double Dijkstras_Alg::getDistanceFromStartToNode(int start, int end)
{
    compute(start);
    
    return distanceTable[end];
}

vector<int> Dijkstras_Alg::getPathFromStartToNode(int start, int end)
{
    compute(start);
    
    vector<int> backTracingPath;
    if (end < predecessorTable.size())
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
    
    if (!isEdgeSetZeroBased())
    {
        makeEdgeSetZeroBased();
    }
    
    try
    {
        buildAdjacencyList();
    }
    catch (NegativeEdgeWeightsException& exception)
    {
        cout << "Exception occurred during edge adding: \n" << exception.what() << endl;
    }
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

vector<Edge>& Dijkstras_Alg::getEdgeSet()
{
    return edgeSet;
}

bool Dijkstras_Alg::isEdgeSetZeroBased()
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

void Dijkstras_Alg::makeEdgeSetZeroBased()
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

void Dijkstras_Alg::resetThenCompute(int sourceVertex)
{
    resetAll();
    compute(sourceVertex);
}

vector<int> Dijkstras_Alg::resetThenGetPathFromStartToNode(int start, int end)
{
    resetAll();
    return std::move(getPathFromStartToNode(start, end));
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