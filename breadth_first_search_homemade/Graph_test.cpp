//
// Created by carpenter on 1/30/19.
//

#include <gtest/gtest.h>
#include "Graph.h"

TEST(Graph_class, constructor_no_params)
{
    Graph testGraph;
    
    auto testNodeList = testGraph.getNodeList();
    auto testNodeCount = testGraph.getNodeCount();
    bool testDirectedGraphFlag = testGraph.isGraphDirected();
    auto testAdjList = testGraph.getAdjacencyList();
    
    EXPECT_TRUE(testNodeList.empty());
    EXPECT_EQ(testNodeCount, 0);
    EXPECT_TRUE(testAdjList.empty());
    EXPECT_TRUE(testDirectedGraphFlag);
}

TEST(Graph_class, constructor_directed_graph_state_param)
{
    Graph testUndirectedGraph(false);
    
    auto undirectedNodeList = testUndirectedGraph.getNodeList();
    auto undirectedNodeCount = testUndirectedGraph.getNodeCount();
    bool undirectedDirectedGraphFlag = testUndirectedGraph.isGraphDirected();
    auto undirectedAdjList = testUndirectedGraph.getAdjacencyList();
    
    EXPECT_TRUE(undirectedNodeList.empty());
    EXPECT_EQ(undirectedNodeCount, 0);
    EXPECT_TRUE(undirectedAdjList.empty());
    EXPECT_FALSE(undirectedDirectedGraphFlag);
    
    Graph testDirectedGraph(true);
    
    auto directedNodeList = testDirectedGraph.getNodeList();
    auto directedNodeCount = testDirectedGraph.getNodeCount();
    bool directedDirectedGraphFlag = testDirectedGraph.isGraphDirected();
    auto directedAdjList = testDirectedGraph.getAdjacencyList();
    
    EXPECT_TRUE(directedNodeList.empty());
    EXPECT_EQ(directedNodeCount, 0);
    EXPECT_TRUE(directedAdjList.empty());
    EXPECT_TRUE(directedDirectedGraphFlag);
}

TEST(Graph_class, add_node)
{
    Graph testGraph;
    
    GraphNode node0("node0");
    GraphNode node1("node1", 10.0);
    GraphNode node2("node2", 1.0, 2.0);
    GraphNode node3("node3", 5.5, -5.0, 5.0);
    
    unsigned long expectedNodeCount = 0;
    EXPECT_EQ(testGraph.getNodeCount(), expectedNodeCount);
    EXPECT_TRUE(testGraph.getNodeList().empty());
    
    testGraph.addNode(node0);
    EXPECT_EQ(testGraph.getNodeCount(), ++expectedNodeCount);
    
    testGraph.addNode(node1);
    EXPECT_EQ(testGraph.getNodeCount(), ++expectedNodeCount);
    
    testGraph.addNode(node2);
    EXPECT_EQ(testGraph.getNodeCount(), ++expectedNodeCount);
    
    testGraph.addNode(node3);
    EXPECT_EQ(testGraph.getNodeCount(), ++expectedNodeCount);
    
    auto testNodeList = testGraph.getNodeList();
    auto testNodeIter = testNodeList.begin();
    auto testNodesEnd = testNodeList.end();
    
    EXPECT_TRUE(*testNodeIter == node0);
    EXPECT_TRUE(*(++testNodeIter) == node1);
    EXPECT_TRUE(*(++testNodeIter) == node2);
    EXPECT_TRUE(*(++testNodeIter) == node3);
}

