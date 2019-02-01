//
// Created by carpenter on 1/28/19.
//

#include <values.h>
#include "BreadthFirstSearchPlanner.h"

BreadthFirstSearchPlanner::BreadthFirstSearchPlanner()
        : goalReached(false)
{
}

void BreadthFirstSearchPlanner::setStartNode(GraphNode& newStartNode)
{
    startNode = newStartNode;
}

void BreadthFirstSearchPlanner::setGraph(Graph& newGraph)
{
    graph = newGraph;
    
    importNodes(graph);
}

void BreadthFirstSearchPlanner::importNodes(Graph& newGraph)
{
    auto nodeList = graph.getNodeList();
    
    auto nodeIter = nodeList.begin();
    auto nodesEnd = nodeList.end();
    
    while (nodeIter != nodesEnd)
    {
        string nodeName = nodeIter->getNodeName();
        visitedNodesSet.emplace(nodeName, false);
        
        ++nodeIter;
    }
}

bool BreadthFirstSearchPlanner::hasGoalBeenReached()
{
    return goalReached;
}

GraphNode& BreadthFirstSearchPlanner::getStartNode()
{
    return startNode;
}

string BreadthFirstSearchPlanner::getStartNodeName()
{
    return startNode.getNodeName();
}

bool BreadthFirstSearchPlanner::checkIfNodeIsInGoalSet(GraphNode& nodeToCheck)
{
    auto goalNodeIter = goalNodesSet.begin();
    auto goalNodesEnd = goalNodesSet.end();
    
    while (goalNodeIter != goalNodesEnd)
    {
        if (nodeToCheck == *goalNodeIter)
        {
            goalReached = true;
            return true;
        }
        
        ++goalNodeIter;
    }
    
    return false;
}

void BreadthFirstSearchPlanner::searchForGoal()
{
    currentNodeName = startNode.getNodeName();
    
    auto visitedNodeFindIter = visitedNodesSet.find(currentNodeName);
    if (visitedNodeFindIter != visitedNodesSet.end())
    {
        visitedNodeFindIter->second = true;
        
        
    }
    else
    {
        goalReached = false;
    }
}

//
//BreadthFirstSearchPlanner::~BreadthFirstSearchPlanner()
//{
//}
//bool BreadthFirstSearchPlanner::hasGoalBeenReached()
//{
//    return true;
//}
//
//vector<int>& BreadthFirstSearchPlanner::recoverFinalPath()
//{
//    return finalPath;
//}
//


//void BreadthFirstSearchPlanner::setGoalNodesSet()
//{
//}
//
