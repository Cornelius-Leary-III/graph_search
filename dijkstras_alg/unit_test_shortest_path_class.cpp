//
// Created by cornelius on 4/23/19.
//

#include <gtest/gtest.h>
#include "ShortestPath.h"

TEST(ctor, defaultCtor)
{
   ShortestPath planner;

   EXPECT_EQ(planner.getEdgeImporter().getNumberOfNodes(), 0);
   EXPECT_EQ(planner.getEdgeImporter().getStartNode(), 0);
   EXPECT_EQ(planner.getEdgeImporter().getGoalNode(), 0);

   EXPECT_FALSE(planner.getEdgeImporter().isFileValid());

   EXPECT_TRUE(planner.getDijkstrasAlg().getAdjacencyList().empty());
   EXPECT_TRUE(planner.getDijkstrasAlg().getEdgeSet().empty());
}

TEST(importInvalidEdgesFile, noFileGiven)
{
   ShortestPath planner;

   EXPECT_THROW(planner.importEdges(""), InvalidGraphFileException);
}

TEST(importInvalidEdgesFile, fileDoesNotExist)
{
   ShortestPath planner;

   EXPECT_THROW(planner.importEdges("file_does_not_exist.txt"), InvalidGraphFileException);
}

TEST(importInvalidEdgesFile, emptyFile)
{
   ShortestPath planner;

   EXPECT_NO_THROW(planner.importEdges("tests/empty_file.txt"));
}

TEST(failToComputePath, edgesNotImportedBeforehand)
{
   ShortestPath planner;

   EXPECT_THROW(planner.computePathFromStartToGoal(),
                MustImportEdgesBeforeCallingThisMethodException);
}

TEST(failToComputePath, zeroNodesImported)
{
   ShortestPath planner;

   planner.importEdges("tests/zero_nodes.txt");

   EXPECT_THROW(planner.computePathFromStartToGoal(), ZeroNodesImportedException);
}

TEST(failToGetDistanceToGoal, edgesNotImportedBeforehand)
{
   ShortestPath planner;

   EXPECT_THROW(planner.getDistanceFromStartToGoal(),
                MustImportEdgesBeforeCallingThisMethodException);
}

TEST(failToGetDistanceToGoal, pathsNotComputedBeforehand)
{
   ShortestPath planner;

   planner.importEdges("tests/single_edge.txt");

   EXPECT_THROW(planner.getDistanceFromStartToGoal(),
                MustComputePathsBeforeCallingThisMethodException);
}

TEST(getDistanceToGoal, singleDirectedEdgeGraph)
{
   ShortestPath planner;

   planner.importEdges("tests/single_edge.txt");
   planner.computePathFromStartToGoal();

   EXPECT_EQ(planner.getEdgeImporter().getStartNode(), 0);
   EXPECT_EQ(planner.getEdgeImporter().getGoalNode(), 1);
   EXPECT_EQ(planner.getEdgeImporter().getNumberOfNodes(), 2);

   EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 1.50);
}

TEST(getDistanceToGoal, singleUndirectedEdgeGraph)
{
   ShortestPath planner;

   planner.importEdges("tests/single_edge.txt", false);
   planner.computePathFromStartToGoal();

   EXPECT_EQ(planner.getEdgeImporter().getStartNode(), 0);
   EXPECT_EQ(planner.getEdgeImporter().getGoalNode(), 1);
   EXPECT_EQ(planner.getEdgeImporter().getNumberOfNodes(), 2);

   EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 1.50);
}

TEST(getDistanceToGoal, multipleDirectedEdgesGraph)
{
   ShortestPath planner;

   planner.importEdges("tests/multiple_edges.txt");
   planner.computePathFromStartToGoal();

   EXPECT_EQ(planner.getEdgeImporter().getStartNode(), 0);
   EXPECT_EQ(planner.getEdgeImporter().getGoalNode(), 3);
   EXPECT_EQ(planner.getEdgeImporter().getNumberOfNodes(), 4);

   EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 2.25);
}

TEST(getDistanceToGoal, multipleUndirectedEdgesGraph)
{
   ShortestPath planner;

   planner.importEdges("tests/multiple_edges.txt", false);
   planner.computePathFromStartToGoal();

   EXPECT_EQ(planner.getEdgeImporter().getStartNode(), 0);
   EXPECT_EQ(planner.getEdgeImporter().getGoalNode(), 3);
   EXPECT_EQ(planner.getEdgeImporter().getNumberOfNodes(), 4);

   EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 2.25);
}

TEST(failToGetDistanceToGoal, didNotComputeBeforeGettingPath)
{
   ShortestPath planner;

   planner.importEdges("tests/single_edge.txt");

   EXPECT_THROW(planner.getPathFromStartToGoal(), StartNodeProvidedIsNonExistentException);
}

TEST(getPathToGoal, singleDirectedEdgeGraph)
{
   ShortestPath planner;

   planner.importEdges("tests/single_edge.txt");
   planner.computePathFromStartToGoal();

   auto path = planner.getPathFromStartToGoal();

   auto path_iter = path.begin();
   EXPECT_EQ(*path_iter, 0);
   EXPECT_EQ(*(++path_iter), 1);
   EXPECT_TRUE((++path_iter) == path.end());
}

TEST(getPathToGoal, singleUndirectedEdgeGraph)
{
   ShortestPath planner;

   planner.importEdges("tests/single_edge.txt", false);
   planner.computePathFromStartToGoal();

   auto path = planner.getPathFromStartToGoal();

   auto path_iter = path.begin();
   EXPECT_EQ(*path_iter, 0);
   EXPECT_EQ(*(++path_iter), 1);
   EXPECT_TRUE((++path_iter) == path.end());
}

