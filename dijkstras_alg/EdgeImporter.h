//
// Created by cornelius on 4/23/19.
//

#ifndef DIJKSTRAS_ALG_EDGEIMPORTER_H
#define DIJKSTRAS_ALG_EDGEIMPORTER_H

#include "EdgeSetBuilder.h"

class EdgeImporter
{
   public:
   explicit EdgeImporter(std::string new_file_to_read_from);

   bool isFileValid();

   std::vector<Edge>& getEdges();
   EdgeSetBuilder&    getEdgeBuilder();
   const std::string& getStartNodeName();
   const std::string& getGoalNodeName();
   unsigned long      getNumberOfNodes();

   void setupEdgeBuilder(bool is_directed               = true,
                         bool can_have_neg_edge_weights = true,
                         bool can_have_self_loops       = true);
   void readGraphFile();

   private:
   void        processFirstThreeLinesOfGraphFile();
   std::string getSetupStringValue();

   void importEdges();
   void processCurrentEdgeInFile(const std::string& edge_to_process);

   //   int  getSmallestNodeIndex();
   //   void makeEdgeSetZeroBased(int difference);

   private:
   EdgeSetBuilder mEdgeSetBuilder;

   unsigned long mNumberOfNodes;
   std::string   mStartNodeName;
   std::string   mGoalNodeName;

   bool          mEdgeBuilderIsSetup;
   bool          mFileIsValid;
   std::string   mInputFileName;
   std::ifstream mInputStream;
};

#endif // DIJKSTRAS_ALG_EDGEIMPORTER_H
