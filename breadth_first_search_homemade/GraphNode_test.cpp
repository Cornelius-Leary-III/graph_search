//
// Created by carpenter on 1/28/19.
//

#include <gtest/gtest.h>
#include "GraphNode.h"

TEST(GraphNode_class, constructor_no_params)
{
    GraphNode testGraphNode;
    
    string testName = testGraphNode.getNodeName();
    EXPECT_EQ(testName, "?");
    
    double testValue = testGraphNode.getNodeValue();
    EXPECT_EQ(testValue, -1);
}

TEST(GraphNode_class, constructor_name_only)
{
    string inputName = "test";
    
    GraphNode testGraphNode(inputName);
    
    string testName = testGraphNode.getNodeName();
    EXPECT_EQ(testName, inputName);
    
    double testValue = testGraphNode.getNodeValue();
    EXPECT_EQ(testValue, -1);
}

TEST(GraphNode_class, constructor_name_value)
{
    string inputName = "test";
    double inputValue = 60.05;
    
    GraphNode testGraphNode(inputName, inputValue);
    
    string testName = testGraphNode.getNodeName();
    EXPECT_EQ(testName, inputName);
    
    double testValue = testGraphNode.getNodeValue();
    EXPECT_EQ(testValue, inputValue);
}

TEST(GridNode_class, constructor_no_params)
{
    GridNode testGridNode;
    
    string testName = testGridNode.getNodeName();
    EXPECT_EQ(testName, "?");
    
    double testValue = testGridNode.getNodeValue();
    EXPECT_EQ(testValue, -1);
    
    double testX = testGridNode.getXCoord();
    EXPECT_EQ(testX, 0.0);
    
    double testY = testGridNode.getYCoord();
    EXPECT_EQ(testY, 0.0);
}

TEST(GridNode_class, constructor_name_only)
{
    string inputName = "test";
    
    GridNode testGridNode(inputName);
    
    string testName = testGridNode.getNodeName();
    EXPECT_EQ(testName, inputName);
    
    double testValue = testGridNode.getNodeValue();
    EXPECT_EQ(testValue, -1);
    
    double testX = testGridNode.getXCoord();
    EXPECT_EQ(testX, 0.0);
    
    double testY = testGridNode.getYCoord();
    EXPECT_EQ(testY, 0.0);
}

TEST(GridNode_class, constructor_name_x_y)
{
    string inputName = "test";
    double inputX = 15.0;
    double inputY = -4.55;
    
    GridNode testGridNode(inputName, inputX, inputY);
    
    string testName = testGridNode.getNodeName();
    EXPECT_EQ(testName, inputName);
    
    double testValue = testGridNode.getNodeValue();
    EXPECT_EQ(testValue, -1);
    
    double testX = testGridNode.getXCoord();
    EXPECT_EQ(testX, inputX);
    
    double testY = testGridNode.getYCoord();
    EXPECT_EQ(testY, inputY);
}

TEST(GridNode_class, constructor_name_value_x_y)
{
    string inputName = "test";
    double inputValue = 1000.0078;
    double inputX = 15.0;
    double inputY = -4.55;
    
    GridNode testGridNode(inputName, inputValue, inputX, inputY);
    
    string testName = testGridNode.getNodeName();
    EXPECT_EQ(testName, inputName);
    
    double testValue = testGridNode.getNodeValue();
    EXPECT_EQ(testValue, inputValue);
    
    double testX = testGridNode.getXCoord();
    EXPECT_EQ(testX, inputX);
    
    double testY = testGridNode.getYCoord();
    EXPECT_EQ(testY, inputY);
}
