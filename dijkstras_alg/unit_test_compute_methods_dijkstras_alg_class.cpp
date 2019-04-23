//
// Created by cornelius on 4/23/19.
//

#include <gtest/gtest.h>
#include "Dijkstras_Alg.h"

TEST(compute_path_fails, too_large_start_node)
{
    Dijkstras_Alg planner(10);
    
    EXPECT_THROW(planner.compute(15), StartNodeProvidedIsNonExistentException);
}

TEST(compute_path_fails, negative_start_node)
{
    Dijkstras_Alg planner(20);
    
    EXPECT_THROW(planner.compute(-5), StartNodeProvidedIsNonExistentException);
}

TEST(compute_path, unweighted_graph)
{
    vector<Edge> inputEdges{
            {0, 1},
            {0, 2},
            {0, 3},
            {1, 3},
            {1, 4},
            {2, 3},
            {3, 4},
            {2, 5},
            {4, 5}
    };
    
    EdgeSetBuilder edgeBuilder(inputEdges, false);
    
    Dijkstras_Alg planner(6);
    EXPECT_NO_THROW(planner.addEdges(edgeBuilder.getEdgeSet()));
    EXPECT_NO_THROW(planner.compute(0));
    
    auto outputDistanceTable = planner.getDistanceTable();
    EXPECT_DOUBLE_EQ(outputDistanceTable[0], 0.00);
    EXPECT_DOUBLE_EQ(outputDistanceTable[1], 1.00);
    EXPECT_DOUBLE_EQ(outputDistanceTable[2], 1.00);
    EXPECT_DOUBLE_EQ(outputDistanceTable[3], 1.00);
    EXPECT_DOUBLE_EQ(outputDistanceTable[4], 2.00);
    EXPECT_DOUBLE_EQ(outputDistanceTable[5], 2.00);
}

TEST(compute_path, weighted_graph)
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
    
    EdgeSetBuilder edgeBuilder(inputEdges, false);
    
    Dijkstras_Alg planner(6);
    EXPECT_NO_THROW(planner.addEdges(edgeBuilder.getEdgeSet()));
    EXPECT_NO_THROW(planner.compute(0));
    
    auto outputDistanceTable = planner.getDistanceTable();
    EXPECT_DOUBLE_EQ(outputDistanceTable[0], 0);
    EXPECT_DOUBLE_EQ(outputDistanceTable[1], 7);
    EXPECT_DOUBLE_EQ(outputDistanceTable[2], 11);
    EXPECT_DOUBLE_EQ(outputDistanceTable[3], 9);
    EXPECT_DOUBLE_EQ(outputDistanceTable[4], 20);
    EXPECT_DOUBLE_EQ(outputDistanceTable[5], 20);
}

TEST(return_path_from_start_to_given_node, unweighted_graph)
{
    vector<Edge> inputEdges{
            {0, 1},
            {0, 2},
            {0, 3},
            {1, 3},
            {1, 4},
            {2, 3},
            {3, 4},
            {2, 5},
            {4, 5}
    };
    
    EdgeSetBuilder edgeBuilder(inputEdges, false);
    
    Dijkstras_Alg planner(6);
    EXPECT_NO_THROW(planner.addEdges(edgeBuilder.getEdgeSet()));
    EXPECT_NO_THROW(planner.compute(0));
    
    auto outputPath_00 = planner.getPathFromStartToNode(0, 0);
    auto outputPath_01 = planner.getPathFromStartToNode(0, 1);
    auto outputPath_02 = planner.getPathFromStartToNode(0, 2);
    auto outputPath_03 = planner.getPathFromStartToNode(0, 3);
    auto outputPath_04 = planner.getPathFromStartToNode(0, 4);
    auto outputPath_05 = planner.getPathFromStartToNode(0, 5);
    
    auto expectedPath_00 = vector<int>{0};
    auto expectedPath_01 = vector<int>{0, 1};
    auto expectedPath_02 = vector<int>{0, 2};
    auto expectedPath_03 = vector<int>{0, 3};
    auto expectedPath_04 = vector<int>{0, 3, 4};
    auto expectedPath_05 = vector<int>{0, 2, 5};
    
    EXPECT_EQ(outputPath_00, expectedPath_00);
    EXPECT_EQ(outputPath_01, expectedPath_01);
    EXPECT_EQ(outputPath_02, expectedPath_02);
    EXPECT_EQ(outputPath_03, expectedPath_03);
    EXPECT_EQ(outputPath_04, expectedPath_04);
    EXPECT_EQ(outputPath_05, expectedPath_05);
}

TEST(return_path_from_start_to_given_node, weighted_graph)
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
    
    EdgeSetBuilder edgeBuilder(inputEdges, false);
    
    Dijkstras_Alg planner(6);
    EXPECT_NO_THROW(planner.addEdges(edgeBuilder.getEdgeSet()));
    EXPECT_NO_THROW(planner.compute(0));
    
    auto outputPath_00 = planner.getPathFromStartToNode(0, 0);
    auto outputPath_01 = planner.getPathFromStartToNode(0, 1);
    auto outputPath_02 = planner.getPathFromStartToNode(0, 2);
    auto outputPath_03 = planner.getPathFromStartToNode(0, 3);
    auto outputPath_04 = planner.getPathFromStartToNode(0, 4);
    auto outputPath_05 = planner.getPathFromStartToNode(0, 5);
    
    auto expectedPath_00 = vector<int>{0};
    auto expectedPath_01 = vector<int>{0, 1};
    auto expectedPath_02 = vector<int>{0, 3, 2};
    auto expectedPath_03 = vector<int>{0, 3};
    auto expectedPath_04 = vector<int>{0, 3, 4};
    auto expectedPath_05 = vector<int>{0, 3, 2, 5};
    
    EXPECT_EQ(outputPath_00, expectedPath_00);
    EXPECT_EQ(outputPath_01, expectedPath_01);
    EXPECT_EQ(outputPath_02, expectedPath_02);
    EXPECT_EQ(outputPath_03, expectedPath_03);
    EXPECT_EQ(outputPath_04, expectedPath_04);
    EXPECT_EQ(outputPath_05, expectedPath_05);
}
