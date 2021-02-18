//
// Created by cornelius on 4/23/19.
//

#include "EdgeImporter.h"

EdgeImporter::EdgeImporter(string new_file_to_read_from)
   : mEdgeSetBuilder(),
     mNumberOfNodes(0),
     mStartNode(0),
     mGoalNode(0),
     mEdgeBuilderIsSetup(false),
     mFileIsValid(false),
     mInputFileName(std::move(new_file_to_read_from))
{
   // check if the file string is empty.
   if (!mInputFileName.empty())
   {
      // open the file.
      mInputStream.open(mInputFileName);

      // check if file has been opened successfully.
      if (mInputStream.is_open())
      {
         mFileIsValid = true;
      }
   }
}

bool EdgeImporter::isFileValid()
{
   return mFileIsValid;
}

int EdgeImporter::getStartNode()
{
   return mStartNode;
}

int EdgeImporter::getGoalNode()
{
   return mGoalNode;
}

unsigned long EdgeImporter::getNumberOfNodes()
{
   return mNumberOfNodes;
}

vector<Edge>& EdgeImporter::getEdges()
{
   return mEdgeSetBuilder.getEdgeSet();
}

EdgeSetBuilder& EdgeImporter::getEdgeBuilder()
{
   return mEdgeSetBuilder;
}

void EdgeImporter::setupEdgeBuilder(bool is_directed,
                                    bool can_have_neg_edge_weights,
                                    bool can_have_self_loops)
{
   mEdgeSetBuilder = EdgeSetBuilder(is_directed, can_have_neg_edge_weights, can_have_self_loops);

   mEdgeBuilderIsSetup = true;
}

void EdgeImporter::readGraphFile()
{
   // check if edge set builder has been setup already.
   if (!mEdgeBuilderIsSetup)
   {
      // create the edge builder using the default setup options.
      setupEdgeBuilder();
   }

   // check if file can be read from.
   if (!mFileIsValid)
   {
      return;
   }

   // read the graph's setup information.
   processFirstThreeLinesOfGraphFile();

   // double check that the file has valid syntax.
   if (!mFileIsValid)
   {
      return;
   }

   // import the edge data.
   importEdges();

   if (mEdgeSetBuilder.getEdgeCount() > 0)
   {
      int difference_from_zero = getSmallestNodeIndex();

      if (difference_from_zero != 0)
      {
         makeEdgeSetZeroBased(difference_from_zero);
      }
   }

   // close the file afterwards.
   mInputStream.close();
}

void EdgeImporter::processFirstThreeLinesOfGraphFile()
{
   // obtain these setup values:
   //      1) # of nodes in graph
   //      2) the start node name
   //      3) the goal node name

   // syntax file: each value is on its own line.

   int value_count = 0;
   while (value_count < 3)
   {
      // parse the setup value on the current line.
      string temp = getSetupStringValue();

      // check if the setup function returned an empty string
      //      --> returns an empty string if no value was on that line.
      //      --> returns an empty string if there is additional information on the line.
      //      --> returns the actual value as a string, otherwise.
      if (temp.empty())
      {
         // string was empty, so the file does not have the correct syntax.

         mFileIsValid = false;
         return;
      }

      if (value_count == 0)
      {
         mNumberOfNodes = std::stoul(temp);
      }
      else if (value_count == 1)
      {
         mStartNode = std::stoi(temp);
      }
      else if (value_count == 2)
      {
         mGoalNode = std::stoi(temp);
      }

      ++value_count;
   }
}

string EdgeImporter::getSetupStringValue()
{
   string current_line;
   string value;

   // obtain the current line from the file.
   if (std::getline(mInputStream, current_line, '\n'))
   {
      // setting found.
      stringstream ss;
      ss << current_line;

      // save the first value.
      if (ss >> value)
      {
         string temp;

         // check if additional value is on same line of file.
         if (ss >> temp)
         {
            // there is additional information on the line.
            return string();
         }
      }
      // value found AND no additional info on the same line.
   }

   return value;
}

void EdgeImporter::importEdges()
{
   string temp_line;

   // get the next line.
   while (std::getline(mInputStream, temp_line))
   {
      // check if line is empty.
      if (temp_line.empty())
      {
         continue;
      }

      // process the current edge.
      processCurrentEdgeInFile(temp_line);
   }
}

void EdgeImporter::processCurrentEdgeInFile(const string& edge_to_process)
{
   // pass the entire edge data string into the stream.
   stringstream ss;
   ss << edge_to_process;

   // parse the source node name from the edge data.
   string source_node_name;
   ss >> source_node_name;
   int source = std::stoi(source_node_name);

   // parse the destination node name from the edge data.
   string destination_node_name;
   ss >> destination_node_name;
   int destination = std::stoi(destination_node_name);

   // parse the weight from the edge data.
   string weight_string;
   ss >> weight_string;
   double edge_weight = std::stod(weight_string);

   // add the edge to the edge list.
   mEdgeSetBuilder.createAndAppendEdge(source, destination, edge_weight);
}

int EdgeImporter::getSmallestNodeIndex()
{
   auto edge_iter = mEdgeSetBuilder.getEdgeSet().begin();
   auto edges_end = mEdgeSetBuilder.getEdgeSet().end();

   int smallest_value = INT32_MAX;

   while (edge_iter != edges_end)
   {
      if (edge_iter->mSource == 0 || edge_iter->mDestination == 0)
      {
         return 0;
      }

      if (edge_iter->mSource < smallest_value)
      {
         smallest_value = edge_iter->mSource;
      }

      if (edge_iter->mDestination < smallest_value)
      {
         smallest_value = edge_iter->mDestination;
      }

      ++edge_iter;
   }
   return smallest_value;
}

void EdgeImporter::makeEdgeSetZeroBased(int difference)
{
   auto edge_iter = mEdgeSetBuilder.getEdgeSet().begin();
   auto edges_end = mEdgeSetBuilder.getEdgeSet().end();

   while (edge_iter != edges_end)
   {
      edge_iter->mSource -= difference;
      edge_iter->mDestination -= difference;
      ++edge_iter;
   }

   mGoalNode -= difference;
   mStartNode -= difference;
}
