//
// Created by carpenter on 1/29/19.
//

#ifndef BREADTH_FIRST_SEARCH_HOMEMADE_EDGE_H
#define BREADTH_FIRST_SEARCH_HOMEMADE_EDGE_H

#include "GraphNode.h"

class GraphEdge
{
public:

    GraphEdge();
    GraphEdge(const GraphEdge& edgeToCopy);
    ~GraphEdge() = default;
    
    void setSourceNode(GraphNode& newSource);
    void setDestinationNode(GraphNode& newDestination);
    void setWeight(double newWeight);
    void setLabel(const string& newLabel);
    
    GraphNode& getSourceNode();
    GraphNode& getDestinationNode();
    double getWeight();
    string getLabel();
    string getSourceName();

private:

    string sourceName;
    GraphNode sourceNode;
    GraphNode destinationNode;
    double weight;
    string label;
};

bool operator==(GraphEdge& lhs, GraphEdge& rhs);
bool operator!=(GraphEdge& lhs, GraphEdge& rhs);


#endif //BREADTH_FIRST_SEARCH_HOMEMADE_EDGE_H
