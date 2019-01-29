//
// Created by carpenter on 1/28/19.
//

#ifndef BREADTH_FIRST_SEARCH_HOMEMADE_GRAPHNODE_H
#define BREADTH_FIRST_SEARCH_HOMEMADE_GRAPHNODE_H

#include <string>

using std::string;

class GraphNode
{
public:
    
    GraphNode();
    explicit GraphNode(const string& newName);
    GraphNode(const string& newName, double newValue);
    
    virtual ~GraphNode() = default;
    
    virtual double getNodeValue() const;
    string getNodeName();

private:
    
    string name;
    double value;
    
};

class GridNode : public GraphNode
{
public:
    
    GridNode();
    explicit GridNode(const string& newName);
    GridNode(const string& newName, double newXCoord, double newYCoord);
    GridNode(const string& newName, double newValue,
             double newXCoord, double newYCoord);
    
    ~GridNode() override = default;
    
    double getXCoord() const;
    double getYCoord() const;

private:
    
    double xCoord;
    double yCoord;
    
};


#endif //BREADTH_FIRST_SEARCH_HOMEMADE_GRAPHNODE_H
