//
// Created by carpenter on 2/11/19.
//

#ifndef DIJKSTRAS_ALG_DIJKSTRAS_ALG_H
#define DIJKSTRAS_ALG_DIJKSTRAS_ALG_H

#include "EdgeImporter.h"

#include <values.h>
#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <string>

// please note the order in elements:
using node        = std::pair<double, std::string>;
using adjListNode = std::pair<std::string, double>;

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

   void addEdges(const std::vector<Edge>& edges);
   void compute(const std::string& source_vertex);

   std::vector<std::string> getPathFromStartToNode(const std::string& start,
                                                   const std::string& end);

   std::map<std::string, std::map<std::string, double>>& getAdjacencyList();
   std::priority_queue<node>&                            getUnvisitedVertices();
   std::map<std::string, double>&                        getDistanceTable();
   std::map<std::string, std::string>&                   getPredecessorTable();
   std::vector<Edge>&                                    getEdgeSet();
   //   std::vector<bool>&                     getVisitedTable();

   private:
   void buildAdjacencyList();
   void processCurrentNode(const std::string& name);

   private:
   //   std::vector<bool>                     mVisitedTable; // change me! (not in STL)
   std::priority_queue<node>                            mOpenSet;
   std::map<std::string, std::map<std::string, double>> mAdjList;

   std::map<std::string, double>      mDistanceTable;
   std::map<std::string, std::string> mPredecessorTable;
   std::vector<Edge>                  mEdgeSet;
   unsigned long                      mNodeCount;
};

#endif // DIJKSTRAS_ALG_DIJKSTRAS_ALG_H
