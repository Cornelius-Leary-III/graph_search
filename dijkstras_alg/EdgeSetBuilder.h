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

using std::endl;
using std::ifstream;
using std::istream;
using std::ostream;
using std::string;
using std::stringstream;
using std::vector;

class EdgeSetBuilder
{
   public:
   EdgeSetBuilder();

   EdgeSetBuilder(bool is_graph_directed,
                  bool are_negative_edge_weights_allowed,
                  bool are_self_loops_allowed);

   EdgeSetBuilder(const vector<Edge>& edges, bool directedGraphState = true);

   EdgeSetBuilder(const EdgeSetBuilder& edge_set_builder_to_copy);

   void createAndAppendEdge(int new_source, int new_destination, double new_weight = 1.00);

   vector<Edge>& getEdgeSet();
   bool          isGraphDirected();
   bool          areNegativeEdgesAllowed();
   bool          areSelfLoopsAllowed();
   unsigned long getEdgeCount();

   // figure out how to incorporate Euclidean coordinates in edge representation.

   EdgeSetBuilder& operator=(const EdgeSetBuilder& rhs);

   private:
   void addEdgesForUndirectedGraph(const vector<Edge>& edges);
   bool checkForNegativeEdges();
   bool checkForSelfLoops();

   private:
   vector<Edge> mEdgeSet;
   bool         mAreNegativeEdgeWeightsAllowed;
   bool         mAreSelfLoopsAllowed;
   bool         mIsGraphDirected;
};

#endif // DIJKSTRAS_ALG_EDGESETBUILDER_H
