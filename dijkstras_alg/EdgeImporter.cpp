//
// Created by cornelius on 4/23/19.
//

#include "EdgeImporter.h"

EdgeImporter::EdgeImporter(string newFileToReadFrom)
        : inputFileName{std::move(newFileToReadFrom)},
          fileIsValid{false},
          numberOfNodes{0},
          startNode{0},
          goalNode{0},
          edgeBuilderIsSetup{false}
{
    // check if the file string is empty.
    if (!inputFileName.empty())
    {
        // open the file.
        inputStream.open(inputFileName);
        
        // check if file has been opened successfully.
        if (inputStream.is_open())
        {
            fileIsValid = true;
        }
    }
}

bool EdgeImporter::isFileValid()
{
    return fileIsValid;
}

int EdgeImporter::getStartNode()
{
    return startNode;
}

int EdgeImporter::getGoalNode()
{
    return goalNode;
}

unsigned long EdgeImporter::getNumberOfNodes()
{
    return numberOfNodes;
}

vector<Edge>& EdgeImporter::getEdges()
{
    return edgeSetBuilder.getEdgeSet();
}

void EdgeImporter::setupEdgeBuilder(bool isDirected,
                                    bool canHaveNegWeights,
                                    bool canHaveSelfLoops)
{
    edgeSetBuilder = EdgeSetBuilder(isDirected, canHaveNegWeights, canHaveSelfLoops);
    
    edgeBuilderIsSetup = true;
}

void EdgeImporter::readGraphFile()
{
    // check if edge set builder has been setup already.
    if (!edgeBuilderIsSetup)
    {
        // create the edge builder using the default setup options.
        setupEdgeBuilder();
    }
    
    // check if file can be read from.
    if (!fileIsValid)
    {
        return;
    }
    
    // read the graph's setup information.
    processFirstThreeLinesOfGraphFile();
    
    // double check that the file has valid syntax.
    if (!fileIsValid)
    {
        return;
    }
    
    // import the edge data.
    importEdges();
    
    // close the file afterwards.
    inputStream.close();
}

void EdgeImporter::processFirstThreeLinesOfGraphFile()
{
    // obtain these setup values:
    //      1) # of nodes in graph
    //      2) the start node name
    //      3) the goal node name
    
    // syntax file: each value is on its own line.
    
    int valueCount = 0;
    while (valueCount < 3)
    {
        // parse the setup value on the current line.
        string temp = getSetupStringValue();
        
        // check if the setup function returned an empty string
        //      --> returns an empty string if no value was on that line.
        //      --> returns an empty string if there is additional information on the line.
        //      --> returns the actual value as a string, otherwise.
        if (!temp.empty())
        {
            if (valueCount == 0)
            {
                numberOfNodes = std::stoul(temp);
            }
            else if (valueCount == 1)
            {
                startNode = std::stoi(temp);
            }
            else if (valueCount == 2)
            {
                goalNode = std::stoi(temp);
            }
        }
        else
        {
            // string was empty, so the file does not have the correct syntax.
            
            fileIsValid = false;
            return;
        }
        
        ++valueCount;
    }
}

string EdgeImporter::getSetupStringValue()
{
    string currentLine;
    string value;
    
    // obtain the current line from the file.
    if (std::getline(inputStream, currentLine, '\n'))
    {
        // setting found.
        stringstream ss;
        ss << currentLine;
        
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
    string tempLine;
    
    // get the next line.
    while (std::getline(inputStream, tempLine))
    {
        // check if line is empty.
        if (tempLine.empty())
        {
            continue;
        }
        
        // process the current edge.
        processCurrentEdgeInFile(tempLine);
    }
}

void EdgeImporter::processCurrentEdgeInFile(const string& edgeToProcess)
{
    // pass the entire edge data string into the stream.
    stringstream ss;
    ss << edgeToProcess;
    
    // parse the source node name from the edge data.
    string sourceNodeName;
    ss >> sourceNodeName;
    int source = std::stoi(sourceNodeName);
    
    // parse the destination node name from the edge data.
    string destinationNodeName;
    ss >> destinationNodeName;
    int destination = std::stoi(destinationNodeName);
    
    // parse the weight from the edge data.
    string weightString;
    ss >> weightString;
    double edgeWeight = std::stod(weightString);
    
    // add the edge to the edge list.
    edgeSetBuilder.createAndAppendEdge(source, destination, edgeWeight);
}