//
// Created by carpenter on 1/31/19.
//

#include <gtest/gtest.h>
#include "BreadthFirstSearchPlanner.h"

TEST(BFS_Planner_Class, constructor_no_params)
{
    BreadthFirstSearchPlanner testBFSPlanner;
    
    EXPECT_FALSE(testBFSPlanner.hasGoalBeenReached());
    
    string inputName("input_node");
    double inputValue = 2.0;
    double inputXCoord = 1.0;
    double inputYCoord = 2.5;
    
    GraphNode testGraphNode(inputName, inputValue, inputXCoord, inputYCoord);
    testBFSPlanner.setStartNode(testGraphNode);
    
    EXPECT_EQ(testBFSPlanner.getStartNodeName(), inputName);
    EXPECT_TRUE(testBFSPlanner.getStartNode() == testGraphNode);
}

