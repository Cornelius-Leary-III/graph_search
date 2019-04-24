//
// Created by carpenter on 2/12/19.
//

#include "EdgeSetBuilder.h"

EdgeSetBuilder::EdgeSetBuilder()
        : edgeSet{},
          directedGraph{true},
          negativeEdgesAllowed{false},
          selfLoopsAllowed{false}
{
}

EdgeSetBuilder::EdgeSetBuilder(bool directedGraphState,
                               bool negativeEdgesAllowedState,
                               bool selfLoopsAllowedState)
        : edgeSet{},
          directedGraph{directedGraphState},
          negativeEdgesAllowed{negativeEdgesAllowedState},
          selfLoopsAllowed{selfLoopsAllowedState}
{
}

EdgeSetBuilder::EdgeSetBuilder(const vector<Edge>& edges,
                               bool directedGraphState)
        : directedGraph{directedGraphState}
{
    if (!directedGraph)
    {
        // add the reverse-edge when the graph is undirected.
        addEdgesForUndirectedGraph(edges);
    }
    else
    {
        // when the graph is directed, the edge set provided is used.
        edgeSet = edges;
    }
    
    // determine these graph traits from the provided edge set.
    negativeEdgesAllowed = checkForNegativeEdges();
    selfLoopsAllowed = checkForSelfLoops();
}

EdgeSetBuilder::EdgeSetBuilder(const EdgeSetBuilder& edgeSetBuilderToCopy)
        : edgeSet{edgeSetBuilderToCopy.edgeSet},
          directedGraph{edgeSetBuilderToCopy.directedGraph},
          negativeEdgesAllowed{edgeSetBuilderToCopy.negativeEdgesAllowed},
          selfLoopsAllowed{edgeSetBuilderToCopy.selfLoopsAllowed}
{
}

void EdgeSetBuilder::addEdgesForUndirectedGraph(const vector<Edge>& edges)
{
    auto edgeIter = edges.begin();
    auto edgesEnd = edges.end();
    
    vector<Edge> undirectedEdges;
    
    while (edgeIter != edgesEnd)
    {
        undirectedEdges.push_back(*edgeIter);                   // add the forward edge.
        undirectedEdges.emplace_back(edgeIter->destination,     // add the reverse edge.
                                     edgeIter->source,
                                     edgeIter->weight);
        ++edgeIter;
    }
    
    edgeSet = undirectedEdges;
}

EdgeSetBuilder& EdgeSetBuilder::operator=(const EdgeSetBuilder& rhs)
{
    if (this != &rhs)
    {
        this->edgeSet = rhs.edgeSet;
        this->directedGraph = rhs.directedGraph;
        this->negativeEdgesAllowed = rhs.negativeEdgesAllowed;
        this->selfLoopsAllowed = rhs.selfLoopsAllowed;
    }
    
    return *this;
}

bool EdgeSetBuilder::checkForNegativeEdges()
{
    auto edgeIter = edgeSet.begin();
    auto edgesEnd = edgeSet.end();
    
    while (edgeIter != edgesEnd)
    {
        if (edgeIter->weight < 0)
        {
            return true;
        }
        ++edgeIter;
    }
    
    return false;
}

bool EdgeSetBuilder::checkForSelfLoops()
{
    auto edgeIter = edgeSet.begin();
    auto edgesEnd = edgeSet.end();
    
    while (edgeIter != edgesEnd)
    {
        if (edgeIter->source == edgeIter->destination)
        {
            return true;
        }
        ++edgeIter;
    }
    
    return false;
}

vector<Edge>& EdgeSetBuilder::getEdgeSet()
{
    return edgeSet;
}

bool EdgeSetBuilder::isGraphDirected()
{
    return directedGraph;
}

bool EdgeSetBuilder::areNegativeEdgesAllowed()
{
    return negativeEdgesAllowed;
}

bool EdgeSetBuilder::areSelfLoopsAllowed()
{
    return selfLoopsAllowed;
}

unsigned long EdgeSetBuilder::getEdgeCount()
{
    return edgeSet.size();
}

void EdgeSetBuilder::createAndAppendEdge(int newSource,
                                         int newDestination,
                                         double newWeight)
{
    // checks if edge is a self-loop.
    if (newSource == newDestination)
    {
        // checks if edges can be self-loops.
        if (!selfLoopsAllowed)
        {
            // ignore this edge in the graph.
            return;
        }
    }
    
    // checks if edge has a negative weight.
    if (newWeight < 0)
    {
        // checks if edges can have negative weights.
        if (!negativeEdgesAllowed)
        {
            // ignore this edge in the graph.
            return;
        }
    }
    
    // add the edge to the edge set.
    edgeSet.emplace_back(newSource, newDestination, newWeight);
    
    // check if the reversed edge must be added to the edge set.
    if (!directedGraph)
    {
        // add the reversed edge.
        edgeSet.emplace_back(newDestination, newSource, newWeight);
    }
}



















