//
// Created by carpenter on 1/29/19.
//

#include <gtest/gtest.h>
#include "Edge.h"

TEST(GraphEdge_class, constructor_no_params)
{
    GraphEdge testEdge;
    
    GraphNode resultCurrentNode = testEdge.getCurrentNode();
    GraphNode testCurrentNode;
    EXPECT_TRUE(resultCurrentNode == testCurrentNode);
    
    GraphNode resultDestinationNode = testEdge.getDestinationNode();
    GraphNode testDestinationNode;
    EXPECT_TRUE(resultDestinationNode == testDestinationNode);
    
    EXPECT_EQ(testEdge.getWeight(), 1.00);
    EXPECT_EQ(testEdge.getLabel(), "");
}

TEST(GraphEdge_class, set_nodes)
{
    GraphEdge testEdge;
    
    string inputSourceName = "aaaaa___bbbbb";
    double inputSourceValue = 1.5;
    double inputSourceXCoord = 0.25;
    double inputSourceYCoord = 0.50;
    GraphNode testSourceNode(inputSourceName, inputSourceValue,
                             inputSourceXCoord, inputSourceYCoord);
    
    string inputDestinationName = "another_dest_node";
    double inputDestinationValue = 2.50;
    double inputDestinationXCoord = -12.25;
    double inputDestinationYCoord = 3.00;
    GraphNode testDestinationNode(inputDestinationName, inputDestinationValue,
                                  inputDestinationXCoord, inputDestinationYCoord);
    
    testEdge.setSourceNode(testSourceNode);
    GraphNode resultCurrentNode = testEdge.getCurrentNode();
    EXPECT_TRUE(resultCurrentNode == testSourceNode);
    
    testEdge.setDestinationNode(testDestinationNode);
    GraphNode resultDestinationNode = testEdge.getDestinationNode();
    EXPECT_TRUE(resultDestinationNode == testDestinationNode);
    
    EXPECT_EQ(testEdge.getWeight(), 1.00);
    EXPECT_EQ(testEdge.getLabel(), "");
}

TEST(GraphEdge_class, set_nodes_weight)
{
    GraphEdge testEdge;
    
    string inputSourceName = "aaaaa___bbbbb";
    double inputSourceValue = 1.5;
    double inputSourceXCoord = 0.25;
    double inputSourceYCoord = 0.50;
    GraphNode testSourceNode(inputSourceName, inputSourceValue,
                             inputSourceXCoord, inputSourceYCoord);
    
    string inputDestinationName = "another_dest_node";
    double inputDestinationValue = 2.50;
    double inputDestinationXCoord = -12.25;
    double inputDestinationYCoord = 3.00;
    GraphNode testDestinationNode(inputDestinationName, inputDestinationValue,
                                  inputDestinationXCoord, inputDestinationYCoord);
    
    double inputWeight = 4.50;
    testEdge.setWeight(inputWeight);
    
    testEdge.setSourceNode(testSourceNode);
    GraphNode resultCurrentNode = testEdge.getCurrentNode();
    EXPECT_TRUE(resultCurrentNode == testSourceNode);
    
    testEdge.setDestinationNode(testDestinationNode);
    GraphNode resultDestinationNode = testEdge.getDestinationNode();
    EXPECT_TRUE(resultDestinationNode == testDestinationNode);
    
    EXPECT_EQ(testEdge.getWeight(), inputWeight);
    EXPECT_EQ(testEdge.getLabel(), "");
}

TEST(GraphEdge_class, set_nodes_weight_label)
{
    GraphEdge testEdge;
    
    string inputSourceName = "aaaaa___bbbbb";
    double inputSourceValue = 1.5;
    double inputSourceXCoord = 0.25;
    double inputSourceYCoord = 0.50;
    GraphNode testSourceNode(inputSourceName, inputSourceValue,
                             inputSourceXCoord, inputSourceYCoord);
    
    string inputDestinationName = "another_dest_node";
    double inputDestinationValue = 2.50;
    double inputDestinationXCoord = -12.25;
    double inputDestinationYCoord = 3.00;
    GraphNode testDestinationNode(inputDestinationName, inputDestinationValue,
                                  inputDestinationXCoord, inputDestinationYCoord);
    
    double inputWeight = 4.50;
    testEdge.setWeight(inputWeight);
    
    string inputLabel("test_label");
    testEdge.setLabel(inputLabel);
    
    testEdge.setSourceNode(testSourceNode);
    GraphNode resultCurrentNode = testEdge.getCurrentNode();
    EXPECT_TRUE(resultCurrentNode == testSourceNode);
    
    testEdge.setDestinationNode(testDestinationNode);
    GraphNode resultDestinationNode = testEdge.getDestinationNode();
    EXPECT_TRUE(resultDestinationNode == testDestinationNode);
    
    EXPECT_EQ(testEdge.getWeight(), inputWeight);
    EXPECT_EQ(testEdge.getLabel(), inputLabel);
}

