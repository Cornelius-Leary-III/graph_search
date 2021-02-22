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

#include "Edge.h"

class EdgeSetBuilder
{
   public:
   EdgeSetBuilder();

   EdgeSetBuilder(bool is_graph_directed,
                  bool are_negative_edge_weights_allowed,
                  bool are_self_loops_allowed);

   EdgeSetBuilder(const std::vector<Edge>& edges, bool directedGraphState = true);

   EdgeSetBuilder(const EdgeSetBuilder& edge_set_builder_to_copy);

   void createAndAppendEdge(const std::string& new_source,
                            const std::string& new_destination,
                            double             new_weight = 1.00);

   std::vector<Edge>& getEdgeSet();
   bool               isGraphDirected();
   bool               areNegativeEdgesAllowed();
   bool               areSelfLoopsAllowed();
   unsigned long      getEdgeCount();

   // figure out how to incorporate Euclidean coordinates in edge representation.

   EdgeSetBuilder& operator=(const EdgeSetBuilder& rhs);

   private:
   void addEdgesForUndirectedGraph(const std::vector<Edge>& edges);
   bool checkForNegativeEdges();
   bool checkForSelfLoops();

   private:
   std::vector<Edge> mEdgeSet;
   bool              mAreNegativeEdgeWeightsAllowed;
   bool              mAreSelfLoopsAllowed;
   bool              mIsGraphDirected;
};

#endif // DIJKSTRAS_ALG_EDGESETBUILDER_H
