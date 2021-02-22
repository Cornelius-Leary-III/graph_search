//
// Created by cornelius on 4/23/19.
//

#ifndef DIJKSTRAS_ALG_SHORTESTPATH_H
#define DIJKSTRAS_ALG_SHORTESTPATH_H

#include "Dijkstras_Alg.h"
#include "EdgeImporter.h"

#include <memory>

class InvalidGraphFileException : public std::exception
{
   public:
   const char* what() noexcept
   {
      return "\nERROR: Start node must be one of the nodes in the graph.\n\nProgram terminating.";
   }
};

class MustImportEdgesBeforeCallingThisMethodException : public std::exception
{
   public:
   const char* what() noexcept
   {
      return "\nERROR: Must call importEdges() before calling this method.\n\nProgram terminating.";
   }
};

class ZeroNodesImportedException : public std::exception
{
   public:
   const char* what() noexcept
   {
      return "\nERROR: Must have a non-zero # of nodes.\n\nProgram terminating.";
   }
};

class MustComputePathsBeforeCallingThisMethodException : public std::exception
{
   public:
   const char* what() noexcept
   {
      return "\nERROR: Must call importEdges() before calling this method.\n\nProgram terminating.";
   }
};

class ShortestPath
{
   public:
   ShortestPath();

   void importEdges(std::string graph_file, bool is_directed = true);
   void computePathFromStartToGoal();

   double                   getDistanceFromStartToGoal();
   std::vector<std::string> getPathFromStartToGoal();

   EdgeImporter&  getEdgeImporter();
   Dijkstras_Alg& getDijkstrasAlg();

   private:
   bool mHaveEdgesBeenImported;
   bool mHavePathsBeenComputed;

   std::unique_ptr<EdgeImporter>  mEdgeImporter;
   std::unique_ptr<Dijkstras_Alg> mDijkstrasAlgPtr;
};

#endif // DIJKSTRAS_ALG_SHORTESTPATH_H
