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
    ~GraphEdge() = default;
    
    void setSourceNode(const GraphNode& newSource);
    void setDestinationNode(const GraphNode& newDestination);
    void setWeight(double newWeight);
    void setLabel(const string& newLabel);
    
    GraphNode& getCurrentNode();
    GraphNode& getDestinationNode();
    double getWeight();
    string getLabel();

private:

    GraphNode currentNode;
    GraphNode destinationNode;

    double weight;
    string label;

};


#endif //BREADTH_FIRST_SEARCH_HOMEMADE_EDGE_H
