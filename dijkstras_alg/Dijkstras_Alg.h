//
// Created by carpenter on 2/11/19.
//

#ifndef DIJKSTRAS_ALG_DIJKSTRAS_ALG_H
#define DIJKSTRAS_ALG_DIJKSTRAS_ALG_H

#include <values.h>
#include <vector>
#include <queue>
#include <iostream>

using std::vector;
using std::queue;
using std::priority_queue;
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
            this->weight = edgeToCopy.weight;
        }
        
        return *this;
    }
};

class Dijkstras_Alg
{
public:
    
    Dijkstras_Alg(unsigned long numberOfNodes);
    
    void addEdges(const vector<Edge>& edges);
    void compute(int sourceVertex);
    
    queue<int>& getUnvisitedVertices();
    vector<double>& getDistanceTable();
    vector<int>& getPredecessorTable();
    vector<Edge>& getEdgeSet();

private:
    
    queue<int> unvisitedVertices;
    vector<double> distanceTable;
    vector<int> predecessorTable;
    vector<Edge> edgeSet;
    unsigned long nodeCount;
};


#endif //DIJKSTRAS_ALG_DIJKSTRAS_ALG_H










