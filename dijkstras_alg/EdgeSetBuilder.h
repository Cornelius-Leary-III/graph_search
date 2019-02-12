//
// Created by carpenter on 2/12/19.
//

#ifndef DIJKSTRAS_ALG_EDGESETBUILDER_H
#define DIJKSTRAS_ALG_EDGESETBUILDER_H

#include <vector>
#include <fstream>
#include <sstream>
#include <istream>
#include <ostream>

using std::vector;
using std::ifstream;
using std::istream;
using std::stringstream;
using std::string;
using std::ostream;
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

class EdgeSetBuilder
{
public:
    
    EdgeSetBuilder();

    void createAndAppendEdge(int newSource, int newDestination, double newWeight);
    void readEdgesFromFile();
    
    // figure out how to incorporate Euclidean coordinates in edge representation.

private:
    
    vector<Edge> edgeSet;
    
};


#endif //DIJKSTRAS_ALG_EDGESETBUILDER_H


















