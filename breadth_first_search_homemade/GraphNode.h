//
// Created by carpenter on 1/28/19.
//

#ifndef BREADTH_FIRST_SEARCH_HOMEMADE_GRAPHNODE_H
#define BREADTH_FIRST_SEARCH_HOMEMADE_GRAPHNODE_H

#include <istream>
#include <string>
#include <vector>

using std::istream;
using std::string;
using std::vector;

class GraphNode
{
public:
    
    GraphNode();
    GraphNode(const GraphNode& nodeToCopy);
    
    explicit GraphNode(const string& newName);
    GraphNode(const string& newName, double newValue);
    GraphNode(const string& newName, double newXCoord, double newYCoord);
    GraphNode(const string& newName, double newValue,
              double newXCoord, double newYCoord);
    
    ~GraphNode() = default;
    
    string getNodeName();
    double getNodeValue();
    double getNodeXCoord();
    double getNodeYCoord();
    
//    GraphNode& operator=(GraphNode& rhs);
    friend istream& operator>>(istream& input, GraphNode& nodeToUpdate);

private:
    
    string name;
    double value;
    double xCoord;
    double yCoord;
    
};

bool operator==(GraphNode& lhs, GraphNode& rhs);
bool operator!=(GraphNode& lhs, GraphNode& rhs);

#endif //BREADTH_FIRST_SEARCH_HOMEMADE_GRAPHNODE_H
