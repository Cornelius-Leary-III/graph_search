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

bool operator==(GraphNode& lhs, GraphNode& rhs)
{
    return (lhs.getNodeName() == rhs.getNodeName()) &&
           (lhs.getNodeValue() == rhs.getNodeValue());
}

bool operator!=(GraphNode& lhs, GraphNode& rhs)
{
    return !(lhs == rhs);
}