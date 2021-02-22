//
// Created by cornelius on 4/23/19.
//

#include <gtest/gtest.h>
#include "EdgeImporter.h"

TEST(EdgeImporterParamsCtor, noFileGiven)
{
   EdgeImporter importer("");

   EXPECT_FALSE(importer.isFileValid());
}

TEST(EdgeImporterParamsCtor, fileDoesNotExist)
{
   EdgeImporter importer("file_does_not_exist.txt");

   EXPECT_FALSE(importer.isFileValid());
}

TEST(EdgeImporterParamsCtor, emptyFile)
{
   EdgeImporter importer("tests/empty_file.txt");

   EXPECT_TRUE(importer.isFileValid());
}

TEST(EdgeImporterParamsCtor, validFile)
{
   EdgeImporter importer("tests/non_empty_file.txt");

   EXPECT_TRUE(importer.isFileValid());
}

TEST(setupEdgeBuilder, defaultSettings)
{
   EdgeImporter importer("");

   importer.setupEdgeBuilder();

   auto outputESB = importer.getEdgeBuilder();

   EXPECT_TRUE(outputESB.isGraphDirected());
   EXPECT_TRUE(outputESB.areNegativeEdgesAllowed());
   EXPECT_TRUE(outputESB.areSelfLoopsAllowed());
}

TEST(setupEdgeBuilder, customSettings)
{
   EdgeImporter importer("");

   importer.setupEdgeBuilder(true, false, false);

   auto outputESB = importer.getEdgeBuilder();

   EXPECT_TRUE(outputESB.isGraphDirected());
   EXPECT_FALSE(outputESB.areNegativeEdgesAllowed());
   EXPECT_FALSE(outputESB.areSelfLoopsAllowed());
}

TEST(readInvalidGraphFile, no_file_given)
{
   EdgeImporter importer("");

   importer.readGraphFile();

   EXPECT_TRUE(importer.getEdges().empty());

   EXPECT_EQ(importer.getStartNodeName(), "0");
   EXPECT_EQ(importer.getGoalNodeName(), "0");
   EXPECT_EQ(importer.getNumberOfNodes(), 0);
}

TEST(readInvalidGraphFile, file_does_not_exist)
{
   EdgeImporter importer("invalid_file.txt");

   importer.readGraphFile();

   EXPECT_TRUE(importer.getEdges().empty());

   EXPECT_EQ(importer.getStartNodeName(), "0");
   EXPECT_EQ(importer.getGoalNodeName(), "0");
   EXPECT_EQ(importer.getNumberOfNodes(), 0);
}

TEST(readInvalidGraphFile, empty_file)
{
   EdgeImporter importer("tests/empty_file.txt");

   importer.readGraphFile();

   EXPECT_TRUE(importer.getEdges().empty());

   EXPECT_EQ(importer.getStartNodeName(), "0");
   EXPECT_EQ(importer.getGoalNodeName(), "0");
   EXPECT_EQ(importer.getNumberOfNodes(), 0);
}

TEST(readInvalidGraphFile, setup_info_is_incorrect)
{
   EdgeImporter importer(
      "/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/setup_syntax_wrong.txt");

   importer.readGraphFile();

   EXPECT_TRUE(importer.getEdges().empty());

   EXPECT_EQ(importer.getStartNodeName(), "0");
   EXPECT_EQ(importer.getGoalNodeName(), "0");
   EXPECT_EQ(importer.getNumberOfNodes(), 0);
}

TEST(readInvalidGraphFile, setup_info_correct_missing_edges)
{
   EdgeImporter importer("tests/missing_edges.txt");

   importer.readGraphFile();

   EXPECT_TRUE(importer.getEdges().empty());

   EXPECT_EQ(importer.getStartNodeName(), "1");
   EXPECT_EQ(importer.getGoalNodeName(), "20");
   EXPECT_EQ(importer.getNumberOfNodes(), 25);
}

TEST(readValidGraphFile, single_edge)
{
   EdgeImporter importer("tests/single_edge.txt");

   importer.readGraphFile();

   EXPECT_FALSE(importer.getEdges().empty());

   auto edge = importer.getEdges().front();

   EXPECT_EQ(edge.mSource.mName, "1");
   EXPECT_EQ(edge.mDestination.mName, "2");
   EXPECT_DOUBLE_EQ(edge.mWeight, 1.50);

   EXPECT_EQ(importer.getStartNodeName(), "1");
   EXPECT_EQ(importer.getGoalNodeName(), "2");
   EXPECT_EQ(importer.getNumberOfNodes(), 2);
}

TEST(readValidGraphFile, multiple_edges)
{
   EdgeImporter importer("tests/multiple_edges.txt");

   importer.readGraphFile();

   EXPECT_FALSE(importer.getEdges().empty());

   EXPECT_EQ(importer.getStartNodeName(), "1");
   EXPECT_EQ(importer.getGoalNodeName(), "4");
   EXPECT_EQ(importer.getNumberOfNodes(), 4);

   auto edge_iter = importer.getEdges().begin();

   EXPECT_EQ(edge_iter->mSource.mName, "1");
   EXPECT_EQ(edge_iter->mDestination.mName, "2");
   EXPECT_DOUBLE_EQ(edge_iter->mWeight, 1.50);

   ++edge_iter;
   EXPECT_EQ(edge_iter->mSource.mName, "1");
   EXPECT_EQ(edge_iter->mDestination.mName, "3");
   EXPECT_DOUBLE_EQ(edge_iter->mWeight, 1.00);

   ++edge_iter;
   EXPECT_EQ(edge_iter->mSource.mName, "1");
   EXPECT_EQ(edge_iter->mDestination.mName, "4");
   EXPECT_DOUBLE_EQ(edge_iter->mWeight, 4.00);

   ++edge_iter;
   EXPECT_EQ(edge_iter->mSource.mName, "2");
   EXPECT_EQ(edge_iter->mDestination.mName, "3");
   EXPECT_DOUBLE_EQ(edge_iter->mWeight, 1.00);

   ++edge_iter;
   EXPECT_EQ(edge_iter->mSource.mName, "3");
   EXPECT_EQ(edge_iter->mDestination.mName, "4");
   EXPECT_DOUBLE_EQ(edge_iter->mWeight, 1.25);

   ++edge_iter;
   EXPECT_TRUE(edge_iter == importer.getEdges().end());
}
