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

using std::string;
using std::vector;
using std::map;
using std::pair;
using std::make_pair;
using std::queue;
using std::ifstream;
using std::stringstream;

class BFSPlanner
{
public:
    
    BFSPlanner();
    ~BFSPlanner() = default;
    
    void importFileToAdjList(const string& fileName);
    
    void setStartNode(const string& newStartNodeName);
    void setGoalNode(const string& newGoalNodeName);
    
    //    void addNodeToAdjList(const string& newNodeName);
    
    //    void searchForGoal();
    bool hasGoalBeenReached();

private:
    
    bool isNodeInGraph(const string& nodeToCheck);
    void addEdge(const string& edgeToProcess);
    void insertEdgeIntoAdjList(const string& source,
                               const string& destination,
                               double edgeWeight);
    //    void processNode();

private:
    
    queue<string> openNodeSet;
    map<string, vector<pair<string, double>>> adjacencyList;
    
    int totalNumberOfNodes;
    string startNode;
    string currentNode;
    string goalNode;
    bool goalReached;
};


#endif //BFS_BFSPLANNER_H
