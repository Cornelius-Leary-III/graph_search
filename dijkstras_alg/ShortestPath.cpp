//
// Created by cornelius on 4/23/19.
//

#include "ShortestPath.h"

ShortestPath::ShortestPath()
        : dijkstrasAlgPtr{new Dijkstras_Alg(0)},        // placeholder object
          edgeImporter{new EdgeImporter("")},           // placeholder object
          edgesHaveBeenImported{false},
          pathsHaveBeenComputed{false}
{
}

void ShortestPath::importEdges(string graphFile, bool isDirected)
{
    // create a new EdgeImporter object using the provided graph file.
    edgeImporter.reset(new EdgeImporter(std::move(graphFile)));
    
    // calling the setup to the edgeSetBuilder for Dijkstra's Algorithm (DA):
    //      <isDirected> --> DA can be either directed or undirected.
    //      false --> DA cannot have negative weights.
    //      false --> DA cannot have self-loops.
    edgeImporter->setupEdgeBuilder(isDirected, false, false);
    
    // check if file is valid.
    if (!edgeImporter->isFileValid())
    {
        throw InvalidGraphFileException();
    }
    
    // import graph setup and edge data.
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
    // check if edges have already been imported.
    if (!edgesHaveBeenImported)
    {
        throw MustImportEdgesBeforeCallingThisMethodException();
    }
    
    // check if DA object has been updated and if paths have been computed.
    if (!pathsHaveBeenComputed)
    {
        throw MustComputePathsBeforeCallingThisMethodException();
    }
    
    auto outputDistances = dijkstrasAlgPtr->getDistanceTable();
    return outputDistances[edgeImporter->getGoalNode()];
}

vector<int> ShortestPath::getPathFromStartToGoal()
{
    // check if edges have already been imported.
    if (!edgesHaveBeenImported)
    {
        throw MustImportEdgesBeforeCallingThisMethodException();
    }
    
    // get the path.
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

