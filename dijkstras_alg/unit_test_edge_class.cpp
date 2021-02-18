//
// Created by cornelius on 4/22/19.
//

#include "Edge.h"
#include <gtest/gtest.h>

TEST(EdgeCtor, defaultCtor)
{
   Edge test_edge;

   EXPECT_EQ(test_edge.mSource, 0);
   EXPECT_EQ(test_edge.mDestination, 0);
   EXPECT_DOUBLE_EQ(test_edge.mWeight, 0.0);
}

TEST(EdgeParamsCtor, source_destination)
{
   Edge test_edge(5, 10);

   EXPECT_EQ(test_edge.mSource, 5);
   EXPECT_EQ(test_edge.mDestination, 10);
   EXPECT_DOUBLE_EQ(test_edge.mWeight, 1.0);
}

TEST(EdgeParamsCtor, source_destination_weight)
{
   Edge test_edge(5, 10, 3.50);

   EXPECT_EQ(test_edge.mSource, 5);
   EXPECT_EQ(test_edge.mDestination, 10);
   EXPECT_DOUBLE_EQ(test_edge.mWeight, 3.50);
}

TEST(EdgeCopyCtor, valid_edge)
{
   Edge edge_to_copy(3, 9, 7.25);

   Edge test_edge = edge_to_copy;

   EXPECT_EQ(test_edge.mSource, 3);
   EXPECT_EQ(test_edge.mDestination, 9);
   EXPECT_DOUBLE_EQ(test_edge.mWeight, 7.25);
}

TEST(EdgeCopyAssignment, valid_edge)
{
   Edge edge_to_copy(3, 9, 7.25);

   Edge test_edge = edge_to_copy;

   EXPECT_EQ(test_edge.mSource, 3);
   EXPECT_EQ(test_edge.mDestination, 9);
   EXPECT_DOUBLE_EQ(test_edge.mWeight, 7.25);
}

TEST(EdgeComparisons, equivalent_edges)
{
   Edge first_edge(1, 2, 5.00);
   Edge second_edge(1, 2, 5.00);

   EXPECT_TRUE(first_edge == second_edge);
   EXPECT_FALSE(first_edge != second_edge);
}

TEST(EdgeComparisons, different_edges)
{
   Edge first_edge(1, 2, 5.00);
   Edge second_edge(1, 2, 2.5);

   EXPECT_FALSE(first_edge == second_edge);
   EXPECT_TRUE(first_edge != second_edge);
}
