//
// Created by cornelius on 4/23/19.
//

#include <gtest/gtest.h>
#include "EdgeImporter.h"

TEST(EdgeImporter_params_ctor, no_file_given)
{
    EdgeImporter importer("");
    
    EXPECT_FALSE(importer.isFileValid());
}

TEST(EdgeImporter_params_ctor, file_does_not_exist)
{
    EdgeImporter importer("file_does_not_exist.txt");
    
    EXPECT_FALSE(importer.isFileValid());
}

TEST(EdgeImporter_params_ctor, empty_file)
{
    EdgeImporter importer("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/empty_file.txt");
    
    EXPECT_TRUE(importer.isFileValid());
}

TEST(EdgeImporter_params_ctor, valid_file)
{
    EdgeImporter importer("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/non_empty_file.txt");
    
    EXPECT_TRUE(importer.isFileValid());
}

TEST(setup_edge_builder, default_settings)
{
    EdgeImporter importer("");
    
    importer.setupEdgeBuilder();
    
    auto outputESB = importer.getEdgeBuilder();
    
    EXPECT_TRUE(outputESB.isGraphDirected());
    EXPECT_TRUE(outputESB.areNegativeEdgesAllowed());
    EXPECT_TRUE(outputESB.areSelfLoopsAllowed());
}

TEST(setup_edge_builder, custom_settings)
{
    EdgeImporter importer("");
    
    importer.setupEdgeBuilder(true, false, false);
    
    auto outputESB = importer.getEdgeBuilder();
    
    EXPECT_TRUE(outputESB.isGraphDirected());
    EXPECT_FALSE(outputESB.areNegativeEdgesAllowed());
    EXPECT_FALSE(outputESB.areSelfLoopsAllowed());
}

TEST(read_invalid_graph_file, no_file_given)
{
    EdgeImporter importer("");
    
    importer.readGraphFile();
    
    EXPECT_TRUE(importer.getEdges().empty());
    
    EXPECT_EQ(importer.getStartNode(), 0);
    EXPECT_EQ(importer.getGoalNode(), 0);
    EXPECT_EQ(importer.getNumberOfNodes(), 0);
}

TEST(read_invalid_graph_file, file_does_not_exist)
{
    EdgeImporter importer("invalid_file.txt");
    
    importer.readGraphFile();
    
    EXPECT_TRUE(importer.getEdges().empty());
    
    EXPECT_EQ(importer.getStartNode(), 0);
    EXPECT_EQ(importer.getGoalNode(), 0);
    EXPECT_EQ(importer.getNumberOfNodes(), 0);
}

TEST(read_invalid_graph_file, empty_file)
{
    EdgeImporter importer("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/empty_file.txt");
    
    importer.readGraphFile();
    
    EXPECT_TRUE(importer.getEdges().empty());
    
    EXPECT_EQ(importer.getStartNode(), 0);
    EXPECT_EQ(importer.getGoalNode(), 0);
    EXPECT_EQ(importer.getNumberOfNodes(), 0);
}

TEST(read_invalid_graph_file, setup_info_is_incorrect)
{
    EdgeImporter importer("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/setup_syntax_wrong.txt");
    
    importer.readGraphFile();
    
    EXPECT_TRUE(importer.getEdges().empty());
    
    EXPECT_EQ(importer.getStartNode(), 0);
    EXPECT_EQ(importer.getGoalNode(), 0);
    EXPECT_EQ(importer.getNumberOfNodes(), 0);
}

TEST(read_invalid_graph_file, setup_info_correct_missing_edges)
{
    EdgeImporter importer("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/missing_edges.txt");
    
    importer.readGraphFile();
    
    EXPECT_TRUE(importer.getEdges().empty());
    
    EXPECT_EQ(importer.getStartNode(), 1);
    EXPECT_EQ(importer.getGoalNode(), 20);
    EXPECT_EQ(importer.getNumberOfNodes(), 25);
}

TEST(read_valid_graph_file, single_edge)
{
    EdgeImporter importer("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/single_edge.txt");
    
    importer.readGraphFile();
    
    EXPECT_FALSE(importer.getEdges().empty());
    
    auto edge = importer.getEdges().front();
    
    EXPECT_EQ(edge.source, 1);
    EXPECT_EQ(edge.destination, 2);
    EXPECT_DOUBLE_EQ(edge.weight, 1.50);
    
    EXPECT_EQ(importer.getStartNode(), 1);
    EXPECT_EQ(importer.getGoalNode(), 2);
    EXPECT_EQ(importer.getNumberOfNodes(), 2);
}

TEST(read_valid_graph_file, multiple_edges)
{
    EdgeImporter importer("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/multiple_edges.txt");
    
    importer.readGraphFile();
    
    EXPECT_FALSE(importer.getEdges().empty());
    
    EXPECT_EQ(importer.getStartNode(), 1);
    EXPECT_EQ(importer.getGoalNode(), 4);
    EXPECT_EQ(importer.getNumberOfNodes(), 4);
    
    auto edgeIter = importer.getEdges().begin();
    
    EXPECT_EQ(edgeIter->source, 1);
    EXPECT_EQ(edgeIter->destination, 2);
    EXPECT_DOUBLE_EQ(edgeIter->weight, 1.50);
    
    ++edgeIter;
    EXPECT_EQ(edgeIter->source, 1);
    EXPECT_EQ(edgeIter->destination, 3);
    EXPECT_DOUBLE_EQ(edgeIter->weight, 1.00);
    
    ++edgeIter;
    EXPECT_EQ(edgeIter->source, 1);
    EXPECT_EQ(edgeIter->destination, 4);
    EXPECT_DOUBLE_EQ(edgeIter->weight, 4.00);
    
    ++edgeIter;
    EXPECT_EQ(edgeIter->source, 2);
    EXPECT_EQ(edgeIter->destination, 3);
    EXPECT_DOUBLE_EQ(edgeIter->weight, 1.00);
    
    ++edgeIter;
    EXPECT_EQ(edgeIter->source, 3);
    EXPECT_EQ(edgeIter->destination, 4);
    EXPECT_DOUBLE_EQ(edgeIter->weight, 1.25);
    
    ++edgeIter;
    EXPECT_TRUE(edgeIter == importer.getEdges().end());
}
