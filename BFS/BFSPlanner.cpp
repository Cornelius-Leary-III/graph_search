//
// Created by carpenter on 2/1/19.
//

#include <iostream>
#include "BFSPlanner.h"

BFSPlanner::BFSPlanner()
        : inputTotalNumNodes(0), goalReached(false)
{
}

void BFSPlanner::importGraphToAdjList(const string& fileName)
{
    ifstream input(fileName);
    
    if (!input.is_open())
    {
        return;
    }
    
    processFirstThreeLinesOfGraphFile(input);
    updateNodesAndEdges(input);
    
    input.close();
}

void BFSPlanner::processGraphSetupHeaderOnly(const string& fileName)
{
    ifstream input(fileName);
    
    if (!input.is_open())
    {
        return;
    }
    
    processFirstThreeLinesOfGraphFile(input);
    
    input.close();
}

void BFSPlanner::processFirstThreeLinesOfGraphFile(istream& inputStream)
{
    string temp;
    
    inputStream >> temp;
    inputTotalNumNodes = std::stoi(temp);
    temp.clear();
    
    inputStream >> startNode;
    inputStream >> goalNode;
    std::getline(inputStream, temp, '\n');
}

void BFSPlanner::updateNodesAndEdges(istream& inputStream)
{
    string tempLine;
    
    while (std::getline(inputStream, tempLine))
    {
        if (tempLine.empty())
        {
            continue;
        }
        
        processEdge(tempLine);
    }
}

void BFSPlanner::processEdge(const string& edgeToProcess)
{
    stringstream ss;
    ss << edgeToProcess;
    
    string sourceNodeName;
    ss >> sourceNodeName;
    
    addNodeToVisitedStateMap(sourceNodeName);
    
    string destinationNodeName;
    ss >> destinationNodeName;
    
    string weightString;
    ss >> weightString;
    double edgeWeight = std::stod(weightString);
    
    addEdgeToAdjList(sourceNodeName, destinationNodeName, edgeWeight);
}

void BFSPlanner::addNodeToVisitedStateMap(const string& nodeName)
{
    visitedStateMap.emplace(nodeName, false);
}

void BFSPlanner::addEdgeToAdjList(const string& source,
                                  const string& destination,
                                  double edgeWeight)
{
    auto findNodeIter = adjacencyList.find(source);
    auto findNodesEnd = adjacencyList.end();
    if (findNodeIter != findNodesEnd)
    {
        findNodeIter->second.emplace_back(destination, edgeWeight);
    }
    else
    {
        pair<string, double> newEdge = make_pair(destination, edgeWeight);
        vector<pair<string, double>> newEdgeVector{newEdge};
        adjacencyList.emplace(source, newEdgeVector);
    }
}

bool BFSPlanner::searchForGoal()
{
    if (!isNodeInGraph(startNode))
    {
        return false;
    }
    
    if (!isNodeInGraph(goalNode))
    {
        return false;
    }
    
    openNodeSet.push(startNode);
    
    while (!openNodeSet.empty() || !goalReached)
    {
        processFrontNode();
        
        openNodeSet.pop();
    }
    
    return true;
}

void BFSPlanner::processFrontNode()
{
    currentNode = openNodeSet.front();
    
    if (currentNode == goalNode)
    {
        goalReached = true;
        return;
    }
    
    if (!hasNodeBeenVisited(currentNode))
    {
        updateNodeVisitedState(currentNode);
        enqueueNeighbors();
    }
}

void BFSPlanner::updateNodeVisitedState(const string& nodeToMark)
{
    auto findNodeIter = visitedStateMap.find(nodeToMark);
    if (findNodeIter != visitedStateMap.end())
    {
        findNodeIter->second = true;
    }
}

void BFSPlanner::enqueueNeighbors()
{
    auto currentNodeIter = adjacencyList.find(currentNode);
    if (currentNodeIter != adjacencyList.end())
    {
        auto edgeList = currentNodeIter->second;
        auto edgeIter = edgeList.begin();
        auto edgesEnd = edgeList.end();
        
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

bool BFSPlanner::hasNodeBeenVisited(const string& nodeToCheck)
{
    auto findNodeIter = visitedStateMap.find(nodeToCheck);
    if (findNodeIter != visitedStateMap.end())
    {
        return findNodeIter->second;
    }
    
    //TODO:
    //  (02/01/19) add exception(s) here to handle case where node isn't in visitedStateMap.
    return true;
}

void BFSPlanner::setStartNode(const string& newStartNodeName)
{
    startNode = newStartNodeName;
}

void BFSPlanner::setGoalNode(const string& newGoalNodeName)
{
    goalNode = newGoalNodeName;
}

bool BFSPlanner::hasGoalBeenReached()
{
    return goalReached;
}

int BFSPlanner::getInputTotalNumberOfNodes()
{
    return inputTotalNumNodes;
}

int BFSPlanner::getSizeOfAdjList()
{
    return static_cast<int>(adjacencyList.size());
}

bool BFSPlanner::isNodeInGraph(const string& nodeToCheck)
{
    auto nodeFindEnd = adjacencyList.end();
    
    return (adjacencyList.find(nodeToCheck) != nodeFindEnd);
}