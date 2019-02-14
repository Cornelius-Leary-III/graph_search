//
// Created by carpenter on 2/11/19.
//

#include <gtest/gtest.h>
#include "Dijkstras_Alg.h"

TEST(Dijkstras_Alg_class, constructor_num_nodes)
{
    unsigned long inputNodeCount = 100;
    Dijkstras_Alg testPlanner(inputNodeCount);
    
    auto testUnvisitedQueue = testPlanner.getUnvisitedVertices();
    auto testDistanceTable = testPlanner.getDistanceTable();
    auto testPredecessorTable = testPlanner.getPredecessorTable();
    auto testEdgeSet = testPlanner.getEdgeSet();
    
    EXPECT_TRUE(testUnvisitedQueue.empty());
    //    EXPECT_EQ(testUnvisitedQueue.size(), inputNodeCount);
    EXPECT_EQ(testDistanceTable.size(), inputNodeCount);
    EXPECT_EQ(testPredecessorTable.size(), inputNodeCount);
    EXPECT_TRUE(testEdgeSet.empty());
}

TEST(Dijkstras_Alg_class, add_zero_based_edges)
{
    vector<Edge> inputEdges{
            {0, 1, 7},
            {0, 2, 14},
            {0, 3, 9},
            {1, 3, 10},
            {1, 4, 15},
            {2, 3, 2},
            {3, 4, 11},
            {2, 5, 9},
            {4, 5, 6}
    };
    
    EdgeSetBuilder testESB(inputEdges, false);
    auto edges = testESB.getEdgeSet();
    EXPECT_FALSE(testESB.isGraphDirected());
    
    Dijkstras_Alg testDijkstraAlg(6);
    EXPECT_NO_THROW(testDijkstraAlg.addEdges(edges));
    
    auto outputEdges = testDijkstraAlg.getEdgeSet();
    EXPECT_EQ(outputEdges.size(), 2 * inputEdges.size());
    EXPECT_EQ(outputEdges.size(), edges.size());
    
    auto inputEdgeIter = inputEdges.begin();
    auto inputEdgesEnd = inputEdges.end();
    
    auto outputEdgeIter = outputEdges.begin();
    auto outputEdgesEnd = outputEdges.end();
    
    while (outputEdgeIter != outputEdgesEnd &&
           inputEdgeIter != inputEdgesEnd)
    {
        EXPECT_EQ(outputEdgeIter->source, inputEdgeIter->source);
        EXPECT_EQ(outputEdgeIter->destination, inputEdgeIter->destination);
        EXPECT_EQ(outputEdgeIter->weight, inputEdgeIter->weight);
        
        ++outputEdgeIter;
        
        if (outputEdgeIter != outputEdgesEnd)
        {
            break;
        }
        
        EXPECT_EQ(outputEdgeIter->source, inputEdgeIter->destination);
        EXPECT_EQ(outputEdgeIter->destination, inputEdgeIter->source);
        EXPECT_EQ(outputEdgeIter->weight, inputEdgeIter->weight);
        
        ++outputEdgeIter;
        ++inputEdgeIter;
    }
}

TEST(Dijkstras_Alg_class, compute_graph)
{
    vector<Edge> inputEdges{
            {0, 1, 7},
            {0, 2, 14},
            {0, 3, 9},
            {1, 3, 10},
            {1, 4, 15},
            {2, 3, 2},
            {3, 4, 11},
            {2, 5, 9},
            {4, 5, 6}
    };
    
    EdgeSetBuilder testESB(inputEdges, false);
    auto edges = testESB.getEdgeSet();
    EXPECT_FALSE(testESB.isGraphDirected());
    
    Dijkstras_Alg testDijkstraAlg(6);
    EXPECT_NO_THROW(testDijkstraAlg.addEdges(edges));
    
    int sourceVertex = 0;
    testDijkstraAlg.compute(sourceVertex);
    
    auto outputDistanceTable = testDijkstraAlg.getDistanceTable();
    EXPECT_EQ(outputDistanceTable[0], 0);
    EXPECT_EQ(outputDistanceTable[1], 7);
    EXPECT_EQ(outputDistanceTable[2], 11);
    EXPECT_EQ(outputDistanceTable[3], 9);
    EXPECT_EQ(outputDistanceTable[4], 20);
    EXPECT_EQ(outputDistanceTable[5], 20);
}



