//
// Created by cornelius on 4/22/19.
//

#include <gtest/gtest.h>
#include "EdgeSetBuilder.h"

TEST(EdgeSetBuilderCtor, defaultCtor)
{
   EdgeSetBuilder builder;

   EXPECT_TRUE(builder.isGraphDirected());
   EXPECT_FALSE(builder.areNegativeEdgesAllowed());
   EXPECT_FALSE(builder.areSelfLoopsAllowed());

   EXPECT_TRUE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilderSettingsParamCtor, fff)
{
   EdgeSetBuilder builder(false, false, false);

   EXPECT_FALSE(builder.isGraphDirected());
   EXPECT_FALSE(builder.areNegativeEdgesAllowed());
   EXPECT_FALSE(builder.areSelfLoopsAllowed());

   EXPECT_TRUE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilderSettingsParamCtor, fft)
{
   EdgeSetBuilder builder(false, false, true);

   EXPECT_FALSE(builder.isGraphDirected());
   EXPECT_FALSE(builder.areNegativeEdgesAllowed());
   EXPECT_TRUE(builder.areSelfLoopsAllowed());

   EXPECT_TRUE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilderSettingsParamCtor, ftf)
{
   EdgeSetBuilder builder(false, true, false);

   EXPECT_FALSE(builder.isGraphDirected());
   EXPECT_TRUE(builder.areNegativeEdgesAllowed());
   EXPECT_FALSE(builder.areSelfLoopsAllowed());

   EXPECT_TRUE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilderSettingsParamCtor, ftt)
{
   EdgeSetBuilder builder(false, true, true);

   EXPECT_FALSE(builder.isGraphDirected());
   EXPECT_TRUE(builder.areNegativeEdgesAllowed());
   EXPECT_TRUE(builder.areSelfLoopsAllowed());

   EXPECT_TRUE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilderSettingsParamCtor, tff)
{
   EdgeSetBuilder builder(true, false, false);

   EXPECT_TRUE(builder.isGraphDirected());
   EXPECT_FALSE(builder.areNegativeEdgesAllowed());
   EXPECT_FALSE(builder.areSelfLoopsAllowed());

   EXPECT_TRUE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilderSettingsParamCtor, tft)
{
   EdgeSetBuilder builder(true, false, true);

   EXPECT_TRUE(builder.isGraphDirected());
   EXPECT_FALSE(builder.areNegativeEdgesAllowed());
   EXPECT_TRUE(builder.areSelfLoopsAllowed());

   EXPECT_TRUE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilderSettingsParamCtor, ttf)
{
   EdgeSetBuilder builder(true, true, false);

   EXPECT_TRUE(builder.isGraphDirected());
   EXPECT_TRUE(builder.areNegativeEdgesAllowed());
   EXPECT_FALSE(builder.areSelfLoopsAllowed());

   EXPECT_TRUE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilderSettingsParamCtor, ttt)
{
   EdgeSetBuilder builder(true, true, true);

   EXPECT_TRUE(builder.isGraphDirected());
   EXPECT_TRUE(builder.areNegativeEdgesAllowed());
   EXPECT_TRUE(builder.areSelfLoopsAllowed());

   EXPECT_TRUE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilderEdgeSetCtor, allPositiveWeightsDirectedEdges)
{
   std::vector<Edge> input_edges{{"0", "1", 1}, // reused this edge set from test_Bellman_Ford.cpp,
                                 {"0", "2", 4}, //      but gave all edges positive weights.
                                 {"1", "2", 3},
                                 {"1", "3", 2},
                                 {"1", "4", 2},
                                 {"3", "1", 1},
                                 {"3", "2", 5},
                                 {"4", "3", 3}};

   EdgeSetBuilder builder(input_edges);

   EXPECT_TRUE(builder.isGraphDirected());
   EXPECT_FALSE(builder.areNegativeEdgesAllowed());
   EXPECT_FALSE(builder.areSelfLoopsAllowed());

   EXPECT_FALSE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 8);
}

TEST(EdgeSetBuilderEdgeSetCtor, mixedSignWeightsDirectedEdges)
{
   std::vector<Edge> input_edges{
      {"0", "1", -1}, // changed this edge.
      {"0", "2", 4},
      {"1", "2", 3},
      {"1", "3", 2},
      {"1", "4", 2},
      {"3", "1", 1},
      {"3", "2", 5},
      {"4", "3", -3} // changed this edge.
   };

   EdgeSetBuilder builder(input_edges);

   EXPECT_TRUE(builder.isGraphDirected());
   EXPECT_TRUE(builder.areNegativeEdgesAllowed());
   EXPECT_FALSE(builder.areSelfLoopsAllowed());

   EXPECT_FALSE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 8);
}

