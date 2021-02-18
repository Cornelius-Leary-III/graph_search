//
// Created by cornelius on 4/23/19.
//

#ifndef DIJKSTRAS_ALG_EDGEIMPORTER_H
#define DIJKSTRAS_ALG_EDGEIMPORTER_H

#include "EdgeSetBuilder.h"

class EdgeImporter
{
   public:
   explicit EdgeImporter(string new_file_to_read_from);

   bool isFileValid();

   vector<Edge>&   getEdges();
   EdgeSetBuilder& getEdgeBuilder();
   int             getStartNode();
   int             getGoalNode();
   unsigned long   getNumberOfNodes();

   void setupEdgeBuilder(bool is_directed               = true,
                         bool can_have_neg_edge_weights = true,
                         bool can_have_self_loops       = true);
   void readGraphFile();

   private:
   void   processFirstThreeLinesOfGraphFile();
   string getSetupStringValue();

   void importEdges();
   void processCurrentEdgeInFile(const string& edge_to_process);

   int  getSmallestNodeIndex();
   void makeEdgeSetZeroBased(int difference);

   private:
   EdgeSetBuilder mEdgeSetBuilder;

   unsigned long mNumberOfNodes;
   int           mStartNode;
   int           mGoalNode;

   bool     mEdgeBuilderIsSetup;
   bool     mFileIsValid;
   string   mInputFileName;
   ifstream mInputStream;
};

#endif // DIJKSTRAS_ALG_EDGEIMPORTER_H
