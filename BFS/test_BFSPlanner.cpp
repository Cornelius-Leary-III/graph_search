//
// Created by carpenter on 2/1/19.
//

#include <gtest/gtest.h>
#include "BFS_Planner.h"

TEST(BFS_Planner_ctor, successful_planner_creation)
{
    BFS_Planner planner;
    
    EXPECT_TRUE(planner.getStartNode().empty());
    EXPECT_TRUE(planner.getGoalNode().empty());
    
    EXPECT_EQ(planner.getInputTotalNumberOfNodes(), 0);
    EXPECT_EQ(planner.getSizeOfAdjList(), 0);
    
    EXPECT_FALSE(planner.hasGoalBeenReached());
}

TEST(BFS_Planner_set_start_node, empty_name)
{
    BFS_Planner planner;
    
    planner.setStartNode("");
    
    EXPECT_TRUE(planner.getStartNode().empty());
}

TEST(BFS_Planner_set_start_node, actual_name)
{
    BFS_Planner planner;
    
    planner.setStartNode("10");
    
    EXPECT_EQ(planner.getStartNode(), "10");
}

TEST(BFS_Planner_set_goal_node, empty_name)
{
    BFS_Planner planner;
    
    planner.setGoalNode("");
    
    EXPECT_TRUE(planner.getGoalNode().empty());
}

TEST(BFS_Planner_set_goal_node, actual_name)
{
    BFS_Planner planner;
    
    planner.setGoalNode("100");
    
    EXPECT_EQ(planner.getGoalNode(), "100");
}

TEST(BFS_Planner_process_setup_header, no_file_given)
{
    BFS_Planner planner;
    
    planner.processGraphSetupHeaderOnly("");
    
    EXPECT_EQ(planner.getInputTotalNumberOfNodes(), 0);
    EXPECT_TRUE(planner.getStartNode().empty());
    EXPECT_TRUE(planner.getGoalNode().empty());
}

TEST(BFS_Planner_process_setup_header, empty_file)
{
    BFS_Planner planner;
    
    planner.processGraphSetupHeaderOnly("/home/cornelius/cpp_repo/graph_search/BFS/test_files/empty_test_file.txt");
    
    EXPECT_EQ(planner.getInputTotalNumberOfNodes(), 0);
    EXPECT_TRUE(planner.getStartNode().empty());
    EXPECT_TRUE(planner.getGoalNode().empty());
}

TEST(BFS_Planner_process_setup_header, missing_start_and_goal_nodes)
{
    BFS_Planner planner;
    
    planner.processGraphSetupHeaderOnly("/home/cornelius/cpp_repo/graph_search/BFS/test_files/missing_start_and_goal.txt");
    
    EXPECT_NE(planner.getInputTotalNumberOfNodes(), 0);
    EXPECT_TRUE(planner.getStartNode().empty());
    EXPECT_TRUE(planner.getGoalNode().empty());
}

TEST(BFS_Planner_process_setup_header, missing_goal_node)
{
    BFS_Planner planner;
    
    planner.processGraphSetupHeaderOnly("/home/cornelius/cpp_repo/graph_search/BFS/test_files/missing_goal.txt");
    
    EXPECT_NE(planner.getInputTotalNumberOfNodes(), 0);
    EXPECT_FALSE(planner.getStartNode().empty());
    EXPECT_TRUE(planner.getGoalNode().empty());
}

TEST(BFS_Planner_process_setup_header, all_setup_info_present)
{
    BFS_Planner planner;
    
    planner.processGraphSetupHeaderOnly("/home/cornelius/cpp_repo/graph_search/BFS/test_files/input1.txt");
    
    EXPECT_NE(planner.getInputTotalNumberOfNodes(), 0);
    EXPECT_FALSE(planner.getStartNode().empty());
    EXPECT_FALSE(planner.getGoalNode().empty());
}

TEST(BFS_Planner_import_graph_to_adj_list, no_file_given)
{
    BFS_Planner planner;
    
    planner.importGraphToAdjList("");
    
    EXPECT_EQ(planner.getInputTotalNumberOfNodes(), 0);
    EXPECT_TRUE(planner.getStartNode().empty());
    EXPECT_TRUE(planner.getGoalNode().empty());
    
    EXPECT_EQ(planner.getSizeOfAdjList(), 0);
}