TEST(EdgeSetBuilderEdgeSetCtor, mixedSignWeightsDirectedEdgesSelfLoops)
{
   std::vector<Edge> input_edges{{"0", "1", -1},
                                 {"0", "2", 4},
                                 {"1", "2", 3},
                                 {"1", "3", 2},
                                 {"1", "1", 2}, // changed this edge.
                                 {"3", "1", 1},
                                 {"3", "2", 5},
                                 {"4", "3", -3}};

   EdgeSetBuilder builder(input_edges);

   EXPECT_TRUE(builder.isGraphDirected());
   EXPECT_TRUE(builder.areNegativeEdgesAllowed());
   EXPECT_TRUE(builder.areSelfLoopsAllowed());

   EXPECT_FALSE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 8);
}

TEST(EdgeSetBuilderEdgeSetCtor, allPositiveWeightsUndirectedEdges)
{
   std::vector<Edge> input_edges{{"0", "1", 1}, // reused this edge set from test_Bellman_Ford.cpp,
                                 {"0", "2", 4}, //      but gave all edges positive weights.
                                 {"1", "2", 3},
                                 {"1", "3", 2},
                                 {"1", "4", 2},
                                 {"3", "1", 1},
                                 {"3", "2", 5},
                                 {"4", "3", 3}};

   EdgeSetBuilder builder(input_edges, false);

   EXPECT_FALSE(builder.isGraphDirected());
   EXPECT_FALSE(builder.areNegativeEdgesAllowed());
   EXPECT_FALSE(builder.areSelfLoopsAllowed());

   EXPECT_FALSE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 16);
}

TEST(EdgeSetBuilderEdgeSetCtor, mixedSignWeightsUndirectedEdges)
{
   std::vector<Edge> input_edges{
      {"0", "1", -1}, // changed this edge.
      {"0", "2", 4},
      {"1", "2", 3},
      {"1", "3", 2},
      {"1", "4", 2},
      {"3", "1", 1},
      {"3", "2", 5},
      {"4", "3", -3} // changed this edge.
   };

   EdgeSetBuilder builder(input_edges, false);

   EXPECT_FALSE(builder.isGraphDirected());
   EXPECT_TRUE(builder.areNegativeEdgesAllowed());
   EXPECT_FALSE(builder.areSelfLoopsAllowed());

   EXPECT_FALSE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 16);
}

TEST(EdgeSetBuilderEdgeSetCtor, mixedSignWeightsUndirectedEdgesSelfLoops)
{
   std::vector<Edge> input_edges{{"0", "1", -1},
                                 {"0", "2", 4},
                                 {"1", "2", 3},
                                 {"1", "3", 2},
                                 {"1", "1", 2}, // changed this edge.
                                 {"3", "1", 1},
                                 {"3", "2", 5},
                                 {"4", "3", -3}};

   EdgeSetBuilder builder(input_edges, false);

   EXPECT_FALSE(builder.isGraphDirected());
   EXPECT_TRUE(builder.areNegativeEdgesAllowed());
   EXPECT_TRUE(builder.areSelfLoopsAllowed());

   EXPECT_FALSE(builder.getEdgeSet().empty());
   EXPECT_EQ(builder.getEdgeCount(), 16);
}

TEST(EdgeSetBuilderCopyCtor, validESB)
{
   std::vector<Edge> input_edges{{"0", "1", -1},
                                 {"0", "2", 4},
                                 {"1", "2", 3},
                                 {"1", "3", 2},
                                 {"1", "1", 2},
                                 {"3", "1", 1},
                                 {"3", "2", 5},
                                 {"4", "3", -3}};

   EdgeSetBuilder builderToCopy(input_edges);

   EdgeSetBuilder testBuilder(builderToCopy);

   EXPECT_TRUE(testBuilder.isGraphDirected());
   EXPECT_TRUE(testBuilder.areNegativeEdgesAllowed());
   EXPECT_TRUE(testBuilder.areSelfLoopsAllowed());

   EXPECT_FALSE(testBuilder.getEdgeSet().empty());
   EXPECT_EQ(testBuilder.getEdgeCount(), 8);
}

