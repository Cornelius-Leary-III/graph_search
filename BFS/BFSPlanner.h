//
// Created by carpenter on 2/1/19.
//

#ifndef BFS_BFSPLANNER_H
#define BFS_BFSPLANNER_H

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <sstream>
#include <cmath>

using std::string;
using std::vector;
using std::map;
using std::pair;
using std::make_pair;
using std::queue;
using std::istream;
using std::ifstream;
using std::stringstream;

class BFSPlanner
{
public:
    
    BFSPlanner();
    ~BFSPlanner() = default;
    
    void importGraphToAdjList(const string& fileName);
    void processGraphSetupHeaderOnly(const string& fileName);
    void setStartNode(const string& newStartNodeName);
    void setGoalNode(const string& newGoalNodeName);
    
    //    void addNodeToAdjList(const string& newNodeName);
    bool searchForGoal();
    bool hasGoalBeenReached();
    int getInputTotalNumberOfNodes();
    int getSizeOfAdjList();
    string getStartNode();
    string getGoalNode();

private:
    
    void processFirstThreeLinesOfGraphFile(istream& inputStream);
    void updateNodesAndEdges(istream& inputStream);
    bool isNodeInGraph(const string& nodeToCheck);
    void processEdge(const string& edgeToProcess);
    void addEdgeToAdjList(const string& source,
                          const string& destination,
                          double edgeWeight);
    void addNodeToVisitedStateMap(const string& nodeName);
    void addNodeToCostMap(const string& nodeName);
    void processFrontNode();
    void enqueueNeighbors();
    bool hasNodeBeenVisited(const string& nodeToCheck);
    void updateNodeVisitedState(const string& nodeToMark);

private:
    
    queue<string> openNodeSet;
    map<string, vector<pair<string, double>>> adjacencyList;
    map<string, bool> visitedStateMap;
    map<string, double> costToReachNodeMap;
    int inputTotalNumNodes;
    string startNode;
    string currentNode;
    double currentCost;
    string previousNode;
    string goalNode;
    bool goalReached;
    
    vector<string> finalPath;
};


#endif //BFS_BFSPLANNER_H
