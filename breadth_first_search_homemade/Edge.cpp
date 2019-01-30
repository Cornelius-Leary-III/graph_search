//
// Created by carpenter on 1/29/19.
//

#include "Edge.h"

GraphEdge::GraphEdge()
        : weight(1.00)
{
}

void GraphEdge::setSourceNode(const GraphNode& newSource)
{
    currentNode = newSource;
}

void GraphEdge::setDestinationNode(const GraphNode& newDestination)
{
    destinationNode = newDestination;
}

void GraphEdge::setWeight(double newWeight)
{
    weight = newWeight;
}

void GraphEdge::setLabel(const string& newLabel)
{
    label = newLabel;
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

double GraphEdge::getWeight()
{
    return weight;
}