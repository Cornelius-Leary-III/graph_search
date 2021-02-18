//
// Created by cornelius on 4/22/19.
//

#ifndef DIJKSTRAS_ALG_EDGE_H
#define DIJKSTRAS_ALG_EDGE_H

struct Edge
{
   int    mSource;
   int    mDestination;
   double mWeight;

   Edge();
   Edge(int new_source, int new_destination);
   Edge(int new_source, int new_destination, double new_weight);
   Edge(const Edge& edge_to_copy);

   Edge& operator=(const Edge& edge_to_copy);
};

bool operator==(const Edge& lhs, const Edge& rhs);
bool operator!=(const Edge& lhs, const Edge& rhs);

#endif // DIJKSTRAS_ALG_EDGE_H
