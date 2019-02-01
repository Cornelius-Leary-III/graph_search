//
// Created by carpenter on 1/28/19.
//

#ifndef BREADTH_FIRST_SEARCH_HOMEMADE_BREADTHFIRSTSEARCHPLANNER_H
#define BREADTH_FIRST_SEARCH_HOMEMADE_BREADTHFIRSTSEARCHPLANNER_H

#include <map>
#include <queue>
#include <vector>
#include <iostream>
#include <sstream>

#include "Graph.h"

using std::map;
using std::pair;
using std::make_pair;
using std::queue;
using std::vector;
using std::cout;
using std::endl;
using std::stringstream;


class BreadthFirstSearchPlanner
{
public:
    
    BreadthFirstSearchPlanner();
    
    ~BreadthFirstSearchPlanner() = default;
    
    void searchForGoal();
    
    string getStartNodeName();
    GraphNode& getStartNode();
    void setStartNode(GraphNode& newStartNode);
    void setGraph(Graph& newGraph);
    bool hasGoalBeenReached();
    
    //    void setGoalNodesSet();
    //    vector<int>& recoverFinalPath();

private:
    
    void importNodes(Graph& newGraph);
    bool checkIfNodeIsInGoalSet(GraphNode& nodeToCheck);

private:
    
    Graph graph;
    map<string, vector<GraphEdge>> adjList;
    
    string currentNodeName;
    
    queue<GraphNode> openSetQueue;
    map<string, bool> visitedNodesSet;
    map<string, double> costToGoalMap;
    vector<GraphNode> finalPath;
    GraphNode startNode;
    vector<GraphNode> goalNodesSet;
    bool goalReached;
};


#endif //BREADTH_FIRST_SEARCH_HOMEMADE_BREADTHFIRSTSEARCHPLANNER_H
