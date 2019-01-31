//
// Created by carpenter on 1/30/19.
//

#include "Graph.h"

Graph::Graph()
        : graphIsDirected(true)
{
}

Graph::Graph(bool graphIsDirectedState)
        : graphIsDirected(graphIsDirectedState)
{
}

//Graph::~Graph()
//{
//}

void Graph::addNode(GraphNode& newGraphNode)
{
    nodeList.push_back(newGraphNode);
}

void Graph::addEdge(GraphEdge& newGraphEdge)
{
    if (graphIsDirected)
    {
        addEdgeDirected(newGraphEdge);
    }
    else
    {
        addEdgeUndirected(newGraphEdge);
    }
}

void Graph::addEdgeDirected(GraphEdge& newGraphEdge)
{
    string sourceNodeName = newGraphEdge.getSourceName();
    
    auto neighborsFindIter = adjacencyList.find(sourceNodeName);
    if (neighborsFindIter != adjacencyList.end())
    {
        (neighborsFindIter->second).push_back(newGraphEdge);
    }
    else
    {
        vector<GraphEdge> newNeighbors{newGraphEdge};
        adjacencyList.emplace(sourceNodeName, newNeighbors);
    }
}

void Graph::addEdgeUndirected(GraphEdge& newGraphEdge)
{
    addEdgeDirected(newGraphEdge);
    
    GraphEdge reverseDirectionEdge(newGraphEdge);
    
    auto tempNode = newGraphEdge.getSourceNode();
    reverseDirectionEdge.setSourceNode(newGraphEdge.getDestinationNode());
    reverseDirectionEdge.setDestinationNode(tempNode);
    string reverseSourceNodeName = reverseDirectionEdge.getSourceName();
    
    addEdgeDirected(reverseDirectionEdge);
}

vector<GraphNode>& Graph::getNodeList()
{
    return nodeList;
}

map<string, vector<GraphEdge>>& Graph::getAdjacencyList()
{
    return adjacencyList;
}

unsigned long Graph::getNodeCount()
{
    return nodeList.size();
}

bool Graph::isGraphDirected()
{
    return graphIsDirected;
}

