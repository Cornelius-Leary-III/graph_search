//
// Created by carpenter on 2/12/19.
//

#include "EdgeSetBuilder.h"

EdgeSetBuilder::EdgeSetBuilder()
   : mEdgeSet(),
     mAreNegativeEdgeWeightsAllowed(false),
     mAreSelfLoopsAllowed(false),
     mIsGraphDirected(true)
{
}

EdgeSetBuilder::EdgeSetBuilder(bool is_graph_directed,
                               bool are_negative_edge_weights_allowed,
                               bool are_self_loops_allowed)
   : mEdgeSet(),
     mAreNegativeEdgeWeightsAllowed(are_negative_edge_weights_allowed),
     mAreSelfLoopsAllowed(are_self_loops_allowed),
     mIsGraphDirected(is_graph_directed)
{
}

EdgeSetBuilder::EdgeSetBuilder(const vector<Edge>& edges, bool is_graph_directed)
   : mIsGraphDirected{is_graph_directed}
{
   if (!mIsGraphDirected)
   {
      // add the reverse-edge when the graph is undirected.
      addEdgesForUndirectedGraph(edges);
   }
   else
   {
      // when the graph is directed, the edge set provided is used.
      mEdgeSet = edges;
   }

   // determine these graph traits from the provided edge set.
   mAreNegativeEdgeWeightsAllowed = checkForNegativeEdges();
   mAreSelfLoopsAllowed           = checkForSelfLoops();
}

EdgeSetBuilder::EdgeSetBuilder(const EdgeSetBuilder& edge_set_builder_to_copy)
   : mEdgeSet(edge_set_builder_to_copy.mEdgeSet),
     mAreNegativeEdgeWeightsAllowed(edge_set_builder_to_copy.mAreNegativeEdgeWeightsAllowed),
     mAreSelfLoopsAllowed(edge_set_builder_to_copy.mAreSelfLoopsAllowed),
     mIsGraphDirected(edge_set_builder_to_copy.mIsGraphDirected)
{
}

void EdgeSetBuilder::addEdgesForUndirectedGraph(const vector<Edge>& edges)
{
   auto edge_iter = edges.begin();
   auto edges_end = edges.end();

   vector<Edge> undirected_edges;

   while (edge_iter != edges_end)
   {
      // add the forward edge.
      undirected_edges.push_back(*edge_iter);

      // add the reverse edge.
      undirected_edges.emplace_back(edge_iter->mDestination,
                                    edge_iter->mSource,
                                    edge_iter->mWeight);

      ++edge_iter;
   }

   mEdgeSet = undirected_edges;
}

EdgeSetBuilder& EdgeSetBuilder::operator=(const EdgeSetBuilder& rhs)
{
   if (this != &rhs)
   {
      this->mEdgeSet                       = rhs.mEdgeSet;
      this->mIsGraphDirected               = rhs.mIsGraphDirected;
      this->mAreNegativeEdgeWeightsAllowed = rhs.mAreNegativeEdgeWeightsAllowed;
      this->mAreSelfLoopsAllowed           = rhs.mAreSelfLoopsAllowed;
   }

   return *this;
}

bool EdgeSetBuilder::checkForNegativeEdges()
{
   auto edge_iter = mEdgeSet.begin();
   auto edges_end = mEdgeSet.end();

   while (edge_iter != edges_end)
   {
      if (edge_iter->mWeight < 0)
      {
         return true;
      }

      ++edge_iter;
   }

   return false;
}

bool EdgeSetBuilder::checkForSelfLoops()
{
   auto edge_iter = mEdgeSet.begin();
   auto edges_end = mEdgeSet.end();

   while (edge_iter != edges_end)
   {
      if (edge_iter->mSource == edge_iter->mDestination)
      {
         return true;
      }

      ++edge_iter;
   }

   return false;
}

vector<Edge>& EdgeSetBuilder::getEdgeSet()
{
   return mEdgeSet;
}

bool EdgeSetBuilder::isGraphDirected()
{
   return mIsGraphDirected;
}

bool EdgeSetBuilder::areNegativeEdgesAllowed()
{
   return mAreNegativeEdgeWeightsAllowed;
}

bool EdgeSetBuilder::areSelfLoopsAllowed()
{
   return mAreSelfLoopsAllowed;
}

unsigned long EdgeSetBuilder::getEdgeCount()
{
   return mEdgeSet.size();
}

void EdgeSetBuilder::createAndAppendEdge(int new_source, int new_destination, double new_weight)
{
   // checks if edge is a self-loop.
   if (new_source == new_destination)
   {
      // checks if edges can be self-loops.
      if (!mAreSelfLoopsAllowed)
      {
         // ignore this edge in the graph.
         return;
      }
   }

   // checks if edge has a negative weight.
   if (new_weight < 0)
   {
      // checks if edges can have negative weights.
      if (!mAreNegativeEdgeWeightsAllowed)
      {
         // ignore this edge in the graph.
         return;
      }
   }

   // add the edge to the edge set.
   mEdgeSet.emplace_back(new_source, new_destination, new_weight);

   // check if the reversed edge must be added to the edge set.
   if (!mIsGraphDirected)
   {
      // add the reversed edge.
      mEdgeSet.emplace_back(new_destination, new_source, new_weight);
   }
}
