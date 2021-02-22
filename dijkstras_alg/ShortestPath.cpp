//
// Created by cornelius on 4/23/19.
//

#include "ShortestPath.h"

ShortestPath::ShortestPath()
   : mHaveEdgesBeenImported(false),
     mHavePathsBeenComputed(false),
     mEdgeImporter(new EdgeImporter("")),   // placeholder object
     mDijkstrasAlgPtr(new Dijkstras_Alg(0)) // placeholder object
{
}

void ShortestPath::importEdges(std::string graph_file, bool is_directed)
{
   // create a new EdgeImporter object using the provided graph file.
   mEdgeImporter.reset(new EdgeImporter(std::move(graph_file)));

   // calling the setup to the edgeSetBuilder for Dijkstra's Algorithm (DA):
   //      <isDirected> --> DA can be either directed or undirected.
   //      false --> DA cannot have negative weights.
   //      false --> DA cannot have self-loops.
   mEdgeImporter->setupEdgeBuilder(is_directed, false, false);

   // check if file is valid.
   if (!mEdgeImporter->isFileValid())
   {
      throw InvalidGraphFileException();
   }

   // import graph setup and edge data.
   mEdgeImporter->readGraphFile();
   mHaveEdgesBeenImported = true;
}

void ShortestPath::computePathFromStartToGoal()
{
   // check if importEdges() has been called.
   if (!mHaveEdgesBeenImported)
   {
      throw MustImportEdgesBeforeCallingThisMethodException();
   }

   // check if any nodes have been imported successfully.
   if (mEdgeImporter->getNumberOfNodes() == 0)
   {
      throw ZeroNodesImportedException();
   }

   // create a new Dijkstras_Alg object using the imported node count.
   mDijkstrasAlgPtr.reset(new Dijkstras_Alg(mEdgeImporter->getNumberOfNodes()));

   try
   {
      mDijkstrasAlgPtr->addEdges(mEdgeImporter->getEdges());
      mDijkstrasAlgPtr->compute(mEdgeImporter->getStartNodeName());
   }
   catch (std::exception& exception)
   {
      std::cout << exception.what() << std::endl;
   }

   mHavePathsBeenComputed = true;
}

double ShortestPath::getDistanceFromStartToGoal()
{
   // check if edges have already been imported.
   if (!mHaveEdgesBeenImported)
   {
      throw MustImportEdgesBeforeCallingThisMethodException();
   }

   // check if DA object has been updated and if paths have been computed.
   if (!mHavePathsBeenComputed)
   {
      throw MustComputePathsBeforeCallingThisMethodException();
   }

   auto outputDistances = mDijkstrasAlgPtr->getDistanceTable();
   return outputDistances[mEdgeImporter->getGoalNodeName()];
}

std::vector<std::string> ShortestPath::getPathFromStartToGoal()
{
   // check if edges have already been imported.
   if (!mHaveEdgesBeenImported)
   {
      throw MustImportEdgesBeforeCallingThisMethodException();
   }

   // get the path.
   return mDijkstrasAlgPtr->getPathFromStartToNode(mEdgeImporter->getStartNodeName(),
                                                   mEdgeImporter->getGoalNodeName());
}

EdgeImporter& ShortestPath::getEdgeImporter()
{
   return *mEdgeImporter;
}

Dijkstras_Alg& ShortestPath::getDijkstrasAlg()
{
   return *mDijkstrasAlgPtr;
}
