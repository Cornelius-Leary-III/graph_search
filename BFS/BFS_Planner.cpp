//
// Created by carpenter on 2/1/19.
//

#include <iostream>
#include "BFS_Planner.h"

BFS_Planner::BFS_Planner()
   : inputTotalNumNodes{0},
     //          currentCost(0.0),
     goalReached{false},
     openNodeSet{},
     adjacencyList{},
     visitedStateMap{},
     startNode{},
     currentNode{},
     goalNode{}
{
}

void BFS_Planner::importGraphToAdjList(const string& fileName)
{
   // open file.
   ifstream input(fileName);

   // check if file has been opened.
   if (!input.is_open())
   {
      return;
   }

   // process the header section of the file.
   processFirstThreeLinesOfGraphFile(input);

   // process the edges from the file.
   updateNodesAndEdges(input);

   // close file.
   input.close();
}

void BFS_Planner::processGraphSetupHeaderOnly(const string& fileName)
{
   // open file.
   ifstream input(fileName);

   // check if file has been opened.
   if (!input.is_open())
   {
      return;
   }

   // process the header section of the file.
   processFirstThreeLinesOfGraphFile(input);

   // close file.
   input.close();
}

void BFS_Planner::processFirstThreeLinesOfGraphFile(istream& inputStream)
{
   // obtain these setup values:
   //      1) # of nodes in graph
   //      2) the start node name
   //      3) the goal node name

   // syntax file: each value is on its own line.

   int valueCount = 0;
   while (valueCount < 3)
   {
      // parse the setup value on the current line.
      string temp = getSetupStringValue(inputStream);

      // check if the setup function returned an empty string
      //      --> returns an empty string if no value was on that line.
      //      --> returns an empty string if there is additional information on the line.
      //      --> returns the actual value as a string, otherwise.
      if (!temp.empty())
      {
         if (valueCount == 0)
         {
            inputTotalNumNodes = std::stoi(temp);
         }
         else if (valueCount == 1)
         {
            startNode = temp;
         }
         else if (valueCount == 2)
         {
            goalNode = temp;
         }
      }
      else
      {
         // string was empty, so the file does not have the correct syntax.
         return;
      }

      ++valueCount;
   }
}

string BFS_Planner::getSetupStringValue(istream& input)
{
   string currentLine;
   string value;

   // obtain the current line from the file.
   if (std::getline(input, currentLine, '\n'))
   {
      // setting found.
      stringstream ss;
      ss << currentLine;

      // save the first value.
      if (ss >> value)
      {
         string temp;

         // check if additional value is on same line of file.
         if (ss >> temp)
         {
            // there is additional information on the line.
            return string();
         }
      }
      // value found AND no additional info on the same line.
   }

   return value;
}

void BFS_Planner::updateNodesAndEdges(istream& inputStream)
{
   string tempLine;

   // get the next line.
   while (std::getline(inputStream, tempLine))
   {
      // check if line is empty.
      if (tempLine.empty())
      {
         continue;
      }

      // process the current edge.
      processEdge(tempLine);
   }
}

void BFS_Planner::processEdge(const string& edgeToProcess)
{
   // pass the entire edge data string into the stream.
   stringstream ss;
   ss << edgeToProcess;

   // parse the source node name from the edge data.
   string sourceNodeName;
   ss >> sourceNodeName;

   // update the set of nodes.
   addNodeToVisitedStateMap(sourceNodeName);
   //    addNodeToCostMap(sourceNodeName);

   // parse the destination node name from the edge data.
   string destinationNodeName;
   ss >> destinationNodeName;

   // parse the weight from the edge data.
   string weightString;
   ss >> weightString;

   // convert the weight to a double value.
   double edgeWeight = std::stod(weightString);

   // add the edge to the adjacency list.
   addEdgeToAdjList(sourceNodeName, destinationNodeName, edgeWeight);
}

void BFS_Planner::addNodeToVisitedStateMap(const string& nodeName)
{
   visitedStateMap.emplace(nodeName, false);
}

// void BFS_Planner::addNodeToCostMap(const string& nodeName)
//{
//    costToReachNodeMap.emplace(nodeName, INFINITY);
//}

