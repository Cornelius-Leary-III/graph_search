//
// Created by carpenter on 1/30/19.
//

#ifndef BREADTH_FIRST_SEARCH_HOMEMADE_GRAPH_H
#define BREADTH_FIRST_SEARCH_HOMEMADE_GRAPH_H

#include <map>
#include <vector>
#include <list>
#include <queue>
#include <sstream>

#include "GraphEdge.h"

using std::map;
using std::make_pair;
using std::vector;
using std::list;
using std::queue;
using std::stringstream;
using std::string;

class Graph
{
public:
    
    Graph();
    ~Graph() = default;
    
//    void setNodeList(const vector<GraphNode>& newNodeList);
//    void setAdjacencyList(const map<string, vector<GraphEdge>>& newAdjList);
    
    vector<GraphNode>& getNodeList();
    map<string, vector<GraphEdge>>& getAdjacencyList();
    
    unsigned long getNodeCount();
    bool isGraphDirected();
    
    void addNode(GraphNode& newGraphNode);
//    // remove node.
//
    void addEdge(GraphEdge& newGraphEdge);
//    // remove edge.
    
    
    
    // check if node is in nodeList
    // get node neighbors

private:
    
    vector<GraphNode> nodeList;
    map<string, vector<GraphEdge>> adjacencyList;
    
    void addEdgeDirected(GraphEdge& newGraphEdge);
    void addEdgeUndirected(GraphEdge& newGraphEdge);
    
    
    bool graphIsDirected;
    
};


#endif //BREADTH_FIRST_SEARCH_HOMEMADE_GRAPH_H
