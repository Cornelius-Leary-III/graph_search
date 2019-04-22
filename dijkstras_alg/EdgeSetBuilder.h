//
// Created by carpenter on 2/12/19.
//

#ifndef DIJKSTRAS_ALG_EDGESETBUILDER_H
#define DIJKSTRAS_ALG_EDGESETBUILDER_H

#include <vector>
#include <fstream>
#include <sstream>
#include <istream>
#include <ostream>

#include "Edge.h"

using std::vector;
using std::ifstream;
using std::istream;
using std::stringstream;
using std::string;
using std::ostream;
using std::endl;


class EdgeSetBuilder
{
public:
    
    EdgeSetBuilder();
    EdgeSetBuilder(bool directedGraphState,
                   bool negativeEdgesAllowedState,
                   bool selfLoopsAllowedState);
    explicit EdgeSetBuilder(const vector<Edge>& edges, bool directedGraphState = true);
    EdgeSetBuilder(const EdgeSetBuilder& edgeSetBuilderToCopy);
    
    void createAndAppendEdge(int newSource, int newDestination, double newWeight = 1.00);
    void readEdgesFromFile(const string& inputFile);
    
    vector<Edge>& getEdgeSet();
    bool isGraphDirected();
    bool areNegativeEdgesAllowed();
    bool areSelfLoopsAllowed();
    unsigned long getEdgeCount();
    // figure out how to incorporate Euclidean coordinates in edge representation.
    
    EdgeSetBuilder& operator=(const EdgeSetBuilder& rhs);

private:
    
    void processFirstThreeLinesOfGraphFile(istream& inputStream);
    void readInEdges(istream& inputStream);
    void processEdge(const string& edgeToProcess);
    void addEdgesForUndirectedGraph(const vector<Edge>& edges);
    
    bool checkForNegativeEdges();
    bool checkForSelfLoops();
    
    vector<Edge> edgeSet;
    bool negativeEdgesAllowed;
    bool selfLoopsAllowed;
    bool directedGraph;
    
    unsigned long numberOfNodes;
    int startNode;
    int goalNode;
};


#endif //DIJKSTRAS_ALG_EDGESETBUILDER_H


















