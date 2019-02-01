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
    explicit Graph(bool graphIsDirectedState);
    
    ~Graph() = default;
    
    vector<GraphNode>& getNodeList();
    map<string, vector<GraphEdge>>& getAdjacencyList();
    bool isGraphDirected();
    unsigned long getNodeCount();
    
    void addNode(GraphNode& newGraphNode);
    void addEdge(GraphEdge& newGraphEdge);
    
    // check if node is in nodeList
    // get node neighbors
    // remove node.
    // remove edge.
    //    void setNodeList(const vector<GraphNode>& newNodeList);
    //    void setAdjacencyList(const map<string, vector<GraphEdge>>& newAdjList);

private:
    
    void addEdgeDirected(GraphEdge& newGraphEdge);
    void addEdgeUndirected(GraphEdge& newGraphEdge);

private:
    vector<GraphNode> nodeList;
    map<string, vector<GraphEdge>> adjacencyList;
    bool graphIsDirected;
};


#endif //BREADTH_FIRST_SEARCH_HOMEMADE_GRAPH_H
