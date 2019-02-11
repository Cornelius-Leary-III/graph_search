//
// Created by carpenter on 2/9/19.
//

#ifndef BELLMAN_FORD_ALG_BELLMAN_FORD_ALG_H
#define BELLMAN_FORD_ALG_BELLMAN_FORD_ALG_H

#include <values.h>
#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

struct Edge
{
    int source;
    int destination;
    double weight;
    
    Edge()
            : source{0}, destination{0}, weight{0.0}
    {
    }
    
    Edge(int newSource, int newDestination)
            : source{newSource}, destination{newDestination}, weight{1.0}
    {
    }
    
    Edge(int newSource, int newDestination, double newWeight)
            : source{newSource}, destination{newDestination}, weight{newWeight}
    {
    }
    
    Edge& operator=(const Edge& edgeToCopy)
    {
        if (this != &edgeToCopy)
        {
            this->source = edgeToCopy.source;
            this->destination = edgeToCopy.destination;
        }
        
        return *this;
    }
};

class Bellman_Ford_Shortest_Path
{
public:
    
    explicit Bellman_Ford_Shortest_Path(unsigned long numberOfNodes);
    
    void addEdges(const vector<Edge>& edges);
    void processGraph(int sourceVertex);
    vector<double>& getDistanceTable();
    vector<int>& getPredecessorTable();
    vector<Edge>& getEdgeSet();

private:
    
    bool isEdgeSetZeroBased();
    void makeEdgeSetZeroBased();
    
    vector<Edge> edgeSet;
    vector<double> distanceTable;
    vector<int> predecessorTable;
    unsigned long nodeCount;
};


#endif //BELLMAN_FORD_ALG_BELLMAN_FORD_ALG_H


















