//
// Created by carpenter on 2/1/19.
//

#include <gtest/gtest.h>
#include "BFSPlanner.h"

TEST(BFSPlanner_class, import_graph)
{
    BFSPlanner planner;
    EXPECT_FALSE(planner.hasGoalBeenReached());
    EXPECT_EQ(planner.getSizeOfAdjList(), 0);
    
    planner.importGraphToAdjList("/home/carpenter/software/cpp/graphs/search/BFS/input1.txt");
    EXPECT_EQ(planner.getSizeOfAdjList(), planner.getInputTotalNumberOfNodes());
}

TEST(BFSPlanner_class, import_weighted_graph)
{
    BFSPlanner planner;
    EXPECT_FALSE(planner.hasGoalBeenReached());
    EXPECT_EQ(planner.getSizeOfAdjList(), 0);
    
    string inputFile = "/home/carpenter/software/cpp/graphs/search/BFS/input2.txt";
    
    BFSPlanner testHeaderImport;
    testHeaderImport.processGraphSetupHeaderOnly(inputFile);
    int testNumNodes = testHeaderImport.getInputTotalNumberOfNodes();
    
    planner.importGraphToAdjList(inputFile);
    EXPECT_EQ(planner.getSizeOfAdjList(), testNumNodes);
}





