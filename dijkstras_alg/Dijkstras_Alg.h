//
// Created by carpenter on 2/11/19.
//

#ifndef DIJKSTRAS_ALG_DIJKSTRAS_ALG_H
#define DIJKSTRAS_ALG_DIJKSTRAS_ALG_H

#include <values.h>
#include <vector>
#include <queue>
#include <iostream>
#include <string>

#include "EdgeImporter.h"

using std::cout;
using std::endl;
using std::priority_queue;
using std::queue;
using std::string;
using std::vector;

using std::make_pair;
using std::pair;

// please note the order in elements:
using node        = pair<double, int>;
using adjListNode = pair<int, double>;

class NegativeEdgeWeightsException : public std::exception
{
   public:
   const char* what() noexcept
   {
      return "\nERROR: Dijkstra's Algorithm does not allow negative edge weights.\n\nProgram "
             "terminating.";
   }
};

class StartNodeProvidedIsNonExistentException : public std::exception
{
   public:
   const char* what() noexcept
   {
      return "\nERROR: Start node must be one of the nodes in the graph.\n\nProgram terminating.";
   }
};

class Dijkstras_Alg
{
   public:
   explicit Dijkstras_Alg(unsigned long number_of_nodes);

   void addEdges(const vector<Edge>& edges);
   void compute(int source_vertex);

   vector<int> getPathFromStartToNode(int start, int end);

   vector<vector<adjListNode>>& getAdjacencyList();
   priority_queue<node>&        getUnvisitedVertices();
   vector<double>&              getDistanceTable();
   vector<int>&                 getPredecessorTable();
   vector<bool>&                getVisitedTable();
   vector<Edge>&                getEdgeSet();

   private:
   void buildAdjacencyList();
   void processCurrentNode(int name);

   private:
   vector<bool>                mVisitedTable; // change me! (not in STL)
   priority_queue<node>        mOpenSet;
   vector<vector<adjListNode>> mAdjList;

   vector<double> mDistanceTable;
   vector<int>    mPredecessorTable;
   vector<Edge>   mEdgeSet;
   unsigned long  mNodeCount;
};

#endif // DIJKSTRAS_ALG_DIJKSTRAS_ALG_H
