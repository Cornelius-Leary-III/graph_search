//
// Created by carpenter on 2/9/19.
//

#include <gtest/gtest.h>
#include "Bellman_Ford_Shortest_Path.h"

bool operator==(const Edge& lhs, const Edge& rhs)
{
    return (lhs.source == rhs.source) &&
           (lhs.destination == rhs.destination) &&
           (lhs.weight == rhs.weight);
}

bool operator!=(const Edge& lhs, const Edge& rhs)
{
    return !(lhs == rhs);
}

TEST(Bellman_Ford_Shortest_Path_class, constructor_num_nodes)
{
    unsigned long testNodeCount = 5;
    Bellman_Ford_Shortest_Path testPlanner(testNodeCount);
    
    auto outputDistanceTable = testPlanner.getDistanceTable();
    auto outputPredecessorTable = testPlanner.getPredecessorTable();
    //    auto outputDistTableSteppedThrough = testPlanner.getSteppedThroughDistanceTable();
    //    auto outputPredTableSteppedThrough = testPlanner.getSteppedThroughPredecessorTable();
    
    EXPECT_EQ(outputDistanceTable.size(), testNodeCount);
    EXPECT_EQ(outputDistanceTable[0], MAXDOUBLE);
    
    EXPECT_EQ(outputPredecessorTable.size(), testNodeCount);
    EXPECT_EQ(outputPredecessorTable[0], -1);
    
    //    EXPECT_TRUE(outputDistTableSteppedThrough.empty());
    //    EXPECT_TRUE(outputPredTableSteppedThrough.empty());
}

TEST(Bellman_Ford_Shortest_Path_class, add_zero_based_edges)
{
    unsigned long testNodeCount = 5;
    Bellman_Ford_Shortest_Path testPlanner(testNodeCount);
    
    vector<Edge> inputEdges{
            {0, 1, -1},
            {0, 2, 4},
            {1, 2, 3},
            {1, 3, 2},
            {1, 4, 2},
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, -3}
    };
    
    EXPECT_NO_THROW(testPlanner.addEdges(inputEdges));
    
    auto outputDistanceTable = testPlanner.getDistanceTable();
    auto outputPredecessorTable = testPlanner.getPredecessorTable();
    //    auto outputDistTableSteppedThrough = testPlanner.getSteppedThroughDistanceTable();
    //    auto outputPredTableSteppedThrough = testPlanner.getSteppedThroughPredecessorTable();
    
    EXPECT_EQ(outputDistanceTable.size(), testNodeCount);
    EXPECT_EQ(outputDistanceTable[0], MAXDOUBLE);
    
    EXPECT_EQ(outputPredecessorTable.size(), testNodeCount);
    EXPECT_EQ(outputPredecessorTable[0], -1);
    
    //    EXPECT_TRUE(outputDistTableSteppedThrough.empty());
    //    EXPECT_TRUE(outputPredTableSteppedThrough.empty());
    
    auto outputEdges = testPlanner.getEdgeSet();
    EXPECT_TRUE(outputEdges == inputEdges);
}

TEST(Bellman_Ford_Shortest_Path_class, add_one_based_edges)
{
    unsigned long testNodeCount = 5;
    Bellman_Ford_Shortest_Path testPlanner(testNodeCount);
    
    vector<Edge> inputEdges{
            {1, 2, -1},
            {1, 3, 4},
            {2, 4, 3},
            {2, 4, 2},
            {2, 5, 2},
            {4, 2, 1},
            {4, 3, 5},
            {5, 4, -3}
    };
    
    EXPECT_NO_THROW(testPlanner.addEdges(inputEdges));
    
    auto outputDistanceTable = testPlanner.getDistanceTable();
    auto outputPredecessorTable = testPlanner.getPredecessorTable();
    //    auto outputDistTableSteppedThrough = testPlanner.getSteppedThroughDistanceTable();
    //    auto outputPredTableSteppedThrough = testPlanner.getSteppedThroughPredecessorTable();
    
    EXPECT_EQ(outputDistanceTable.size(), testNodeCount);
    EXPECT_EQ(outputDistanceTable[0], MAXDOUBLE);
    
    EXPECT_EQ(outputPredecessorTable.size(), testNodeCount);
    EXPECT_EQ(outputPredecessorTable[0], -1);
    
    //    EXPECT_TRUE(outputDistTableSteppedThrough.empty());
    //    EXPECT_TRUE(outputPredTableSteppedThrough.empty());
    
    auto outputEdges = testPlanner.getEdgeSet();
    EXPECT_FALSE(outputEdges == inputEdges);
}

TEST(Bellman_Ford_Shortest_Path_class, process_graph)
{
    unsigned long testNodeCount = 5;
    Bellman_Ford_Shortest_Path testPlanner(testNodeCount);
    
    vector<Edge> inputEdges{
            {0, 1, -1},
            {0, 2, 4},
            {1, 2, 3},
            {1, 3, 2},
            {1, 4, 2},
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, -3}
    };
    
    EXPECT_NO_THROW(testPlanner.addEdges(inputEdges));
    
    int sourceVertex = 0;
    EXPECT_NO_THROW(testPlanner.processGraph(sourceVertex));
    
    auto outputDistanceTable = testPlanner.getDistanceTable();
    auto outputPredecessorTable = testPlanner.getPredecessorTable();
    //    auto outputDistTableSteppedThrough = testPlanner.getSteppedThroughDistanceTable();
    //    auto outputPredTableSteppedThrough = testPlanner.getSteppedThroughPredecessorTable();
    
    EXPECT_EQ(outputDistanceTable.size(), testNodeCount);
    EXPECT_EQ(outputDistanceTable[sourceVertex], 0);
    
    vector<double> expectedDistanceTable{0, -1, 2, -2, 1};
    EXPECT_EQ(outputDistanceTable, expectedDistanceTable);
    
    EXPECT_EQ(outputPredecessorTable.size(), testNodeCount);
    EXPECT_EQ(outputPredecessorTable[sourceVertex], -1);
    
    //    EXPECT_FALSE(outputDistTableSteppedThrough.empty());
    //    EXPECT_FALSE(outputPredTableSteppedThrough.empty());
    
    //    vector<vector<double>> expectedSteppedThroughDistTable{
    //            {0, MAXDOUBLE, MAXDOUBLE, MAXDOUBLE, MAXDOUBLE},
    //            {0, -1,        MAXDOUBLE, MAXDOUBLE, MAXDOUBLE},
    //            {0, -1, 4,                MAXDOUBLE, MAXDOUBLE},
    //            {0, -1, 2,                MAXDOUBLE, MAXDOUBLE},
    //            {0, -1, 2,                MAXDOUBLE, 1},
    //            {0, -1, 2, 1,                        1},
    //            {0, -1, 2, -2,                       1}
    //    };
    //
    //    EXPECT_EQ(outputDistTableSteppedThrough, expectedSteppedThroughDistTable);
    
    auto outputEdges = testPlanner.getEdgeSet();
    EXPECT_TRUE(outputEdges == inputEdges);
}