TEST(Graph_class, add_directed_edge_one_source_node)
{
    Graph testGraph;
    EXPECT_TRUE(testGraph.isGraphDirected());
    
    string name0 = "node0";
    string name1 = "node1";
    string name2 = "node2";
    string name3 = "node3";
    
    GraphNode node0(name0);
    GraphNode node1(name1, 10.0);
    GraphNode node2(name2, 1.0, 2.0);
    GraphNode node3(name3, 5.5, -5.0, 5.0);
    
    GraphEdge testEdge01;
    testEdge01.setSourceNode(node0);
    testEdge01.setDestinationNode(node1);
    
    EXPECT_TRUE(testEdge01.getSourceName() == name0);
    EXPECT_TRUE(testEdge01.getSourceNode() == node0);
    EXPECT_TRUE(testEdge01.getDestinationNode() == node1);
    EXPECT_EQ(testEdge01.getLabel(), "");
    EXPECT_EQ(testEdge01.getWeight(), 1.00);
    
    GraphEdge testEdge02;
    testEdge02.setSourceNode(node0);
    testEdge02.setDestinationNode(node2);
    
    EXPECT_TRUE(testEdge02.getSourceName() == name0);
    EXPECT_TRUE(testEdge02.getSourceNode() == node0);
    EXPECT_TRUE(testEdge02.getDestinationNode() == node2);
    EXPECT_EQ(testEdge02.getLabel(), "");
    EXPECT_EQ(testEdge02.getWeight(), 1.00);
    
    GraphEdge testEdge03;
    testEdge03.setSourceNode(node0);
    testEdge03.setDestinationNode(node3);
    
    EXPECT_TRUE(testEdge03.getSourceName() == name0);
    EXPECT_TRUE(testEdge03.getSourceNode() == node0);
    EXPECT_TRUE(testEdge03.getDestinationNode() == node3);
    EXPECT_EQ(testEdge03.getLabel(), "");
    EXPECT_EQ(testEdge03.getWeight(), 1.00);
    
    testGraph.addEdge(testEdge01);
    testGraph.addEdge(testEdge02);
    testGraph.addEdge(testEdge03);
    
    auto testAdjList = testGraph.getAdjacencyList();
    EXPECT_EQ(testAdjList.size(), 1);
    
    auto nodeMapIter = testAdjList.begin();
    auto nodeMapEnd = testAdjList.end();
    
    auto edgeSetForCurrentNode = nodeMapIter->second;
    EXPECT_EQ(edgeSetForCurrentNode.size(), 3);
    
    auto edgeIter = edgeSetForCurrentNode.begin();
    auto edgesEnd = edgeSetForCurrentNode.end();
    
    EXPECT_EQ(nodeMapIter->first, name0);
    EXPECT_TRUE(*edgeIter == testEdge01);
    EXPECT_TRUE(*(++edgeIter) == testEdge02);
    EXPECT_TRUE(*(++edgeIter) == testEdge03);
}