void BFS_Planner::addEdgeToAdjList(const string& source,
                                   const string& destination,
                                   double        edgeWeight)
{
   // look up the source node.
   auto findNodeIter = adjacencyList.find(source);
   auto findNodesEnd = adjacencyList.end();

   if (findNodeIter != findNodesEnd)
   {
      // the source exists in the adjacency list.

      // add the current edge to the source's edge list.
      findNodeIter->second.emplace_back(destination, edgeWeight);
   }
   else
   {
      // the source must be added to the adjacency list.

      // make the edge pair.
      pair<string, double> newEdge = make_pair(destination, edgeWeight);

      // make a new edge list.
      vector<pair<string, double>> newEdgeVector{newEdge};

      // add the edge list to the adjacency list.
      adjacencyList.emplace(source, newEdgeVector);
   }
}

bool BFS_Planner::searchForGoal()
{
   // check if the starting node exists in the imported graph.
   if (!isNodeInGraph(startNode))
   {
      return false;
   }

   // check if the goal node exists in the imported graph.
   if (!isNodeInGraph(goalNode))
   {
      return false;
   }

   // push the starting node onto the open set queue.
   openNodeSet.push(startNode);

   // loop until the:
   //      --> the open set queue is empty OR
   //      --> the goal has been reached
   while (!openNodeSet.empty() && !goalReached)
   {
      // process the node at the front of the open set queue.
      processFrontNode();

      // remove the front node.
      openNodeSet.pop();
   }

   return goalReached;
}

void BFS_Planner::processFrontNode()
{
   // get the front of the open set queue.
   currentNode = openNodeSet.front();

   // check if the goal has been reached.
   if (currentNode == goalNode)
   {
      goalReached = true;
      return;
   }

   // check if the current node has been visited already.
   if (!hasNodeBeenVisited(currentNode))
   {
      // update the visited state of the current node.
      updateNodeVisitedState(currentNode);

      // add the neighbors of the current node to the open set queue.
      enqueueNeighbors();

      //        previousNode = currentNode;
      //        finalPath.push_back(currentNode);
   }
}

void BFS_Planner::updateNodeVisitedState(const string& nodeToMark)
{
   auto findNodeIter = visitedStateMap.find(nodeToMark);
   if (findNodeIter != visitedStateMap.end())
   {
      findNodeIter->second = true;
   }
}

void BFS_Planner::enqueueNeighbors()
{
   // find the current node in the adjacency list.
   auto currentNodeIter = adjacencyList.find(currentNode);
   if (currentNodeIter != adjacencyList.end())
   {
      auto edgeList = currentNodeIter->second;
      auto edgeIter = edgeList.begin();
      auto edgesEnd = edgeList.end();

      // add each unvisited neighbor to the open set queue.
      while (edgeIter != edgesEnd)
      {
         if (!hasNodeBeenVisited(edgeIter->first))
         {
            openNodeSet.push(edgeIter->first);
         }

         ++edgeIter;
      }
   }
}

bool BFS_Planner::hasNodeBeenVisited(const string& nodeToCheck)
{
   auto findNodeIter = visitedStateMap.find(nodeToCheck);
   if (findNodeIter != visitedStateMap.end())
   {
      return findNodeIter->second;
   }

   // TODO:
   //  (02/01/19) add exception(s) here to handle case where node isn't in visitedStateMap.
   return true;
}

bool BFS_Planner::isNodeInGraph(const string& nodeToCheck)
{
   auto nodeFindEnd = adjacencyList.end();

   return (adjacencyList.find(nodeToCheck) != nodeFindEnd);
}

void BFS_Planner::setStartNode(const string& newStartNodeName)
{
   startNode = newStartNodeName;
}

void BFS_Planner::setGoalNode(const string& newGoalNodeName)
{
   goalNode = newGoalNodeName;
}

bool BFS_Planner::hasGoalBeenReached()
{
   return goalReached;
}

int BFS_Planner::getInputTotalNumberOfNodes()
{
   return inputTotalNumNodes;
}

int BFS_Planner::getSizeOfAdjList()
{
   return static_cast<int>(adjacencyList.size());
}

string BFS_Planner::getStartNode()
{
   return startNode;
}

string BFS_Planner::getGoalNode()
{
   return goalNode;
}
