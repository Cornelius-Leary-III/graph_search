//
// Created by cornelius on 4/23/19.
//

#include <gtest/gtest.h>
#include "Dijkstras_Alg.h"

TEST(Dijkstras_Alg_ctor, zero_nodes)
{
    Dijkstras_Alg planner(0);
    
    EXPECT_TRUE(planner.getEdgeSet().empty());
    EXPECT_TRUE(planner.getUnvisitedVertices().empty());
    
    EXPECT_TRUE(planner.getAdjacencyList().empty());
    EXPECT_TRUE(planner.getDistanceTable().empty());
    EXPECT_TRUE(planner.getPredecessorTable().empty());
    EXPECT_TRUE(planner.getVisitedTable().empty());
}

TEST(Dijkstras_Alg_ctor, finite_node_count)
{
    Dijkstras_Alg planner(10);
    
    EXPECT_TRUE(planner.getEdgeSet().empty());
    EXPECT_TRUE(planner.getUnvisitedVertices().empty());
    
    EXPECT_EQ(planner.getAdjacencyList().size(), 10);
    EXPECT_EQ(planner.getDistanceTable().size(), 10);
    EXPECT_EQ(planner.getPredecessorTable().size(), 10);
    EXPECT_EQ(planner.getVisitedTable().size(), 10);
}

TEST(add_zero_based_edges, unweighted_edges)
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
    
    Dijkstras_Alg planner(6);
    planner.addEdges(inputEdges);
    
    EXPECT_EQ(planner.getEdgeSet(), inputEdges);
    
    EXPECT_EQ(planner.getEdgeSet().size(), 9);
    EXPECT_EQ(planner.getAdjacencyList().size(), 6);
    
    auto outputAdjList = planner.getAdjacencyList();
    
    int sourceIndex = 0;
    auto destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 1);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 2);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 3);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 3);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 4);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 3);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 5);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 4);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 5);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
}

TEST(add_zero_based_edges, weighted_edges)
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
    
    Dijkstras_Alg planner(6);
    planner.addEdges(inputEdges);
    
    EXPECT_EQ(planner.getEdgeSet(), inputEdges);
    
    EXPECT_EQ(planner.getEdgeSet().size(), 9);
    EXPECT_EQ(planner.getAdjacencyList().size(), 6);
    
    auto outputAdjList = planner.getAdjacencyList();
    
    int sourceIndex = 0;
    auto destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 1);
    EXPECT_DOUBLE_EQ(destinationIter->second, 7.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 2);
    EXPECT_DOUBLE_EQ(destinationIter->second, 14.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 3);
    EXPECT_DOUBLE_EQ(destinationIter->second, 9.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 3);
    EXPECT_DOUBLE_EQ(destinationIter->second, 10.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 4);
    EXPECT_DOUBLE_EQ(destinationIter->second, 15.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 3);
    EXPECT_DOUBLE_EQ(destinationIter->second, 2.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 5);
    EXPECT_DOUBLE_EQ(destinationIter->second, 9.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 4);
    EXPECT_DOUBLE_EQ(destinationIter->second, 11.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 5);
    EXPECT_DOUBLE_EQ(destinationIter->second, 6.00);
}

TEST(add_ones_based_edges, unweighted_edges)
{
    vector<Edge> inputEdges{
            {1, 2},
            {1, 3},
            {1, 4},
            {2, 4},
            {2, 5},
            {3, 4},
            {4, 5},
            {3, 6},
            {5, 6}
    };
    
    Dijkstras_Alg planner(6);
    planner.addEdges(inputEdges);
    
    EXPECT_NE(planner.getEdgeSet(), inputEdges);
    
    EXPECT_EQ(planner.getEdgeSet().size(), 9);
    EXPECT_EQ(planner.getAdjacencyList().size(), 6);
    
    auto outputAdjList = planner.getAdjacencyList();
    
    int sourceIndex = 0;
    auto destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 1);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 2);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 3);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 3);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 4);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 3);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 5);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 4);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 5);
    EXPECT_DOUBLE_EQ(destinationIter->second, 1.00);
}

TEST(add_ones_based_edges, weighted_edges)
{
    vector<Edge> inputEdges{
            {1, 2, 7},
            {1, 3, 14},
            {1, 4, 9},
            {2, 4, 10},
            {2, 5, 15},
            {3, 4, 2},
            {4, 5, 11},
            {3, 6, 9},
            {5, 6, 6}
    };
    
    Dijkstras_Alg planner(6);
    planner.addEdges(inputEdges);
    
    EXPECT_NE(planner.getEdgeSet(), inputEdges);
    
    EXPECT_EQ(planner.getEdgeSet().size(), 9);
    EXPECT_EQ(planner.getAdjacencyList().size(), 6);
    
    auto outputAdjList = planner.getAdjacencyList();
    
    int sourceIndex = 0;
    auto destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 1);
    EXPECT_DOUBLE_EQ(destinationIter->second, 7.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 2);
    EXPECT_DOUBLE_EQ(destinationIter->second, 14.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 3);
    EXPECT_DOUBLE_EQ(destinationIter->second, 9.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 3);
    EXPECT_DOUBLE_EQ(destinationIter->second, 10.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 4);
    EXPECT_DOUBLE_EQ(destinationIter->second, 15.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 3);
    EXPECT_DOUBLE_EQ(destinationIter->second, 2.00);
    
    ++destinationIter;
    EXPECT_EQ(destinationIter->first, 5);
    EXPECT_DOUBLE_EQ(destinationIter->second, 9.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 4);
    EXPECT_DOUBLE_EQ(destinationIter->second, 11.00);
    
    ++sourceIndex;
    destinationIter = outputAdjList[sourceIndex].begin();
    
    EXPECT_EQ(destinationIter->first, 5);
    EXPECT_DOUBLE_EQ(destinationIter->second, 6.00);
}

TEST(add_edges, all_pos_edge_weights)
{
    vector<Edge> inputEdges{
            {1, 2, 7},
            {1, 3, 14},
            {1, 4, 9},
            {2, 4, 10},
            {2, 5, 15},
            {3, 4, 2},
            {4, 5, 11},
            {3, 6, 9},
            {5, 6, 6}
    };
    
    Dijkstras_Alg planner(6);
    
    EXPECT_NO_THROW(planner.addEdges(inputEdges));
}

TEST(add_edges, mixed_pos_neg_edge_weights)
{
    vector<Edge> inputEdges{
            {1, 2, 7},
            {1, 3, -14},
            {1, 4, -9},
            {2, 4, 10},
            {2, 5, 15},
            {3, 4, -2},
            {4, 5, 11},
            {3, 6, 9},
            {5, 6, -6}
    };
    
    Dijkstras_Alg planner(6);
    
    EXPECT_THROW(planner.addEdges(inputEdges), NegativeEdgeWeightsException);
}
