//
// Created by cornelius on 4/22/19.
//

#include "Edge.h"

Edge::Edge()
        : source{0}, destination{0}, weight{0.0}
{
}

Edge::Edge(int newSource, int newDestination)
        : source{newSource}, destination{newDestination}, weight{1.0}
{
}

Edge::Edge(int newSource, int newDestination, double newWeight)
        : source{newSource}, destination{newDestination}, weight{newWeight}
{
}

Edge::Edge(const Edge& edgeToCopy)
{
    if (this != &edgeToCopy)
    {
        this->source = edgeToCopy.source;
        this->destination = edgeToCopy.destination;
        this->weight = edgeToCopy.weight;
    }
}

Edge& Edge::operator=(const Edge& edgeToCopy)
{
    if (this != &edgeToCopy)
    {
        this->source = edgeToCopy.source;
        this->destination = edgeToCopy.destination;
        this->weight = edgeToCopy.weight;
    }
    
    return *this;
}

bool operator==(const Edge& lhs, const Edge& rhs)
{
    return (lhs.source == rhs.source) &&
           (lhs.destination == rhs.destination) &&
           (lhs.weight == rhs.weight);
}

bool operator!=(const Edge& lhs, const Edge& rhs)
{
    return !(lhs == rhs);
}