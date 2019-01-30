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
    
    double testXCoord = testGraphNode.getNodeXCoord();
    EXPECT_EQ(testXCoord, 0.0);
    
    double testYCoord = testGraphNode.getNodeYCoord();
    EXPECT_EQ(testYCoord, 0.0);
}

TEST(GraphNode_class, constructor_name_only)
{
    string inputName = "test";
    
    GraphNode testGraphNode(inputName);
    
    string testName = testGraphNode.getNodeName();
    EXPECT_EQ(testName, inputName);
    
    double testValue = testGraphNode.getNodeValue();
    EXPECT_EQ(testValue, -1);
    
    double testXCoord = testGraphNode.getNodeXCoord();
    EXPECT_EQ(testXCoord, 0.0);
    
    double testYCoord = testGraphNode.getNodeYCoord();
    EXPECT_EQ(testYCoord, 0.0);
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
    
    double testXCoord = testGraphNode.getNodeXCoord();
    EXPECT_EQ(testXCoord, 0.0);
    
    double testYCoord = testGraphNode.getNodeYCoord();
    EXPECT_EQ(testYCoord, 0.0);
}

TEST(GraphNode_class, constructor_name_x_y)
{
    string inputName = "test";
    double inputXCoord = 2.50;
    double inputYCoord = -1.75;
    
    GraphNode testGraphNode(inputName, inputXCoord, inputYCoord);
    
    string testName = testGraphNode.getNodeName();
    EXPECT_EQ(testName, inputName);
    
    double testValue = testGraphNode.getNodeValue();
    EXPECT_EQ(testValue, -1);
    
    double testXCoord = testGraphNode.getNodeXCoord();
    EXPECT_EQ(testXCoord, inputXCoord);
    
    double testYCoord = testGraphNode.getNodeYCoord();
    EXPECT_EQ(testYCoord, inputYCoord);
}

TEST(GraphNode_class, constructor_name_value_x_y)
{
    string inputName = "test";
    double inputValue = 55.32;
    double inputXCoord = 2.50;
    double inputYCoord = -1.75;
    
    GraphNode testGraphNode(inputName, inputValue,
                            inputXCoord, inputYCoord);
    
    string testName = testGraphNode.getNodeName();
    EXPECT_EQ(testName, inputName);
    
    double testValue = testGraphNode.getNodeValue();
    EXPECT_EQ(testValue, inputValue);
    
    double testXCoord = testGraphNode.getNodeXCoord();
    EXPECT_EQ(testXCoord, inputXCoord);
    
    double testYCoord = testGraphNode.getNodeYCoord();
    EXPECT_EQ(testYCoord, inputYCoord);
}

TEST(GraphNode_class, operator_comparison_equalequal_notequal)
{
    GraphNode testGraphNode;
    GraphNode testGraphNode2;
    
    EXPECT_TRUE(testGraphNode == testGraphNode2);
    EXPECT_FALSE(testGraphNode != testGraphNode2);
    
    string inputName3 = "?";
    double inputValue3 = -1;
    GraphNode testGraphNode3(inputName3, inputValue3);
    
    EXPECT_TRUE(testGraphNode == testGraphNode3);
    EXPECT_FALSE(testGraphNode != testGraphNode3);
    
    string inputName4 = "test4";
    double inputValue4 = 60.05;
    GraphNode testGraphNode4(inputName4, inputValue4);
    
    EXPECT_FALSE(testGraphNode == testGraphNode4);
    EXPECT_FALSE(testGraphNode2 == testGraphNode4);
    EXPECT_FALSE(testGraphNode3 == testGraphNode4);
    
    EXPECT_TRUE(testGraphNode != testGraphNode4);
    EXPECT_TRUE(testGraphNode2 != testGraphNode4);
    EXPECT_TRUE(testGraphNode3 != testGraphNode4);
    
    string inputName5 = "test";
    //    double inputValue5 = 60.05;
    double inputXCoord5 = 12.25;
    double inputYCoord5 = -4.00;
    GraphNode testGraphNode5(inputName5, inputXCoord5, inputYCoord5);
    
    EXPECT_FALSE(testGraphNode == testGraphNode5);
    EXPECT_FALSE(testGraphNode2 == testGraphNode5);
    EXPECT_FALSE(testGraphNode3 == testGraphNode5);
    EXPECT_FALSE(testGraphNode4 == testGraphNode5);
    
    EXPECT_TRUE(testGraphNode != testGraphNode5);
    EXPECT_TRUE(testGraphNode2 != testGraphNode5);
    EXPECT_TRUE(testGraphNode3 != testGraphNode5);
    EXPECT_TRUE(testGraphNode4 != testGraphNode5);
    
    string inputName6 = "test";
    double inputValue6 = 60.05;
    double inputXCoord6 = 12.25;
    double inputYCoord6 = -4.00;
    GraphNode testGraphNode6(inputName6, inputValue6, inputXCoord6, inputYCoord6);
    
    EXPECT_FALSE(testGraphNode == testGraphNode6);
    EXPECT_FALSE(testGraphNode2 == testGraphNode6);
    EXPECT_FALSE(testGraphNode3 == testGraphNode6);
    EXPECT_FALSE(testGraphNode4 == testGraphNode6);
    EXPECT_FALSE(testGraphNode5 == testGraphNode6);
    
    EXPECT_TRUE(testGraphNode != testGraphNode6);
    EXPECT_TRUE(testGraphNode2 != testGraphNode6);
    EXPECT_TRUE(testGraphNode3 != testGraphNode6);
    EXPECT_TRUE(testGraphNode4 != testGraphNode6);
    EXPECT_TRUE(testGraphNode5 != testGraphNode6);
}

TEST(GraphNode_class, operator_insert_node_contents)
{
    GraphNode defaultGraphNode;
    
    string inputName = "test";
    double inputValue = 55.32;
    double inputXCoord = 2.50;
    double inputYCoord = -1.75;
    
    std::stringstream ss;
    ss << inputName << " "
       << inputValue << " "
       << inputXCoord << " "
       << inputYCoord;
    
    GraphNode updatedGraphNode;
    ss >> updatedGraphNode;
    
    string testName = updatedGraphNode.getNodeName();
    EXPECT_EQ(testName, inputName);
    
    double testValue = updatedGraphNode.getNodeValue();
    EXPECT_EQ(testValue, inputValue);
    
    double testXCoord = updatedGraphNode.getNodeXCoord();
    EXPECT_EQ(testXCoord, inputXCoord);
    
    double testYCoord = updatedGraphNode.getNodeYCoord();
    EXPECT_EQ(testYCoord, inputYCoord);
    
    EXPECT_FALSE(defaultGraphNode == updatedGraphNode);
}

TEST(GraphNode_class, operator_copy_assignment)
{
    GraphNode testGraphNode;
    
    string inputName = "test";
    double inputValue = 55.32;
    double inputXCoord = 2.50;
    double inputYCoord = -1.75;
    
    GraphNode inputGraphNode(inputName, inputValue,
                            inputXCoord, inputYCoord);
    
    testGraphNode = inputGraphNode;
    
    string testName = testGraphNode.getNodeName();
    EXPECT_EQ(testName, inputName);
    
    double testValue = testGraphNode.getNodeValue();
    EXPECT_EQ(testValue, inputValue);
    
    double testXCoord = testGraphNode.getNodeXCoord();
    EXPECT_EQ(testXCoord, inputXCoord);
    
    double testYCoord = testGraphNode.getNodeYCoord();
    EXPECT_EQ(testYCoord, inputYCoord);
    
    EXPECT_TRUE(inputGraphNode == testGraphNode);
}

