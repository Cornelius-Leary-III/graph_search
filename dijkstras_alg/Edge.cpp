//
// Created by cornelius on 4/22/19.
//

#include "Edge.h"

Edge::Edge() : mSource{0}, mDestination{0}, mWeight{0.0}
{
}

Edge::Edge(int new_source, int new_destination)
   : mSource(new_source),
     mDestination(new_destination),
     mWeight(1.0)
{
}

Edge::Edge(int new_source, int new_destination, double new_weight)
   : mSource(new_source),
     mDestination(new_destination),
     mWeight(new_weight)
{
}

Edge::Edge(const Edge& edge_to_copy)
{
   if (this != &edge_to_copy)
   {
      this->mSource      = edge_to_copy.mSource;
      this->mDestination = edge_to_copy.mDestination;
      this->mWeight      = edge_to_copy.mWeight;
   }
}

Edge& Edge::operator=(const Edge& edge_to_copy)
{
   if (this != &edge_to_copy)
   {
      this->mSource      = edge_to_copy.mSource;
      this->mDestination = edge_to_copy.mDestination;
      this->mWeight      = edge_to_copy.mWeight;
   }

   return *this;
}

bool operator==(const Edge& lhs, const Edge& rhs)
{
   return (lhs.mSource == rhs.mSource) && (lhs.mDestination == rhs.mDestination)
          && (lhs.mWeight == rhs.mWeight);
}

bool operator!=(const Edge& lhs, const Edge& rhs)
{
   return !(lhs == rhs);
}
