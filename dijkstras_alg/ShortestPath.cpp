//
// Created by cornelius on 4/23/19.
//

#include "ShortestPath.h"

ShortestPath::ShortestPath()
        : dijkstrasAlgPtr{new Dijkstras_Alg(0)},
          edgeImporter{new EdgeImporter("")},
          edgesHaveBeenImported{false},
          pathsHaveBeenComputed{false}
{
}

void ShortestPath::importEdges(string graphFile)
{
    edgeImporter.reset(new EdgeImporter(std::move(graphFile)));
    
    edgeImporter->setupEdgeBuilder(true, false, false);
    
    if (!edgeImporter->isFileValid())
    {
        throw InvalidGraphFileException();
    }
    
    edgeImporter->readGraphFile();
    
    edgesHaveBeenImported = true;
}

void ShortestPath::computePathFromStartToGoal()
{
    // check if importEdges() has been called.
    if (!edgesHaveBeenImported)
    {
        throw MustImportEdgesBeforeCallingThisMethodException();
    }
    
    // check if any nodes have been imported successfully.
    if (edgeImporter->getNumberOfNodes() == 0)
    {
        throw ZeroNodesImportedException();
    }
    
    // create a new Dijkstras_Alg object using the imported node count.
    dijkstrasAlgPtr.reset(new Dijkstras_Alg(edgeImporter->getNumberOfNodes()));
    
    try
    {
        dijkstrasAlgPtr->addEdges(edgeImporter->getEdges());
        dijkstrasAlgPtr->compute(edgeImporter->getStartNode());
    }
    catch (std::exception& exception)
    {
        cout << exception.what() << endl;
    }
    
    pathsHaveBeenComputed = true;
}

double ShortestPath::getDistanceFromStartToGoal()
{
    if (!edgesHaveBeenImported)
    {
        throw MustImportEdgesBeforeCallingThisMethodException();
    }
    
    if (!pathsHaveBeenComputed)
    {
        throw MustComputePathsBeforeCallingThisMethodException();
    }
    
    auto outputDistances = dijkstrasAlgPtr->getDistanceTable();
    return outputDistances[edgeImporter->getGoalNode()];
}

vector<int> ShortestPath::getPathFromStartToGoal()
{
    if (!edgesHaveBeenImported)
    {
        throw MustImportEdgesBeforeCallingThisMethodException();
    }
    
    return dijkstrasAlgPtr->getPathFromStartToNode(edgeImporter->getStartNode(),
                                                             edgeImporter->getGoalNode());
}

EdgeImporter& ShortestPath::getEdgeImporter()
{
    return *edgeImporter;
}

Dijkstras_Alg& ShortestPath::getDijkstrasAlg()
{
    return *dijkstrasAlgPtr;
}