TEST(createAndAppendDirectedEdge, positiveWeight)
{
   EdgeSetBuilder builder;

   builder.createAndAppendEdge("5", "20", 2.00);

   auto output_edges = builder.getEdgeSet();

   EXPECT_EQ(builder.getEdgeCount(), 1);

   EXPECT_EQ(output_edges.front().mSource.mName, "5");
   EXPECT_EQ(output_edges.front().mDestination.mName, "20");
   EXPECT_DOUBLE_EQ(output_edges.front().mWeight, 2.00);
}

TEST(createAndAppendDirectedEdge, negativeWeightIsAllowed)
{
   EdgeSetBuilder builder(true, true, true);

   builder.createAndAppendEdge("1", "5", -4.00);

   auto output_edges = builder.getEdgeSet();

   EXPECT_EQ(builder.getEdgeCount(), 1);

   EXPECT_EQ(output_edges.front().mSource.mName, "1");
   EXPECT_EQ(output_edges.front().mDestination.mName, "5");
   EXPECT_DOUBLE_EQ(output_edges.front().mWeight, -4.00);
}

TEST(createAndAppendDirectedEdge, negativeWeightIsNotAllowed)
{
   EdgeSetBuilder builder(true, false, true);

   builder.createAndAppendEdge("1", "5", -4.00);

   auto output_edges = builder.getEdgeSet();

   EXPECT_EQ(builder.getEdgeCount(), 0);

   EXPECT_TRUE(output_edges.empty());
}

TEST(createAndAppendDirectedEdge, selfLoopIsAllowed)
{
   EdgeSetBuilder builder(true, true, true);

   builder.createAndAppendEdge("1", "1");

   auto output_edges = builder.getEdgeSet();

   EXPECT_EQ(builder.getEdgeCount(), 1);

   EXPECT_EQ(output_edges.front().mSource.mName, "1");
   EXPECT_EQ(output_edges.front().mDestination.mName, "1");
   EXPECT_DOUBLE_EQ(output_edges.front().mWeight, 1.00);
}

TEST(createAndAppendDirectedEdge, selfLoopIsNotAllowed)
{
   EdgeSetBuilder builder(true, true, false);

   builder.createAndAppendEdge("1", "1");

   auto output_edges = builder.getEdgeSet();

   EXPECT_EQ(builder.getEdgeCount(), 0);

   EXPECT_TRUE(output_edges.empty());
}

TEST(createAndAppendUndirectedEdge, positiveWeight)
{
   EdgeSetBuilder builder(false, true, true);

   builder.createAndAppendEdge("5", "20", 2.00);

   auto output_edges = builder.getEdgeSet();

   EXPECT_EQ(builder.getEdgeCount(), 2);

   EXPECT_EQ(output_edges.front().mSource.mName, "5");
   EXPECT_EQ(output_edges.front().mDestination.mName, "20");
   EXPECT_DOUBLE_EQ(output_edges.front().mWeight, 2.00);
}

TEST(createAndAppendUndirectedEdge, negativeWeightIsAllowed)
{
   EdgeSetBuilder builder(false, true, true);

   builder.createAndAppendEdge("1", "5", -4.00);

   auto output_edges = builder.getEdgeSet();

   EXPECT_EQ(builder.getEdgeCount(), 2);

   EXPECT_EQ(output_edges.front().mSource.mName, "1");
   EXPECT_EQ(output_edges.front().mDestination.mName, "5");
   EXPECT_DOUBLE_EQ(output_edges.front().mWeight, -4.00);
}

TEST(createAndAppendUndirectedEdge, negativeWeightIsNotAllowed)
{
   EdgeSetBuilder builder(false, false, true);

   builder.createAndAppendEdge("1", "5", -4.00);

   auto output_edges = builder.getEdgeSet();

   EXPECT_EQ(builder.getEdgeCount(), 0);

   EXPECT_TRUE(output_edges.empty());
}

TEST(createAndAppendUndirectedEdge, selfLoopIsAllowed)
{
   EdgeSetBuilder builder(false, true, true);

   builder.createAndAppendEdge("1", "1");

   auto output_edges = builder.getEdgeSet();

   EXPECT_EQ(builder.getEdgeCount(), 2);

   EXPECT_EQ(output_edges.front().mSource.mName, "1");
   EXPECT_EQ(output_edges.front().mDestination.mName, "1");
   EXPECT_DOUBLE_EQ(output_edges.front().mWeight, 1.00);
}

TEST(createAndAppendUndirectedEdge, selfLoopIsNotAllowed)
{
   EdgeSetBuilder builder(false, true, false);

   builder.createAndAppendEdge("1", "1");

   auto output_edges = builder.getEdgeSet();

   EXPECT_EQ(builder.getEdgeCount(), 0);

   EXPECT_TRUE(output_edges.empty());
}
