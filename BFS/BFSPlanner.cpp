//
// Created by carpenter on 2/1/19.
//

#include <iostream>
#include "BFSPlanner.h"

BFSPlanner::BFSPlanner()
        : totalNumberOfNodes(0), goalReached(false)
{
}

void BFSPlanner::importFileToAdjList(const string& fileName)
{
    ifstream input(fileName);
    
    if (!input.is_open())
    {
        return;
    }
    
    string temp;
    
    input >> temp;
    totalNumberOfNodes = std::stoi(temp);
    temp.clear();
    
    input >> startNode;
    input >> goalNode;
    std::getline(input, temp, '\n');
    
    string tempLine;
    
    auto adjListEnd = adjacencyList.end();
    
    while (std::getline(input, tempLine))
    {
        if (tempLine.empty())
        {
            continue;
        }
        
        addEdge(tempLine);
    }
}

void BFSPlanner::addEdge(const string& edgeToProcess)
{
    stringstream ss;
    ss << edgeToProcess;
    
    string sourceNodeName;
    ss >> sourceNodeName;
    
    string destinationNodeName;
    ss >> destinationNodeName;
    
    string weightString;
    ss >> weightString;
    double edgeWeight = std::stod(weightString);
    
    insertEdgeIntoAdjList(sourceNodeName, destinationNodeName, edgeWeight);
}

void BFSPlanner::insertEdgeIntoAdjList(const string& source,
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

bool BFSPlanner::isNodeInGraph(const string& nodeToCheck)
{
    auto nodeFindEnd = adjacencyList.end();
    
    return (adjacencyList.find(nodeToCheck) != nodeFindEnd);
}