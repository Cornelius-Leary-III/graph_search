//
// Created by carpenter on 2/11/19.
//

#ifndef DIJKSTRAS_ALG_DIJKSTRAS_ALG_H
#define DIJKSTRAS_ALG_DIJKSTRAS_ALG_H

#include <values.h>
#include <vector>
#include <queue>
#include <iostream>
#include <string>

#include "EdgeSetBuilder.h"

using std::vector;
using std::queue;
using std::priority_queue;
using std::cout;
using std::endl;
using std::string;

using std::pair;
using std::make_pair;

using node = pair<double, int>;
using adjListNode = pair<int, double>;

class NegativeEdgeWeightsException : public std::exception
{
public:

    const char * what() noexcept
    {
        return "\nERROR: Dijkstra's Algorithm does not allow negative edge weights.\n\nProgram terminating.";
    }

};

class Dijkstras_Alg
{
public:
    
    explicit Dijkstras_Alg(unsigned long numberOfNodes);
    
    void addEdges(const vector<Edge>& edges);
    void compute(int sourceVertex);
    void resetThenCompute(int sourceVertex);
    vector<int> resetThenGetPathFromStartToNode(int start, int end);
    
    double getDistanceFromStartToNode(int start, int end);
    vector<int> getPathFromStartToNode(int start, int end);
    
    priority_queue<node>& getUnvisitedVertices();
    vector<double>& getDistanceTable();
    vector<int>& getPredecessorTable();
    vector<Edge>& getEdgeSet();
    
    void resetAll();
    
private:
    bool isEdgeSetZeroBased();
    void makeEdgeSetZeroBased();
    void buildAdjacencyList();
    void processCurrentNode(int name);
    
    void resetVisitedTable();
    void resetDistanceTable();
    void resetPredecessorTable();
    void resetOpenSet();
    
    vector<bool> visitedTable;
    priority_queue<node> openSet;
    vector<vector<adjListNode>> adjList;
    
    vector<double> distanceTable;
    vector<int> predecessorTable;
    vector<Edge> edgeSet;
    unsigned long nodeCount;
};


#endif //DIJKSTRAS_ALG_DIJKSTRAS_ALG_H










