//
// Created by cornelius on 4/23/19.
//

#include <gtest/gtest.h>
#include "ShortestPath.h"

TEST(ShortestPath_ctor, default_ctor)
{
    ShortestPath planner;
    
    EXPECT_EQ(planner.getEdgeImporter().getNumberOfNodes(), 0);
    EXPECT_EQ(planner.getEdgeImporter().getStartNode(), 0);
    EXPECT_EQ(planner.getEdgeImporter().getGoalNode(), 0);
    
    EXPECT_FALSE(planner.getEdgeImporter().isFileValid());
    
    EXPECT_TRUE(planner.getDijkstrasAlg().getAdjacencyList().empty());
    EXPECT_TRUE(planner.getDijkstrasAlg().getEdgeSet().empty());
}

TEST(import_invalid_edges_file, no_file_given)
{
    ShortestPath planner;
    
    EXPECT_THROW(planner.importEdges(""), InvalidGraphFileException);
}

TEST(import_invalid_edges_file, file_does_not_exist)
{
    ShortestPath planner;
    
    EXPECT_THROW(planner.importEdges("file_does_not_exist.txt"), InvalidGraphFileException);
}

TEST(import_invalid_edges_file, empty_file)
{
    ShortestPath planner;
    
    EXPECT_NO_THROW(planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/empty_file.txt"));
}

TEST(fail_to_compute_path, edges_not_imported_beforehand)
{
    ShortestPath planner;
    
    EXPECT_THROW(planner.computePathFromStartToGoal(), MustImportEdgesBeforeCallingThisMethodException);
}

TEST(fail_to_compute_path, zero_nodes_imported)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/zero_nodes.txt");
    
    EXPECT_THROW(planner.computePathFromStartToGoal(), ZeroNodesImportedException);
}

TEST(fail_to_get_distance_to_goal, edges_not_imported_beforehand)
{
    ShortestPath planner;
    
    EXPECT_THROW(planner.getDistanceFromStartToGoal(), MustImportEdgesBeforeCallingThisMethodException);
}

TEST(fail_to_get_distance_to_goal, paths_not_computed_beforehand)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/single_edge.txt");
    
    EXPECT_THROW(planner.getDistanceFromStartToGoal(), MustComputePathsBeforeCallingThisMethodException);
}

TEST(get_distance_to_goal, single_edge_graph)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/single_edge.txt");
    planner.computePathFromStartToGoal();
    
    EXPECT_EQ(planner.getEdgeImporter().getStartNode(), 0);
    EXPECT_EQ(planner.getEdgeImporter().getGoalNode(), 1);
    EXPECT_EQ(planner.getEdgeImporter().getNumberOfNodes(), 2);
    
    EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 1.50);
}

TEST(get_distance_to_goal, multiple_edges_graph)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/multiple_edges.txt");
    planner.computePathFromStartToGoal();
    
    EXPECT_EQ(planner.getEdgeImporter().getStartNode(), 0);
    EXPECT_EQ(planner.getEdgeImporter().getGoalNode(), 3);
    EXPECT_EQ(planner.getEdgeImporter().getNumberOfNodes(), 4);
    
    EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 2.25);
}

TEST(fail_to_get_path_to_goal, did_not_compute_before_getting_path)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/single_edge.txt");
    
    EXPECT_THROW(planner.getPathFromStartToGoal(), StartNodeProvidedIsNonExistentException);
}

TEST(get_path_to_goal, single_edge_graph)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/single_edge.txt");
    planner.computePathFromStartToGoal();
    
    auto path = planner.getPathFromStartToGoal();
    
    auto pathIter = path.begin();
    EXPECT_EQ(*pathIter, 0);
    EXPECT_EQ(*(++pathIter), 1);
    EXPECT_TRUE((++pathIter) == path.end());
}

TEST(get_path_to_goal, multiple_edges_graph)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/multiple_edges.txt");
    planner.computePathFromStartToGoal();
    
    auto path = planner.getPathFromStartToGoal();
    
    auto pathIter = path.begin();
    EXPECT_EQ(*pathIter, 0);
    EXPECT_EQ(*(++pathIter), 2);
    EXPECT_EQ(*(++pathIter), 3);
    EXPECT_TRUE((++pathIter) == path.end());
}

