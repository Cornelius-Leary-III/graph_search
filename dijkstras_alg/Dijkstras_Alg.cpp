//
// Created by carpenter on 2/11/19.
//

#include "Dijkstras_Alg.h"

Dijkstras_Alg::Dijkstras_Alg(unsigned long number_of_nodes)
   : mVisitedTable(number_of_nodes, false),
     mOpenSet(),
     mAdjList(number_of_nodes, vector<adjListNode>()),
     mDistanceTable(number_of_nodes, MAXDOUBLE),
     mPredecessorTable(number_of_nodes, -1),
     mEdgeSet(),
     mNodeCount(number_of_nodes)
{
}

void Dijkstras_Alg::compute(int source_vertex)
{
   // check if the source node is too large or a negative #.
   if (source_vertex >= (int) mNodeCount || source_vertex < 0)
   {
      throw StartNodeProvidedIsNonExistentException();
   }

   // set the distance to the source node from the source node to be 0.
   mDistanceTable[source_vertex] = 0;

   // put the this edge into the open set queue.
   mOpenSet.emplace(mDistanceTable[source_vertex], source_vertex);

   // continue computing as long as there are still edges in the open set queue.
   while (!mOpenSet.empty())
   {
      // save and remove the top of the open set queue.
      auto current_node = mOpenSet.top();
      mOpenSet.pop();

      // process the top node.
      processCurrentNode(current_node.second);
   }
}

void Dijkstras_Alg::processCurrentNode(int name)
{
   // process each neighbor of the provided node.
   for (auto& neighbor : mAdjList[name])
   {
      int neighbor_name = neighbor.first;

      // compute the alternative path to this node:
      //      --> add the existing cost from the source node to the current node to the weight of
      //      the
      //              edge to the neighbor node.
      double alternate_path = mDistanceTable[name] + neighbor.second;

      // compare the cost of going from the source node to the neighbor node and
      //      the cost of going from the source node to the neighbor node via the current node.
      if (alternate_path < mDistanceTable[neighbor_name])
      {
         // traveling via the current node is a less-costly path, so update the distance and
         // predecessor tables to
         //      reflect the new best path.
         mDistanceTable[neighbor_name]    = alternate_path;
         mPredecessorTable[neighbor_name] = name;

         // add this neighbor and the new distance to the open set queue.
         mOpenSet.emplace(mDistanceTable[neighbor_name], neighbor_name);
      }
   }
}

vector<int> Dijkstras_Alg::getPathFromStartToNode(int start, int end)
{
   // TODO: (04/24/19)
   //      either:
   //          * reimplement the reset() methods I had in a previous version.
   //          * remove the call to the compute() module here.

   // compute the distances using the provided start node.
   compute(start);

   vector<int> back_tracing_path;

   // check that the end node provided is within the graph.
   if (end <= (int) mPredecessorTable.size())
   {
      // begin at the end node
      int back_tracing_index = end;

      // continue until the index is:
      //      * at the start node provided
      //      * at a dead-end (== -1)
      while (back_tracing_index != start && back_tracing_index != -1)
      {
         // add the current index (which doubles as the node name) to the path.
         back_tracing_path.push_back(back_tracing_index);

         // advance to the next predecessor.
         back_tracing_index = mPredecessorTable[back_tracing_index];
      }

      // add the final index to the path.
      back_tracing_path.push_back(back_tracing_index);
   }

   // reverse the path; goes from start node to goal node.
   return vector<int>(back_tracing_path.rbegin(), back_tracing_path.rend());
}

void Dijkstras_Alg::addEdges(const vector<Edge>& edges)
{
   mEdgeSet = edges;

   buildAdjacencyList();
}

vector<vector<adjListNode>>& Dijkstras_Alg::getAdjacencyList()
{
   return mAdjList;
}

priority_queue<node>& Dijkstras_Alg::getUnvisitedVertices()
{
   return mOpenSet;
}

vector<double>& Dijkstras_Alg::getDistanceTable()
{
   return mDistanceTable;
}

vector<int>& Dijkstras_Alg::getPredecessorTable()
{
   return mPredecessorTable;
}

vector<bool>& Dijkstras_Alg::getVisitedTable()
{
   return mVisitedTable;
}

vector<Edge>& Dijkstras_Alg::getEdgeSet()
{
   return mEdgeSet;
}

void Dijkstras_Alg::buildAdjacencyList()
{
   for (auto& edge : mEdgeSet)
   {
      if (edge.mWeight < 0)
      {
         throw NegativeEdgeWeightsException();
      }

      mAdjList[edge.mSource].emplace_back(edge.mDestination, edge.mWeight);
   }
}
