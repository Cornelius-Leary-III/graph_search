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

TEST(get_distance_to_goal, single_directed_edge_graph)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/single_edge.txt");
    planner.computePathFromStartToGoal();
    
    EXPECT_EQ(planner.getEdgeImporter().getStartNode(), 0);
    EXPECT_EQ(planner.getEdgeImporter().getGoalNode(), 1);
    EXPECT_EQ(planner.getEdgeImporter().getNumberOfNodes(), 2);
    
    EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 1.50);
}

TEST(get_distance_to_goal, single_undirected_edge_graph)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/single_edge.txt", false);
    planner.computePathFromStartToGoal();
    
    EXPECT_EQ(planner.getEdgeImporter().getStartNode(), 0);
    EXPECT_EQ(planner.getEdgeImporter().getGoalNode(), 1);
    EXPECT_EQ(planner.getEdgeImporter().getNumberOfNodes(), 2);
    
    EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 1.50);
}

TEST(get_distance_to_goal, multiple_directed_edges_graph)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/multiple_edges.txt");
    planner.computePathFromStartToGoal();
    
    EXPECT_EQ(planner.getEdgeImporter().getStartNode(), 0);
    EXPECT_EQ(planner.getEdgeImporter().getGoalNode(), 3);
    EXPECT_EQ(planner.getEdgeImporter().getNumberOfNodes(), 4);
    
    EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 2.25);
}

TEST(get_distance_to_goal, multiple_undirected_edges_graph)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/multiple_edges.txt", false);
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

TEST(get_path_to_goal, single_directed_edge_graph)
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

TEST(get_path_to_goal, single_undirected_edge_graph)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/single_edge.txt", false);
    planner.computePathFromStartToGoal();
    
    auto path = planner.getPathFromStartToGoal();
    
    auto pathIter = path.begin();
    EXPECT_EQ(*pathIter, 0);
    EXPECT_EQ(*(++pathIter), 1);
    EXPECT_TRUE((++pathIter) == path.end());
}

TEST(get_path_to_goal, multiple_directed_edges_graph)
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

TEST(get_path_to_goal, multiple_undirected_edges_graph)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/multiple_edges.txt", false);
    planner.computePathFromStartToGoal();
    
    auto path = planner.getPathFromStartToGoal();
    
    auto pathIter = path.begin();
    EXPECT_EQ(*pathIter, 0);
    EXPECT_EQ(*(++pathIter), 2);
    EXPECT_EQ(*(++pathIter), 3);
    EXPECT_TRUE((++pathIter) == path.end());
}

TEST(full_example, small_weighted_directed_graph)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/small_weighted_graph.txt");
    planner.computePathFromStartToGoal();
    
    auto path = planner.getPathFromStartToGoal();
    auto pathIter = path.begin();
    auto pathEnd = path.end();
    
    EXPECT_EQ(*pathIter, 0);
    EXPECT_EQ(*(++pathIter), 2);
    EXPECT_EQ(*(++pathIter), 5);
    EXPECT_TRUE((++pathIter) == pathEnd);
    
    EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 23.0);
}

TEST(full_example, small_weighted_undirected_graph)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/small_weighted_graph.txt", false);
    planner.computePathFromStartToGoal();
    
    auto path = planner.getPathFromStartToGoal();
    auto pathIter = path.begin();
    auto pathEnd = path.end();
    
    EXPECT_EQ(*pathIter, 0);
    EXPECT_EQ(*(++pathIter), 3);
    EXPECT_EQ(*(++pathIter), 2);
    EXPECT_EQ(*(++pathIter), 5);
    EXPECT_TRUE((++pathIter) == pathEnd);
    
    EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 20.0);
}

TEST(full_example, medium_unweighted_directed_graph)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/medium_unweighted_directed_graph.txt");
    planner.computePathFromStartToGoal();
    
    auto path = planner.getPathFromStartToGoal();
    auto pathIter = path.begin();
    auto pathEnd = path.end();
    
    EXPECT_EQ(*pathIter, 42);
    EXPECT_EQ(*(++pathIter), 51);
    EXPECT_EQ(*(++pathIter), 59);
    EXPECT_EQ(*(++pathIter), 68);
    EXPECT_EQ(*(++pathIter), 77);
    EXPECT_EQ(*(++pathIter), 88);
    EXPECT_EQ(*(++pathIter), 99);
    EXPECT_EQ(*(++pathIter), 100);
    EXPECT_EQ(*(++pathIter), 101);
    EXPECT_EQ(*(++pathIter), 102);
    EXPECT_EQ(*(++pathIter), 103);
    EXPECT_EQ(*(++pathIter), 104);
    EXPECT_EQ(*(++pathIter), 105);
    EXPECT_EQ(*(++pathIter), 106);
    EXPECT_EQ(*(++pathIter), 107);
    EXPECT_EQ(*(++pathIter), 108);
    EXPECT_EQ(*(++pathIter), 109);
    
    EXPECT_TRUE((++pathIter) == pathEnd);
    
    EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 16.0);
}

TEST(full_example, medium_weighted_directed_graph)
{
    ShortestPath planner;
    
    planner.importEdges("/home/cornelius/cpp_repo/graph_search/dijkstras_alg/tests/medium_weighted_directed_graph.txt");
    planner.computePathFromStartToGoal();
    
    auto path = planner.getPathFromStartToGoal();
    auto pathIter = path.begin();
    auto pathEnd = path.end();
    
    EXPECT_EQ(*pathIter, 11);
    EXPECT_EQ(*(++pathIter), 22);
    EXPECT_EQ(*(++pathIter), 33);
    EXPECT_EQ(*(++pathIter), 44);
    EXPECT_EQ(*(++pathIter), 55);
    EXPECT_EQ(*(++pathIter), 66);
    EXPECT_EQ(*(++pathIter), 67);
    EXPECT_EQ(*(++pathIter), 68);
    EXPECT_EQ(*(++pathIter), 69);
    EXPECT_EQ(*(++pathIter), 70);
    EXPECT_EQ(*(++pathIter), 71);
    EXPECT_EQ(*(++pathIter), 72);
    EXPECT_EQ(*(++pathIter), 83);
    EXPECT_EQ(*(++pathIter), 84);
    EXPECT_EQ(*(++pathIter), 85);
    EXPECT_EQ(*(++pathIter), 96);
    EXPECT_EQ(*(++pathIter), 97);
    EXPECT_EQ(*(++pathIter), 108);
    EXPECT_EQ(*(++pathIter), 109);
    EXPECT_EQ(*(++pathIter), 120);
    
    EXPECT_TRUE((++pathIter) == pathEnd);
    
    EXPECT_DOUBLE_EQ(planner.getDistanceFromStartToGoal(), 82.518007);
}

