//
// Created by cornelius on 4/22/19.
//

#ifndef DIJKSTRAS_ALG_EDGE_H
#define DIJKSTRAS_ALG_EDGE_H

struct Edge
{
    int source;
    int destination;
    double weight;
    
    Edge();
    Edge(int newSource, int newDestination);
    Edge(int newSource, int newDestination, double newWeight);
    Edge(const Edge& edgeToCopy);
    
    Edge& operator=(const Edge& edgeToCopy);
};

bool operator==(const Edge& lhs, const Edge& rhs);
bool operator!=(const Edge& lhs, const Edge& rhs);


#endif //DIJKSTRAS_ALG_EDGE_H
