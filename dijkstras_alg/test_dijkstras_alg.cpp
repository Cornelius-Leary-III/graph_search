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

TEST(Dijkstras_Alg_class, get_shortest_path)
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
    
    auto outputPath_00 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 0);
    auto outputPath_01 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 1);
    auto outputPath_02 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 2);
    auto outputPath_03 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 3);
    auto outputPath_04 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 4);
    auto outputPath_05 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 5);
    
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

TEST(Dijkstras_Alg_class, reset_then_get_shortest_path)
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
    
    auto outputPath_00 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 0);
    auto outputPath_01 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 1);
    auto outputPath_02 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 2);
    auto outputPath_03 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 3);
    auto outputPath_04 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 4);
    auto outputPath_05 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 5);
    
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
    
    sourceVertex = 5;
    testDijkstraAlg.resetAll();
    
    auto outputPath_50 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 0);
    auto outputPath_51 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 1);
    auto outputPath_52 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 2);
    auto outputPath_53 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 3);
    auto outputPath_54 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 4);
    auto outputPath_55 = testDijkstraAlg.getPathFromStartToNode(sourceVertex, 5);
    
    auto expectedPath_50 = vector<int>{5, 2, 3, 0};
    auto expectedPath_51A = vector<int>{5, 4, 1};
    auto expectedPath_51B = vector<int>{5, 2, 3, 1};
    auto expectedPath_52 = vector<int>{5, 2};
    auto expectedPath_53 = vector<int>{5, 2, 3};
    auto expectedPath_54 = vector<int>{5, 4};
    auto expectedPath_55 = vector<int>{5};
    
    EXPECT_EQ(outputPath_50, expectedPath_50);
    EXPECT_TRUE(outputPath_51 == expectedPath_51A ||
                outputPath_51 == expectedPath_51B);
    EXPECT_EQ(outputPath_52, expectedPath_52);
    EXPECT_EQ(outputPath_53, expectedPath_53);
    EXPECT_EQ(outputPath_54, expectedPath_54);
    EXPECT_EQ(outputPath_55, expectedPath_55);
}












