//
// Created by carpenter on 2/9/19.
//
// https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
//

#ifndef FLOYD_WARSHALL_ALG_FLOYD_WARSHALL_ALG_H
#define FLOYD_WARSHALL_ALG_FLOYD_WARSHALL_ALG_H

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

class Floyd_Warshall_Shortest_Path
{
public:
    
    explicit Floyd_Warshall_Shortest_Path(unsigned long numberOfNodes);
    
    void addEdgesAsSet(const vector<Edge>& edges);
    void processGraph();
    vector<vector<double>>& getMinDistMatrix();
    vector<int> getPathFromFirstToSecond(int u, int v);
    
private:
    
    void processEdge(const Edge& edgeToProcess);
    bool isEdgeSetZeroBased();
    void makeEdgeSetZeroBased();
    
    vector<Edge> edgeSet;
    vector<vector<double>> minDistMatrix;
    vector<vector<int>> successorMatrix;
    unsigned long nodeCount;
};

#endif //FLOYD_WARSHALL_ALG_FLOYD_WARSHALL_ALG_H
