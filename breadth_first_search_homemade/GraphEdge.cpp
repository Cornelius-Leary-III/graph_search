//
// Created by carpenter on 1/29/19.
//

#include "GraphEdge.h"

GraphEdge::GraphEdge()
        : weight(1.00)
{
}

GraphEdge::GraphEdge(const GraphEdge& edgeToCopy)
        : sourceName(edgeToCopy.sourceName),
          sourceNode(edgeToCopy.sourceNode),
          destinationNode(edgeToCopy.destinationNode),
          weight(edgeToCopy.weight),
          label(edgeToCopy.label)
{
}

void GraphEdge::setSourceNode(GraphNode& newSource)
{
    sourceNode = newSource;
    sourceName = newSource.getNodeName();
}

void GraphEdge::setDestinationNode(GraphNode& newDestination)
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

GraphNode& GraphEdge::getSourceNode()
{
    return sourceNode;
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

string GraphEdge::getSourceName()
{
    return sourceName;
}

bool operator==(GraphEdge& lhs, GraphEdge& rhs)
{
    return (lhs.getSourceName() == rhs.getSourceName()) &&
           (lhs.getSourceNode() == rhs.getSourceNode()) &&
           (lhs.getDestinationNode() == rhs.getDestinationNode()) &&
           (lhs.getWeight() == rhs.getWeight()) &&
           (lhs.getLabel() == rhs.getLabel());
}

bool operator!=(GraphEdge& lhs, GraphEdge& rhs)
{
    return !(lhs == rhs);
}















