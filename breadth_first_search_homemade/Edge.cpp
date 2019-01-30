//
// Created by carpenter on 1/29/19.
//

#include "Edge.h"

GraphEdge::GraphEdge()
{
    currentNode;
    destinationNode;
    
    weight = 0.0;
    label = "<none>";
}

GraphNode& GraphEdge::getCurrentNode()
{
    return currentNode;
}

GraphNode& GraphEdge::getDestinationNode()
{
    return destinationNode;
}

string GraphEdge::getLabel()
{
    return label;
}

double GraphEdge::getWeight() const
{
    return weight;
}