//
// Created by cornelius on 4/22/19.
//

#include <gtest/gtest.h>
#include "EdgeSetBuilder.h"

TEST(EdgeSetBuilder_ctor, default_ctor)
{
    EdgeSetBuilder builder;
    
    EXPECT_TRUE(builder.isGraphDirected());
    EXPECT_FALSE(builder.areNegativeEdgesAllowed());
    EXPECT_FALSE(builder.areSelfLoopsAllowed());
    
    EXPECT_TRUE(builder.getEdgeSet().empty());
    EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilder_settings_param_ctor, fff)
{
    EdgeSetBuilder builder(false, false, false);
    
    EXPECT_FALSE(builder.isGraphDirected());
    EXPECT_FALSE(builder.areNegativeEdgesAllowed());
    EXPECT_FALSE(builder.areSelfLoopsAllowed());
    
    EXPECT_TRUE(builder.getEdgeSet().empty());
    EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilder_settings_param_ctor, fft)
{
    EdgeSetBuilder builder(false, false, true);
    
    EXPECT_FALSE(builder.isGraphDirected());
    EXPECT_FALSE(builder.areNegativeEdgesAllowed());
    EXPECT_TRUE(builder.areSelfLoopsAllowed());
    
    EXPECT_TRUE(builder.getEdgeSet().empty());
    EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilder_settings_param_ctor, ftf)
{
    EdgeSetBuilder builder(false, true, false);
    
    EXPECT_FALSE(builder.isGraphDirected());
    EXPECT_TRUE(builder.areNegativeEdgesAllowed());
    EXPECT_FALSE(builder.areSelfLoopsAllowed());
    
    EXPECT_TRUE(builder.getEdgeSet().empty());
    EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilder_settings_param_ctor, ftt)
{
    EdgeSetBuilder builder(false, true, true);
    
    EXPECT_FALSE(builder.isGraphDirected());
    EXPECT_TRUE(builder.areNegativeEdgesAllowed());
    EXPECT_TRUE(builder.areSelfLoopsAllowed());
    
    EXPECT_TRUE(builder.getEdgeSet().empty());
    EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilder_settings_param_ctor, tff)
{
    EdgeSetBuilder builder(true, false, false);
    
    EXPECT_TRUE(builder.isGraphDirected());
    EXPECT_FALSE(builder.areNegativeEdgesAllowed());
    EXPECT_FALSE(builder.areSelfLoopsAllowed());
    
    EXPECT_TRUE(builder.getEdgeSet().empty());
    EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilder_settings_param_ctor, tft)
{
    EdgeSetBuilder builder(true, false, true);
    
    EXPECT_TRUE(builder.isGraphDirected());
    EXPECT_FALSE(builder.areNegativeEdgesAllowed());
    EXPECT_TRUE(builder.areSelfLoopsAllowed());
    
    EXPECT_TRUE(builder.getEdgeSet().empty());
    EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilder_settings_param_ctor, ttf)
{
    EdgeSetBuilder builder(true, true, false);
    
    EXPECT_TRUE(builder.isGraphDirected());
    EXPECT_TRUE(builder.areNegativeEdgesAllowed());
    EXPECT_FALSE(builder.areSelfLoopsAllowed());
    
    EXPECT_TRUE(builder.getEdgeSet().empty());
    EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilder_settings_param_ctor, ttt)
{
    EdgeSetBuilder builder(true, true, true);
    
    EXPECT_TRUE(builder.isGraphDirected());
    EXPECT_TRUE(builder.areNegativeEdgesAllowed());
    EXPECT_TRUE(builder.areSelfLoopsAllowed());
    
    EXPECT_TRUE(builder.getEdgeSet().empty());
    EXPECT_EQ(builder.getEdgeCount(), 0);
}

TEST(EdgeSetBuilder_edge_set_ctor, all_positive_weights_directed_edges)
{
    vector<Edge> inputEdges{
            {0, 1, 1},          // reused this edge set from test_Bellman_Ford.cpp,
            {0, 2, 4},          //      but gave all edges positive weights.
            {1, 2, 3},
            {1, 3, 2},
            {1, 4, 2},
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, 3}
    };
    
    EdgeSetBuilder builder(inputEdges);
    
    EXPECT_TRUE(builder.isGraphDirected());
    EXPECT_FALSE(builder.areNegativeEdgesAllowed());
    EXPECT_FALSE(builder.areSelfLoopsAllowed());
    
    EXPECT_FALSE(builder.getEdgeSet().empty());
    EXPECT_EQ(builder.getEdgeCount(), 8);
}

TEST(EdgeSetBuilder_edge_set_ctor, mixed_sign_weights_directed_edges)
{
    vector<Edge> inputEdges{
            {0, 1, -1},         // changed this edge.
            {0, 2, 4},
            {1, 2, 3},
            {1, 3, 2},
            {1, 4, 2},
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, -3}          // changed this edge.
    };
    
    EdgeSetBuilder builder(inputEdges);
    
    EXPECT_TRUE(builder.isGraphDirected());
    EXPECT_TRUE(builder.areNegativeEdgesAllowed());
    EXPECT_FALSE(builder.areSelfLoopsAllowed());
    
    EXPECT_FALSE(builder.getEdgeSet().empty());
    EXPECT_EQ(builder.getEdgeCount(), 8);
}

TEST(EdgeSetBuilder_edge_set_ctor, mixed_sign_weights_directed_edges_self_loops)
{
    vector<Edge> inputEdges{
            {0, 1, -1},
            {0, 2, 4},
            {1, 2, 3},
            {1, 3, 2},
            {1, 1, 2},          // changed this edge.
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, -3}
    };
    
    EdgeSetBuilder builder(inputEdges);
    
    EXPECT_TRUE(builder.isGraphDirected());
    EXPECT_TRUE(builder.areNegativeEdgesAllowed());
    EXPECT_TRUE(builder.areSelfLoopsAllowed());
    
    EXPECT_FALSE(builder.getEdgeSet().empty());
    EXPECT_EQ(builder.getEdgeCount(), 8);
}

TEST(EdgeSetBuilder_copy_ctor, valid_ESB)
{
    vector<Edge> inputEdges{
            {0, 1, -1},
            {0, 2, 4},
            {1, 2, 3},
            {1, 3, 2},
            {1, 1, 2},
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, -3}
    };
    
    EdgeSetBuilder builderToCopy(inputEdges);
    
    EdgeSetBuilder testBuilder(builderToCopy);
    
    EXPECT_TRUE(testBuilder.isGraphDirected());
    EXPECT_TRUE(testBuilder.areNegativeEdgesAllowed());
    EXPECT_TRUE(testBuilder.areSelfLoopsAllowed());
    
    EXPECT_FALSE(testBuilder.getEdgeSet().empty());
    EXPECT_EQ(testBuilder.getEdgeCount(), 8);
}
