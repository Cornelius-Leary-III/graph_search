//
// Created by cornelius on 4/22/19.
//

#include "Edge.h"

Edge::Edge() : mSource("0"), mDestination("0"), mWeight(0.0)
{
}

Edge::Edge(const BaseNode& source, const BaseNode& destination, double weight)
   : mSource(source),
     mDestination(destination),
     mWeight(weight)
{
}

Edge::Edge(const std::string& source, const std::string& destination, double weight)
   : mSource(source),
     mDestination(destination),
     mWeight(weight)
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
