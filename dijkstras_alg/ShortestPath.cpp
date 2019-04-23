//
// Created by cornelius on 4/23/19.
//

#include "ShortestPath.h"

ShortestPath::ShortestPath(string graphFile)
        : dijkstrasAlgPtr{nullptr},
          edgeImporter{std::move(graphFile)}
{
}

void ShortestPath::importEdges()
{
    edgeImporter.setupEdgeBuilder(true, false, false);
    
    if (!edgeImporter.isFileValid())
    {
        throw InvalidGraphFileException();
    }
    
    edgeImporter.readGraphFile();
}

void ShortestPath::computePathFromStartToGoal()
{
    dijkstrasAlgPtr.reset(new Dijkstras_Alg(edgeImporter.getNumberOfNodes()));
    
    dijkstrasAlgPtr->addEdges(edgeImporter.getEdges());
    dijkstrasAlgPtr->compute(edgeImporter.getStartNode());
}

double ShortestPath::getDistanceFromStartToGoal()
{
    auto outputDistances = dijkstrasAlgPtr->getDistanceTable();
    
    return outputDistances[edgeImporter.getGoalNode()];
}

vector<int> ShortestPath::getPathFromStartToGoal()
{
    return std::move(dijkstrasAlgPtr->getPathFromStartToNode(edgeImporter.getStartNode(),
                                                             edgeImporter.getGoalNode()));
}

