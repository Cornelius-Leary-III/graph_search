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

bool operator==(GraphNode& lhs, GraphNode& rhs);
bool operator!=(GraphNode& lhs, GraphNode& rhs);

#endif //BREADTH_FIRST_SEARCH_HOMEMADE_GRAPHNODE_H
