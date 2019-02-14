//
// Created by carpenter on 2/12/19.
//

#include "EdgeSetBuilder.h"

EdgeSetBuilder::EdgeSetBuilder()
        : edgeSet{},
          directedGraph{true},
          negativeEdgesAllowed{false},
          selfLoopsAllowed{false}
{
}

EdgeSetBuilder::EdgeSetBuilder(bool directedGraphState,
                               bool negativeEdgesAllowedState,
                               bool selfLoopsAllowedState)
        : edgeSet{},
          directedGraph{directedGraphState},
          negativeEdgesAllowed{negativeEdgesAllowedState},
          selfLoopsAllowed{selfLoopsAllowedState}
{
}

EdgeSetBuilder::EdgeSetBuilder(const vector<Edge>& edges,
                               bool directedGraphState)
        : directedGraph{directedGraphState}
{
    if (!directedGraph)
    {
        addEdgesForUndirectedGraph(edges);
    }
    else
    {
        edgeSet = edges;
    }
    
    negativeEdgesAllowed = checkForNegativeEdges();
    selfLoopsAllowed = checkForSelfLoops();
}

void EdgeSetBuilder::addEdgesForUndirectedGraph(const vector<Edge>& edges)
{
    auto edgeIter = edges.begin();
    auto edgesEnd = edges.end();
    
    vector<Edge> undirectedEdges;
    
    while (edgeIter != edgesEnd)
    {
        undirectedEdges.push_back(*edgeIter);
        undirectedEdges.emplace_back(edgeIter->destination,
                                     edgeIter->source,
                                     edgeIter->weight);
        ++edgeIter;
    }
    
    edgeSet = undirectedEdges;
}

EdgeSetBuilder::EdgeSetBuilder(const EdgeSetBuilder& edgeSetBuilderToCopy)
{
    this->edgeSet = edgeSetBuilderToCopy.edgeSet;
    this->directedGraph = edgeSetBuilderToCopy.directedGraph;
    this->negativeEdgesAllowed = edgeSetBuilderToCopy.negativeEdgesAllowed;
    this->selfLoopsAllowed = edgeSetBuilderToCopy.selfLoopsAllowed;
}

EdgeSetBuilder& EdgeSetBuilder::operator=(const EdgeSetBuilder& rhs)
{
    if (this != &rhs)
    {
        this->edgeSet = rhs.edgeSet;
        this->directedGraph = rhs.directedGraph;
        this->negativeEdgesAllowed = rhs.negativeEdgesAllowed;
        this->selfLoopsAllowed = rhs.selfLoopsAllowed;
    }
    
    return *this;
}

bool EdgeSetBuilder::checkForNegativeEdges()
{
    auto edgeIter = edgeSet.begin();
    auto edgesEnd = edgeSet.end();
    
    while (edgeIter != edgesEnd)
    {
        if (edgeIter->weight < 0)
        {
            return true;
        }
        ++edgeIter;
    }
    
    return false;
}

bool EdgeSetBuilder::checkForSelfLoops()
{
    auto edgeIter = edgeSet.begin();
    auto edgesEnd = edgeSet.end();
    
    while (edgeIter != edgesEnd)
    {
        if (edgeIter->source == edgeIter->destination)
        {
            return true;
        }
        ++edgeIter;
    }
    
    return false;
}

vector<Edge>& EdgeSetBuilder::getEdgeSet()
{
    return edgeSet;
}

bool EdgeSetBuilder::isGraphDirected()
{
    return directedGraph;
}

bool EdgeSetBuilder::areNegativeEdgesAllowed()
{
    return negativeEdgesAllowed;
}

bool EdgeSetBuilder::areSelfLoopsAllowed()
{
    return selfLoopsAllowed;
}

unsigned long EdgeSetBuilder::getEdgeCount()
{
    return edgeSet.size();
}

void EdgeSetBuilder::createAndAppendEdge(int newSource,
                                         int newDestination,
                                         double newWeight)
{
    edgeSet.emplace_back(newSource, newDestination, newWeight);
    
    if (!directedGraph)
    {
        edgeSet.emplace_back(newDestination, newSource, newWeight);
    }
}

void EdgeSetBuilder::readEdgesFromFile(const string& inputFile)
{
    ifstream input(inputFile);
    
    if (!input.is_open())
    {
        return;
    }
    
    processFirstThreeLinesOfGraphFile(input);
    readInEdges(input);
    
    input.close();
}

void EdgeSetBuilder::processFirstThreeLinesOfGraphFile(istream& inputStream)
{
    string temp;
    
    inputStream >> temp;
    numberOfNodes = std::stoul(temp);
    
    temp.clear();
    inputStream >> temp;
    startNode = std::stoi(temp);
    
    temp.clear();
    inputStream >> temp;
    goalNode = std::stoi(temp);
    
    std::getline(inputStream, temp, '\n');
}

void EdgeSetBuilder::readInEdges(istream& input)
{
    string tempLine;
    
    while (std::getline(input, tempLine))
    {
        if (tempLine.empty())
        {
            continue;
        }
        processEdge(tempLine);
    }
}

void EdgeSetBuilder::processEdge(const string& edgeToProcess)
{
    stringstream ss;
    ss << edgeToProcess;
    
    string sourceNodeName;
    ss >> sourceNodeName;
    int source = std::stoi(sourceNodeName);
    
    string destinationNodeName;
    ss >> destinationNodeName;
    int destination = std::stoi(destinationNodeName);
    
    string weightString;
    ss >> weightString;
    double weight = std::stod(weightString);
    
    edgeSet.emplace_back(source, destination, weight);
    
    if (!directedGraph)
    {
        edgeSet.emplace_back(destination, source, weight);
    }
}




