TEST(Graph_class, add_directed_edge_multiple_source_nodes)
{
    Graph testGraph;
    EXPECT_TRUE(testGraph.isGraphDirected());
    
    string name0 = "node0";
    string name1 = "node1";
    string name2 = "node2";
    string name3 = "node3";
    
    GraphNode node0(name0);
    GraphNode node1(name1, 10.0);
    GraphNode node2(name2, 1.0, 2.0);
    GraphNode node3(name3, 5.5, -5.0, 5.0);
    
    GraphEdge testEdge01;
    testEdge01.setSourceNode(node0);
    testEdge01.setDestinationNode(node1);
    
    EXPECT_TRUE(testEdge01.getSourceName() == name0);
    EXPECT_TRUE(testEdge01.getSourceNode() == node0);
    EXPECT_TRUE(testEdge01.getDestinationNode() == node1);
    EXPECT_EQ(testEdge01.getLabel(), "");
    EXPECT_EQ(testEdge01.getWeight(), 1.00);
    
    GraphEdge testEdge02;
    testEdge02.setSourceNode(node0);
    testEdge02.setDestinationNode(node2);
    
    EXPECT_TRUE(testEdge02.getSourceName() == name0);
    EXPECT_TRUE(testEdge02.getSourceNode() == node0);
    EXPECT_TRUE(testEdge02.getDestinationNode() == node2);
    EXPECT_EQ(testEdge02.getLabel(), "");
    EXPECT_EQ(testEdge02.getWeight(), 1.00);
    
    GraphEdge testEdge03;
    testEdge03.setSourceNode(node0);
    testEdge03.setDestinationNode(node3);
    
    EXPECT_TRUE(testEdge03.getSourceName() == name0);
    EXPECT_TRUE(testEdge03.getSourceNode() == node0);
    EXPECT_TRUE(testEdge03.getDestinationNode() == node3);
    EXPECT_EQ(testEdge03.getLabel(), "");
    EXPECT_EQ(testEdge03.getWeight(), 1.00);
    
    GraphEdge testEdge10;
    testEdge10.setSourceNode(node1);
    testEdge10.setDestinationNode(node0);
    
    EXPECT_TRUE(testEdge10.getSourceName() == name1);
    EXPECT_TRUE(testEdge10.getSourceNode() == node1);
    EXPECT_TRUE(testEdge10.getDestinationNode() == node0);
    EXPECT_EQ(testEdge10.getLabel(), "");
    EXPECT_EQ(testEdge10.getWeight(), 1.00);
    
    GraphEdge testEdge12;
    testEdge12.setSourceNode(node1);
    testEdge12.setDestinationNode(node0);
    
    EXPECT_TRUE(testEdge12.getSourceName() == name1);
    EXPECT_TRUE(testEdge12.getSourceNode() == node1);
    EXPECT_TRUE(testEdge12.getDestinationNode() == node0);
    EXPECT_EQ(testEdge12.getLabel(), "");
    EXPECT_EQ(testEdge12.getWeight(), 1.00);
    
    GraphEdge testEdge13;
    testEdge13.setSourceNode(node1);
    testEdge13.setDestinationNode(node0);
    
    EXPECT_TRUE(testEdge13.getSourceName() == name1);
    EXPECT_TRUE(testEdge13.getSourceNode() == node1);
    EXPECT_TRUE(testEdge13.getDestinationNode() == node0);
    EXPECT_EQ(testEdge13.getLabel(), "");
    EXPECT_EQ(testEdge13.getWeight(), 1.00);
    
    testGraph.addEdge(testEdge01);
    testGraph.addEdge(testEdge02);
    testGraph.addEdge(testEdge03);
    testGraph.addEdge(testEdge10);
    testGraph.addEdge(testEdge12);
    testGraph.addEdge(testEdge13);
    
    auto testAdjList = testGraph.getAdjacencyList();
    EXPECT_EQ(testAdjList.size(), 2);
    
    auto nodeMapIter = testAdjList.begin();
    auto nodeMapEnd = testAdjList.end();
    
    auto edgeSetForNode0 = nodeMapIter->second;
    EXPECT_EQ(edgeSetForNode0.size(), 3);
    
    auto edgeIter = edgeSetForNode0.begin();
    
    EXPECT_EQ(nodeMapIter->first, name0);
    EXPECT_TRUE(*edgeIter == testEdge01);
    EXPECT_TRUE(*(++edgeIter) == testEdge02);
    EXPECT_TRUE(*(++edgeIter) == testEdge03);
    
    auto edgeSetForNode1 = (++nodeMapIter)->second;
    EXPECT_EQ(edgeSetForNode1.size(), 3);
    
    auto node1EdgeIter = edgeSetForNode1.begin();
    
    EXPECT_EQ(nodeMapIter->first, name1);
    EXPECT_TRUE(*node1EdgeIter == testEdge10);
    EXPECT_TRUE(*(++node1EdgeIter) == testEdge12);
    EXPECT_TRUE(*(++node1EdgeIter) == testEdge13);
}

