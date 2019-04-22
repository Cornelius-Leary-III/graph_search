//
// Created by cornelius on 4/22/19.
//

#include "Edge.h"
#include <gtest/gtest.h>

TEST(Edge_ctor, default_ctor)
{
    Edge testEdge;
    
    EXPECT_EQ(testEdge.source, 0);
    EXPECT_EQ(testEdge.destination, 0);
    EXPECT_DOUBLE_EQ(testEdge.weight, 0.0);
}

TEST(Edge_params_ctor, source_destination)
{
    Edge testEdge(5, 10);
    
    EXPECT_EQ(testEdge.source, 5);
    EXPECT_EQ(testEdge.destination, 10);
    EXPECT_DOUBLE_EQ(testEdge.weight, 1.0);
}

TEST(Edge_params_ctor, source_destination_weight)
{
    Edge testEdge(5, 10, 3.50);
    
    EXPECT_EQ(testEdge.source, 5);
    EXPECT_EQ(testEdge.destination, 10);
    EXPECT_DOUBLE_EQ(testEdge.weight, 3.50);
}

TEST(Edge_copy_ctor, valid_edge)
{
    Edge edgeToCopy(3, 9, 7.25);
    
    Edge testEdge = edgeToCopy;
    
    EXPECT_EQ(testEdge.source, 3);
    EXPECT_EQ(testEdge.destination, 9);
    EXPECT_DOUBLE_EQ(testEdge.weight, 7.25);
}

TEST(Edge_copy_assignment, valid_edge)
{
    Edge edgeToCopy(3, 9, 7.25);
    
    Edge testEdge = edgeToCopy;
    
    EXPECT_EQ(testEdge.source, 3);
    EXPECT_EQ(testEdge.destination, 9);
    EXPECT_DOUBLE_EQ(testEdge.weight, 7.25);
}

TEST(Edge_comparisons, equivalent_edges)
{
    Edge firstEdge(1, 2, 5.00);
    Edge secondEdge(1, 2, 5.00);
    
    EXPECT_TRUE(firstEdge == secondEdge);
    EXPECT_FALSE(firstEdge != secondEdge);
}

TEST(Edge_comparisons, different_edges)
{
    Edge firstEdge(1, 2, 5.00);
    Edge secondEdge(1, 2, 2.5);
    
    EXPECT_FALSE(firstEdge == secondEdge);
    EXPECT_TRUE(firstEdge != secondEdge);
}

