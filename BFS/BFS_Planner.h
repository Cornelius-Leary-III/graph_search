//
// Created by carpenter on 2/1/19.
//

#ifndef BFS_BFS_PLANNER_H
#define BFS_BFS_PLANNER_H

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

class BFS_Planner
{
public:
    
    /* CONSTRUCTOR(S) & DESTRUCTOR */
    BFS_Planner();
    ~BFS_Planner() = default;
    
    
    /* SETUP PUBLIC METHODS */
    void importGraphToAdjList(const string& fileName);
    void processGraphSetupHeaderOnly(const string& fileName);
    void setStartNode(const string& newStartNodeName);
    void setGoalNode(const string& newGoalNodeName);
    //    void addNodeToAdjList(const string& newNodeName);
    
    
    /* SEARCH PUBLIC METHODS */
    bool searchForGoal();
    
    
    /* ACCESSOR PUBLIC METHODS */
    bool hasGoalBeenReached();
    int getInputTotalNumberOfNodes();
    int getSizeOfAdjList();
    string getStartNode();
    string getGoalNode();

    
private:
    
    /* SETUP PRIVATE METHODS */
    void processFirstThreeLinesOfGraphFile(istream& inputStream);
    static string getSetupStringValue(istream& input);
    
    
    /* EDGE-PROCESSING PRIVATE METHODS */
    void updateNodesAndEdges(istream& inputStream);
    void processEdge(const string& edgeToProcess);
    void addEdgeToAdjList(const string& source, const string& destination, double edgeWeight);
    
    
    /* NODE-LOOKUP PRIVATE METHODS */
    bool isNodeInGraph(const string& nodeToCheck);
    bool hasNodeBeenVisited(const string& nodeToCheck);
    
    
    /* NODE-PROCESSING PRIVATE METHODS */
    void processFrontNode();
    void enqueueNeighbors();
    void addNodeToVisitedStateMap(const string& nodeName);
    void updateNodeVisitedState(const string& nodeToMark);
    //    void addNodeToCostMap(const string& nodeName);
    
    
private:
    
    queue<string> openNodeSet;
    map<string, vector<pair<string, double>>> adjacencyList;
    map<string, bool> visitedStateMap;
    
    
    //    map<string, double> costToReachNodeMap;
    //    double currentCost;
    //    string previousNode;
    
    
    int inputTotalNumNodes;
    string startNode;
    string currentNode;
    string goalNode;
    bool goalReached;
    
    //    vector<string> finalPath;
};


#endif //BFS_BFS_PLANNER_H
