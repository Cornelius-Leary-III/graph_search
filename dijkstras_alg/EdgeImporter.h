//
// Created by cornelius on 4/23/19.
//

#ifndef DIJKSTRAS_ALG_EDGEIMPORTER_H
#define DIJKSTRAS_ALG_EDGEIMPORTER_H

#include "EdgeSetBuilder.h"

class EdgeImporter
{
public:
    
    explicit EdgeImporter(string newFileToReadFrom);
    
    bool isFileValid();
    
    vector<Edge>& getEdges();
    int getStartNode();
    int getGoalNode();
    unsigned long getNumberOfNodes();
    
    void setupEdgeBuilder(bool isDirected = true,
                          bool canHaveNegWeights = true,
                          bool canHaveSelfLoops = true);
    void readGraphFile();


private:
    
    void processFirstThreeLinesOfGraphFile();
    string getSetupStringValue();
    
    void importEdges();
    void processCurrentEdgeInFile(const string& edgeToProcess);


private:
    
    EdgeSetBuilder edgeSetBuilder;
    
    unsigned long numberOfNodes;
    int startNode;
    int goalNode;
    
    bool edgeBuilderIsSetup;
    bool fileIsValid;
    string inputFileName;
    ifstream inputStream;
};


#endif //DIJKSTRAS_ALG_EDGEIMPORTER_H
