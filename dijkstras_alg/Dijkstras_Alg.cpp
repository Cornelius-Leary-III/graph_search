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
    // check if the source node is too large or a negative #.
    if (sourceVertex >= nodeCount ||
        sourceVertex < 0)
    {
        throw StartNodeProvidedIsNonExistentException();
    }
    
    // set the distance to the source node from the source node to be 0.
    distanceTable[sourceVertex] = 0;
    
    // put the this edge into the open set queue.
    openSet.emplace(distanceTable[sourceVertex], sourceVertex);
    
    // continue computing as long as there are still edges in the open set queue.
    while (!openSet.empty())
    {
        // save and remove the top of the open set queue.
        auto currentNode = openSet.top();
        openSet.pop();
        
        // process the top node.
        processCurrentNode(currentNode.second);
    }
}

void Dijkstras_Alg::processCurrentNode(int name)
{
    // process each neighbor of the provided node.
    for (auto& neighbor : adjList[name])
    {
        int neighborName = neighbor.first;
        
        // compute the alternative path to this node:
        //      --> add the existing cost from the source node to the current node to the weight of the
        //              edge to the neighbor node.
        double alternatePath = distanceTable[name] + neighbor.second;
        
        // compare the cost of going from the source node to the neighbor node and
        //      the cost of going from the source node to the neighbor node via the current node.
        if (alternatePath < distanceTable[neighborName])
        {
            // traveling via the current node is a less-costly path, so update the distance and predecessor tables to
            //      reflect the new best path.
            distanceTable[neighborName] = alternatePath;
            predecessorTable[neighborName] = name;
            
            // add this neighbor and the new distance to the open set queue.
            openSet.emplace(distanceTable[neighborName], neighborName);
        }
    }
}

vector<int> Dijkstras_Alg::getPathFromStartToNode(int start, int end)
{
    //TODO: (04/24/19)
    //      either:
    //          * reimplement the reset() methods I had in a previous version.
    //          * remove the call to the compute() module here.
    
    // compute the distances using the provided start node.
    compute(start);
    
    vector<int> backTracingPath;
    
    // check that the end node provided is within the graph.
    if (end <= predecessorTable.size())
    {
        // begin at the end node
        int backTracingIndex = end;
        
        // continue until the index is:
        //      * at the start node provided
        //      * at a dead-end (== -1)
        while (backTracingIndex != start &&
               backTracingIndex != -1)
        {
            // add the current index (which doubles as the node name) to the path.
            backTracingPath.push_back(backTracingIndex);
            
            // advance to the next predecessor.
            backTracingIndex = predecessorTable[backTracingIndex];
        }
        
        // add the final index to the path.
        backTracingPath.push_back(backTracingIndex);
    }
    
    // reverse the path; goes from start node to goal node.
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