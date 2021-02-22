//
// Created by carpenter on 2/11/19.
//

#include "Dijkstras_Alg.h"

Dijkstras_Alg::Dijkstras_Alg(unsigned long number_of_nodes)
   : /*mVisitedTable(number_of_nodes, false),*/
     mOpenSet(),
     mAdjList(),
     mDistanceTable(),
     mPredecessorTable(),
     //     mAdjList(number_of_nodes, std::vector<adjListNode>()),
     //     mDistanceTable(number_of_nodes, MAXDOUBLE),
     //     mPredecessorTable(number_of_nodes, -1),
     mEdgeSet(),
     mNodeCount(number_of_nodes)
{
}

void Dijkstras_Alg::compute(const std::string& source_vertex)
{
   // check if the source node is too large or a negative #.
   auto find_iter = mDistanceTable.find(source_vertex);
   auto find_end  = mDistanceTable.end();

   if (find_iter == find_end)
   {
      throw StartNodeProvidedIsNonExistentException();
   }

   // set the distance to the source node from the source node to be 0.
   //   mDistanceTable.(source_vertex, 0);
   find_iter->second = 0;

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

void Dijkstras_Alg::processCurrentNode(const std::string& name)
{
   // process each neighbor of the provided node.
   for (auto& neighbor : mAdjList[name])
   {
      std::string neighbor_name = neighbor.first;

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

std::vector<std::string> Dijkstras_Alg::getPathFromStartToNode(const std::string& start,
                                                               const std::string& end)
{
   // TODO: (04/24/19)
   //      either:
   //          * reimplement the reset() methods I had in a previous version.
   //          * remove the call to the compute() module here.

   // compute the distances using the provided start node.
   compute(start);

   std::vector<std::string> back_tracing_path;

   auto find_iter = mPredecessorTable.find(end);
   auto find_end  = mPredecessorTable.end();

   // check that the end node provided is within the graph.
   if (find_iter != find_end)
   {
      // begin at the end node
      std::string back_tracking_node_name = end;

      // continue until the index is:
      //      * at the start node provided
      //      * at a dead-end (== -1)
      while (back_tracking_node_name != start && !back_tracking_node_name.empty())
      {
         // add the current index (which doubles as the node name) to the path.
         back_tracing_path.push_back(back_tracking_node_name);

         // advance to the next predecessor.
         back_tracking_node_name = mPredecessorTable[back_tracking_node_name];
      }

      // add the final index to the path.
      back_tracing_path.push_back(back_tracking_node_name);
   }

   // reverse the path; goes from start node to goal node.
   return std::vector<std::string>(back_tracing_path.rbegin(), back_tracing_path.rend());
}

void Dijkstras_Alg::addEdges(const std::vector<Edge>& edges)
{
   mEdgeSet = edges;

   buildAdjacencyList();
}

std::map<std::string, std::map<std::string, double>>& Dijkstras_Alg::getAdjacencyList()
{
   return mAdjList;
}

std::priority_queue<node>& Dijkstras_Alg::getUnvisitedVertices()
{
   return mOpenSet;
}

std::map<std::string, double>& Dijkstras_Alg::getDistanceTable()
{
   return mDistanceTable;
}

std::map<std::string, std::string>& Dijkstras_Alg::getPredecessorTable()
{
   return mPredecessorTable;
}

// std::vector<bool>& Dijkstras_Alg::getVisitedTable()
//{
//   return mVisitedTable;
//}

std::vector<Edge>& Dijkstras_Alg::getEdgeSet()
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

      auto source_iter = mAdjList.find(edge.mSource.mName);
      auto sources_end = mAdjList.end();

      if (source_iter != sources_end)
      {
         source_iter->second.emplace(edge.mDestination.mName, edge.mWeight);
      }
      else
      {
         std::map<std::string, double> neighbor_to_source;
         neighbor_to_source.emplace(edge.mDestination.mName, edge.mWeight);

         mAdjList.emplace(edge.mSource.mName, neighbor_to_source);
      }
   }
}