TEST(getPathToGoal, multipleDirectedEdgesGraph)
{
   ShortestPath planner;

   planner.importEdges("tests/multiple_edges.txt");
   planner.computePathFromStartToGoal();

   auto path = planner.getPathFromStartToGoal();

   auto path_iter = path.begin();
   EXPECT_EQ(*path_iter, 0);
   EXPECT_EQ(*(++path_iter), 2);
   EXPECT_EQ(*(++path_iter), 3);
   EXPECT_TRUE((++path_iter) == path.end());
}

TEST(getPathToGoal, multipleUndirectedEdgesGraph)
{
   ShortestPath planner;

   planner.importEdges("tests/multiple_edges.txt", false);
   planner.computePathFromStartToGoal();

   auto path = planner.getPathFromStartToGoal();

   auto path_iter = path.begin();
   EXPECT_EQ(*path_iter, 0);
   EXPECT_EQ(*(++path_iter), 2);
   EXPECT_EQ(*(++path_iter), 3);
   EXPECT_TRUE((++path_iter) == path.end());
}

TEST(fullExample, smallWeightedDirectedGraph)
{
   ShortestPath planner;

   planner.importEdges("tests/small_weighted_graph.txt");
   planner.computePathFromStartToGoal();

   auto path      = planner.getPathFromStartToGoal();
   auto path_iter = path.begin();
   auto path_end  = path.end();

   EXPECT_EQ(*path_iter, 0);
   EXPECT_EQ(*(++path_iter), 2);
   EXPECT_EQ(*(++path_iter), 5);
   EXPECT_TRUE((++path_iter) == path_end);

   EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 23.0);
}

TEST(fullExample, smallWeightedUndirectedGraph)
{
   ShortestPath planner;

   planner.importEdges("tests/small_weighted_graph.txt", false);
   planner.computePathFromStartToGoal();

   auto path      = planner.getPathFromStartToGoal();
   auto path_iter = path.begin();
   auto path_end  = path.end();

   EXPECT_EQ(*path_iter, 0);
   EXPECT_EQ(*(++path_iter), 3);
   EXPECT_EQ(*(++path_iter), 2);
   EXPECT_EQ(*(++path_iter), 5);
   EXPECT_TRUE((++path_iter) == path_end);

   EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 20.0);
}

TEST(fullExample, mediumUnweightedDirectedGraph)
{
   ShortestPath planner;

   planner.importEdges("tests/medium_unweighted_directed_graph.txt");
   planner.computePathFromStartToGoal();

   auto path      = planner.getPathFromStartToGoal();
   auto path_iter = path.begin();
   auto path_end  = path.end();

   EXPECT_EQ(*path_iter, 42);
   EXPECT_EQ(*(++path_iter), 51);
   EXPECT_EQ(*(++path_iter), 59);
   EXPECT_EQ(*(++path_iter), 68);
   EXPECT_EQ(*(++path_iter), 77);
   EXPECT_EQ(*(++path_iter), 88);
   EXPECT_EQ(*(++path_iter), 99);
   EXPECT_EQ(*(++path_iter), 100);
   EXPECT_EQ(*(++path_iter), 101);
   EXPECT_EQ(*(++path_iter), 102);
   EXPECT_EQ(*(++path_iter), 103);
   EXPECT_EQ(*(++path_iter), 104);
   EXPECT_EQ(*(++path_iter), 105);
   EXPECT_EQ(*(++path_iter), 106);
   EXPECT_EQ(*(++path_iter), 107);
   EXPECT_EQ(*(++path_iter), 108);
   EXPECT_EQ(*(++path_iter), 109);

   EXPECT_TRUE((++path_iter) == path_end);

   EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 16.0);
}

TEST(fullExample, mediumWeightedDirectedGraph)
{
   ShortestPath planner;

   planner.importEdges("tests/medium_weighted_directed_graph.txt");
   planner.computePathFromStartToGoal();

   auto path      = planner.getPathFromStartToGoal();
   auto path_iter = path.begin();
   auto path_end  = path.end();

   EXPECT_EQ(*path_iter, 11);
   EXPECT_EQ(*(++path_iter), 22);
   EXPECT_EQ(*(++path_iter), 33);
   EXPECT_EQ(*(++path_iter), 44);
   EXPECT_EQ(*(++path_iter), 55);
   EXPECT_EQ(*(++path_iter), 66);
   EXPECT_EQ(*(++path_iter), 67);
   EXPECT_EQ(*(++path_iter), 68);
   EXPECT_EQ(*(++path_iter), 69);
   EXPECT_EQ(*(++path_iter), 70);
   EXPECT_EQ(*(++path_iter), 71);
   EXPECT_EQ(*(++path_iter), 72);
   EXPECT_EQ(*(++path_iter), 83);
   EXPECT_EQ(*(++path_iter), 84);
   EXPECT_EQ(*(++path_iter), 85);
   EXPECT_EQ(*(++path_iter), 96);
   EXPECT_EQ(*(++path_iter), 97);
   EXPECT_EQ(*(++path_iter), 108);
   EXPECT_EQ(*(++path_iter), 109);
   EXPECT_EQ(*(++path_iter), 120);

   EXPECT_TRUE((++path_iter) == path_end);

   EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 82.518007);
}
