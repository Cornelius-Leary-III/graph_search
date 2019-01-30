//
// Created by carpenter on 1/29/19.
//

#include <gtest/gtest.h>
#include "GraphEdge.h"

TEST(GraphEdge_class, constructor_no_params)
{
    GraphEdge testEdge;
    
    GraphNode testCurrentNode;
    GraphNode resultCurrentNode = testEdge.getSourceNode();
    EXPECT_TRUE(resultCurrentNode == testCurrentNode);
    
    GraphNode testDestinationNode;
    GraphNode resultDestinationNode = testEdge.getDestinationNode();
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
    GraphNode resultCurrentNode = testEdge.getSourceNode();
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
    GraphNode resultCurrentNode = testEdge.getSourceNode();
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
    string inputLabel("test_label");

    testEdge.setSourceNode(testSourceNode);
    testEdge.setDestinationNode(testDestinationNode);
    testEdge.setWeight(inputWeight);
    testEdge.setLabel(inputLabel);

    GraphNode resultCurrentNode = testEdge.getSourceNode();
    EXPECT_TRUE(resultCurrentNode == testSourceNode);

    GraphNode resultDestinationNode = testEdge.getDestinationNode();
    EXPECT_TRUE(resultDestinationNode == testDestinationNode);

    EXPECT_EQ(testEdge.getWeight(), inputWeight);
    EXPECT_EQ(testEdge.getLabel(), inputLabel);
}