TEST(BFS_Planner_import_graph_to_adj_list, empty_file)
{
    BFS_Planner planner;
    
    planner.importGraphToAdjList("/home/cornelius/cpp_repo/graph_search/BFS/test_files/empty_test_file.txt");
    
    EXPECT_EQ(planner.getInputTotalNumberOfNodes(), 0);
    EXPECT_TRUE(planner.getStartNode().empty());
    EXPECT_TRUE(planner.getGoalNode().empty());
    
    EXPECT_EQ(planner.getSizeOfAdjList(), 0);
}

TEST(BFS_Planner_import_graph_to_adj_list, missing_start_and_goal_nodes)
{
    BFS_Planner planner;
    
    planner.importGraphToAdjList("/home/cornelius/cpp_repo/graph_search/BFS/test_files/missing_start_and_goal.txt");
    
    EXPECT_NE(planner.getInputTotalNumberOfNodes(), 0);
    EXPECT_TRUE(planner.getStartNode().empty());
    EXPECT_TRUE(planner.getGoalNode().empty());
    
    EXPECT_EQ(planner.getSizeOfAdjList(), 2);
}

TEST(BFS_Planner_import_graph_to_adj_list, missing_goal_node)
{
    BFS_Planner planner;
    
    planner.importGraphToAdjList("/home/cornelius/cpp_repo/graph_search/BFS/test_files/missing_goal.txt");
    
    EXPECT_NE(planner.getInputTotalNumberOfNodes(), 0);
    EXPECT_FALSE(planner.getStartNode().empty());
    EXPECT_TRUE(planner.getGoalNode().empty());
    
    EXPECT_EQ(planner.getSizeOfAdjList(), 3);
}

TEST(BFS_Planner_import_graph_to_adj_list, only_header_no_edges)
{
    BFS_Planner planner;
    
    planner.importGraphToAdjList("/home/cornelius/cpp_repo/graph_search/BFS/test_files/setup_info_only.txt");
    
    EXPECT_NE(planner.getInputTotalNumberOfNodes(), 0);
    EXPECT_FALSE(planner.getStartNode().empty());
    EXPECT_FALSE(planner.getGoalNode().empty());
    
    EXPECT_EQ(planner.getSizeOfAdjList(), 0);
}






TEST(BFS_Planner_search_for_goal, no_graph_imported)
{
    BFS_Planner planner;
    
    planner.processGraphSetupHeaderOnly("/home/cornelius/cpp_repo/graph_search/BFS/test_files/input1.txt");
    
    EXPECT_FALSE(planner.searchForGoal());
}

TEST(BFS_Planner_search_for_goal, only_2_nodes_start_and_goal)
{
    BFS_Planner planner;
    
    planner.importGraphToAdjList("/home/cornelius/cpp_repo/graph_search/BFS/test_files/only_2_nodes_no_path_to_goal_in_graph.txt");
    
    EXPECT_EQ(planner.getSizeOfAdjList(), 2);
    EXPECT_FALSE(planner.searchForGoal());
}

TEST(BFS_Planner_search_for_goal, import_and_search_graph)
{
    BFS_Planner planner;
    string inputFile = "/home/cornelius/cpp_repo/graph_search/BFS/test_files/input1.txt";
    
    BFS_Planner testHeaderImport;
    testHeaderImport.processGraphSetupHeaderOnly(inputFile);
    int testNumNodes = testHeaderImport.getInputTotalNumberOfNodes();
    
    planner.importGraphToAdjList(inputFile);
    EXPECT_EQ(planner.getSizeOfAdjList(), testNumNodes);
    EXPECT_EQ(planner.getStartNode(), testHeaderImport.getStartNode());
    EXPECT_EQ(planner.getGoalNode(), testHeaderImport.getGoalNode());
    
    EXPECT_TRUE(planner.searchForGoal());
}

TEST(BFSPlanner_class, import_and_search_weighted_graph)
{
    BFS_Planner planner;
    EXPECT_FALSE(planner.hasGoalBeenReached());
    EXPECT_EQ(planner.getSizeOfAdjList(), 0);
    
    string inputFile = "/home/cornelius/cpp_repo/graph_search/BFS/test_files/input2.txt";
    
    BFS_Planner testHeaderImport;
    testHeaderImport.processGraphSetupHeaderOnly(inputFile);
    int testNumNodes = testHeaderImport.getInputTotalNumberOfNodes();
    
    planner.importGraphToAdjList(inputFile);
    EXPECT_EQ(planner.getSizeOfAdjList(), testNumNodes);
    EXPECT_EQ(planner.getStartNode(), testHeaderImport.getStartNode());
    EXPECT_EQ(planner.getGoalNode(), testHeaderImport.getGoalNode());
    
    EXPECT_TRUE(planner.searchForGoal());
}






