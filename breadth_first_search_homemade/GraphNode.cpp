//
// Created by carpenter on 1/28/19.
//

#include "GraphNode.h"

GraphNode::GraphNode()
{
    name = "?";
    value = -1;
}

GraphNode::GraphNode(const string& newName)
{
    name = newName;
    value = -1;
}

GraphNode::GraphNode(const string& newName, double newValue)
{
    name = newName;
    value = newValue;
}

string GraphNode::getNodeName()
{
    return name;
}

double GraphNode::getNodeValue() const
{
    return value;
}

GridNode::GridNode()
        : GraphNode()
{
    xCoord = 0.0;
    yCoord = 0.0;
}

GridNode::GridNode(const string& newName)
        : GraphNode(newName)
{
    xCoord = 0.0;
    yCoord = 0.0;
}

GridNode::GridNode(const string& newName, double newXCoord, double newYCoord)
        : GraphNode(newName)
{
    xCoord = newXCoord;
    yCoord = newYCoord;
}

GridNode::GridNode(const string& newName, double newValue,
                   double newXCoord, double newYCoord)
        : GraphNode(newName, newValue)
{
    xCoord = newXCoord;
    yCoord = newYCoord;
}

double GridNode::getXCoord() const
{
    return xCoord;
}

double GridNode::getYCoord() const
{
    return yCoord;
}