TEST(Graph_class, add_undirected_edges)
{
    Graph testGraph(false);
    
    EXPECT_FALSE(testGraph.isGraphDirected());
    
    string name0 = "node0";
    string name1 = "node1";
    string name2 = "node2";
    string name3 = "node3";
    
    GraphNode node0(name0);
    GraphNode node1(name1, 10.0);
    GraphNode node2(name2, 1.0, 2.0);
    GraphNode node3(name3, 5.5, -5.0, 5.0);
    
    GraphEdge testEdge01;
    testEdge01.setSourceNode(node0);
    testEdge01.setDestinationNode(node1);
    
    EXPECT_TRUE(testEdge01.getSourceName() == name0);
    EXPECT_TRUE(testEdge01.getSourceNode() == node0);
    EXPECT_TRUE(testEdge01.getDestinationNode() == node1);
    EXPECT_EQ(testEdge01.getLabel(), "");
    EXPECT_EQ(testEdge01.getWeight(), 1.00);
    
    GraphEdge testEdge02;
    testEdge02.setSourceNode(node0);
    testEdge02.setDestinationNode(node2);
    
    EXPECT_TRUE(testEdge02.getSourceName() == name0);
    EXPECT_TRUE(testEdge02.getSourceNode() == node0);
    EXPECT_TRUE(testEdge02.getDestinationNode() == node2);
    EXPECT_EQ(testEdge02.getLabel(), "");
    EXPECT_EQ(testEdge02.getWeight(), 1.00);
    
    GraphEdge testEdge03;
    testEdge03.setSourceNode(node0);
    testEdge03.setDestinationNode(node3);
    
    EXPECT_TRUE(testEdge03.getSourceName() == name0);
    EXPECT_TRUE(testEdge03.getSourceNode() == node0);
    EXPECT_TRUE(testEdge03.getDestinationNode() == node3);
    EXPECT_EQ(testEdge03.getLabel(), "");
    EXPECT_EQ(testEdge03.getWeight(), 1.00);
    
    GraphEdge testEdge10;
    testEdge10.setSourceNode(node1);
    testEdge10.setDestinationNode(node0);
    
    EXPECT_TRUE(testEdge10.getSourceName() == name1);
    EXPECT_TRUE(testEdge10.getSourceNode() == node1);
    EXPECT_TRUE(testEdge10.getDestinationNode() == node0);
    EXPECT_EQ(testEdge10.getLabel(), "");
    EXPECT_EQ(testEdge10.getWeight(), 1.00);
    
    GraphEdge testEdge20;
    testEdge20.setSourceNode(node2);
    testEdge20.setDestinationNode(node0);
    
    EXPECT_TRUE(testEdge20.getSourceName() == name2);
    EXPECT_TRUE(testEdge20.getSourceNode() == node2);
    EXPECT_TRUE(testEdge20.getDestinationNode() == node0);
    EXPECT_EQ(testEdge20.getLabel(), "");
    EXPECT_EQ(testEdge20.getWeight(), 1.00);
    
    GraphEdge testEdge30;
    testEdge30.setSourceNode(node3);
    testEdge30.setDestinationNode(node0);
    
    EXPECT_TRUE(testEdge30.getSourceName() == name3);
    EXPECT_TRUE(testEdge30.getSourceNode() == node3);
    EXPECT_TRUE(testEdge30.getDestinationNode() == node0);
    EXPECT_EQ(testEdge30.getLabel(), "");
    EXPECT_EQ(testEdge30.getWeight(), 1.00);
    
    testGraph.addEdge(testEdge01);
    testGraph.addEdge(testEdge02);
    testGraph.addEdge(testEdge03);
    
    auto testAdjList = testGraph.getAdjacencyList();
    EXPECT_EQ(testAdjList.size(), 4);
    
    auto nodeMapIter = testAdjList.begin();
    auto nodeMapEnd = testAdjList.end();
    
    auto edgeSetForNode0 = nodeMapIter->second;
    EXPECT_EQ(edgeSetForNode0.size(), 3);
    auto edgeIter = edgeSetForNode0.begin();
    EXPECT_EQ(nodeMapIter->first, name0);
    EXPECT_TRUE(*edgeIter == testEdge01);
    EXPECT_TRUE(*(++edgeIter) == testEdge02);
    EXPECT_TRUE(*(++edgeIter) == testEdge03);
    
    auto edgeSetForNode1 = (++nodeMapIter)->second;
    EXPECT_EQ(edgeSetForNode1.size(), 1);
    auto node1EdgeIter = edgeSetForNode1.begin();
    EXPECT_EQ(nodeMapIter->first, name1);
    EXPECT_TRUE(*node1EdgeIter == testEdge10);
    
    auto edgeSetForNode2 = (++nodeMapIter)->second;
    EXPECT_EQ(edgeSetForNode2.size(), 1);
    auto node2EdgeIter = edgeSetForNode2.begin();
    EXPECT_EQ(nodeMapIter->first, name2);
    EXPECT_TRUE(*node2EdgeIter == testEdge20);
    
    auto edgeSetForNode3 = (++nodeMapIter)->second;
    EXPECT_EQ(edgeSetForNode3.size(), 1);
    auto node3EdgeIter = edgeSetForNode3.begin();
    EXPECT_EQ(nodeMapIter->first, name3);
    EXPECT_TRUE(*node3EdgeIter == testEdge30);
    
}










