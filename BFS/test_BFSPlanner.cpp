//
// Created by carpenter on 2/1/19.
//

#include <gtest/gtest.h>
#include "BFSPlanner.h"

TEST(BFSPlanner_class, import_graph)
{
    BFSPlanner planner;
    
    planner.importFileToAdjList("/home/carpenter/software/cpp/graphs/search/BFS/input1.txt");
    
    EXPECT_FALSE(planner.hasGoalBeenReached());
}

TEST(BFSPlanner_class, import_weighted_graph)
{
    BFSPlanner planner;
    
    planner.importFileToAdjList("/home/carpenter/software/cpp/graphs/search/BFS/input2.txt");
    
    EXPECT_FALSE(planner.hasGoalBeenReached());
}
