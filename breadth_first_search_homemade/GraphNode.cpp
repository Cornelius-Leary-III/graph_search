//
// Created by carpenter on 1/28/19.
//

#include "GraphNode.h"

GraphNode::GraphNode()
        : name("?"), value(-1),
          xCoord(0.0), yCoord(0.0)
{
}

GraphNode::GraphNode(const string& newName)
        : name(newName), value(-1),
          xCoord(0.0), yCoord(0.0)
{
}

GraphNode::GraphNode(const string& newName, double newValue)
        : name(newName), value(newValue),
          xCoord(0.0), yCoord(0.0)
{
}

GraphNode::GraphNode(const string& newName,
                     double newXCoord, double newYCoord)
        : name(newName), value(-1),
          xCoord(newXCoord), yCoord(newYCoord)
{
}

GraphNode::GraphNode(const string& newName, double newValue,
                     double newXCoord, double newYCoord)
        : name(newName), value(newValue),
          xCoord(newXCoord), yCoord(newYCoord)
{
}

string GraphNode::getNodeName()
{
    return name;
}

double GraphNode::getNodeValue()
{
    return value;
}

double GraphNode::getNodeXCoord()
{
    return xCoord;
}

double GraphNode::getNodeYCoord()
{
    return yCoord;
}

//GraphNode& GraphNode::operator=(GraphNode& rhs)
//{
//    if (this != &rhs)
//    {
//        this->name = rhs.name;
//        this->value = rhs.value;
//        this->xCoord = rhs.xCoord;
//        this->yCoord = rhs.yCoord;
//    }
//
//    return *this;
//}

istream& operator>>(istream& input, GraphNode& nodeToUpdate)
{
    input >> nodeToUpdate.name
          >> nodeToUpdate.value
          >> nodeToUpdate.xCoord
          >> nodeToUpdate.yCoord;
    
    return input;
}

bool operator==(GraphNode& lhs, GraphNode& rhs)
{
    return (lhs.getNodeName() == rhs.getNodeName()) &&
           (lhs.getNodeValue() == rhs.getNodeValue()) &&
           (lhs.getNodeXCoord() == rhs.getNodeXCoord()) &&
           (lhs.getNodeYCoord() == rhs.getNodeYCoord());
}

bool operator!=(GraphNode& lhs, GraphNode& rhs)
{
    return !(lhs == rhs);
}