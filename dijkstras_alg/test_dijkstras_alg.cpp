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
    vector<Edge> inputEdges = {
            {0, 1, 7},
            {0, 2, 3},
            {1, 2, 1},
            {1, }
    };
}