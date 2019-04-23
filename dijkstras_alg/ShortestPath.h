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

class ShortestPath
{
public:
    
    explicit ShortestPath(string graphFile);
    
    void importEdges();
    void computePathFromStartToGoal();
    
    double getDistanceFromStartToGoal();
    vector<int> getPathFromStartToGoal();
    
private:
    
    EdgeImporter edgeImporter;
    unique_ptr<Dijkstras_Alg> dijkstrasAlgPtr;
};


#endif //DIJKSTRAS_ALG_SHORTESTPATH_H
