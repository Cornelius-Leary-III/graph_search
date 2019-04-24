//
// Created by cornelius on 4/23/19.
//

#ifndef DIJKSTRAS_ALG_SHORTESTPATH_H
#define DIJKSTRAS_ALG_SHORTESTPATH_H

#include "Dijkstras_Alg.h"
#include "EdgeImporter.h"

#include <memory>
using std::unique_ptr;
using std::make_unique;

class InvalidGraphFileException : public std::exception
{
public:
    
    const char * what() noexcept
    {
        return "\nERROR: Start node must be one of the nodes in the graph.\n\nProgram terminating.";
    }
    
};

class MustImportEdgesBeforeCallingThisMethodException : public std::exception
{
public:
    
    const char * what() noexcept
    {
        return "\nERROR: Must call importEdges() before calling this method.\n\nProgram terminating.";
    }
    
};

class ZeroNodesImportedException : public std::exception
{
public:
    
    const char * what() noexcept
    {
        return "\nERROR: Must have a non-zero # of nodes.\n\nProgram terminating.";
    }
    
};

class MustComputePathsBeforeCallingThisMethodException : public std::exception
{
public:
    
    const char * what() noexcept
    {
        return "\nERROR: Must call importEdges() before calling this method.\n\nProgram terminating.";
    }
    
};

class ShortestPath
{
public:
    
    ShortestPath();
    
    void importEdges(string graphFile);
    void computePathFromStartToGoal();
    
    double getDistanceFromStartToGoal();
    vector<int> getPathFromStartToGoal();
    
    EdgeImporter& getEdgeImporter();
    Dijkstras_Alg& getDijkstrasAlg();
    
    
private:
    
    bool edgesHaveBeenImported;
    bool pathsHaveBeenComputed;
    
    unique_ptr<EdgeImporter> edgeImporter;
    unique_ptr<Dijkstras_Alg> dijkstrasAlgPtr;
};


#endif //DIJKSTRAS_ALG_SHORTESTPATH_H
