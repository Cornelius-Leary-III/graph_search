//
// Created by carpenter on 1/30/19.
//

#include <gtest/gtest.h>
#include "Graph.h"

TEST(Graph_class, constructor_no_params)
{
    Graph testGraph;
    
    auto testNodeList = testGraph.getNodeList();
    auto testNodeCount = testGraph.getNodeCount();
    bool testDirectedGraphFlag = testGraph.isGraphDirected();
    auto testAdjList = testGraph.getAdjacencyList();
    
    EXPECT_TRUE(testNodeList.empty());
    EXPECT_EQ(testNodeCount, 0);
    EXPECT_TRUE(testAdjList.empty());
    EXPECT_TRUE(testDirectedGraphFlag);
}
