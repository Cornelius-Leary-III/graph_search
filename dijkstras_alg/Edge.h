//
// Created by cornelius on 4/22/19.
//

#ifndef DIJKSTRAS_ALG_EDGE_H
#define DIJKSTRAS_ALG_EDGE_H

#include "BaseNode.h"

struct Edge
{
   BaseNode mSource;
   BaseNode mDestination;
   double   mWeight;

   Edge();

   Edge(const BaseNode& source, const BaseNode& destination, double weight = 1.0);

   Edge(const std::string& source, const std::string& destination, double weight = 1.0);

   Edge(const Edge& edge_to_copy);

   Edge& operator=(const Edge& edge_to_copy);
};

bool operator==(const Edge& lhs, const Edge& rhs);
bool operator!=(const Edge& lhs, const Edge& rhs);

#endif // DIJKSTRAS_ALG_EDGE_H
