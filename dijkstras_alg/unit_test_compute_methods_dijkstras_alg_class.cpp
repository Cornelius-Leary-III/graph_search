//
// Created by cornelius on 4/23/19.
//

#include <gtest/gtest.h>
#include "Dijkstras_Alg.h"

TEST(computePathFails, tooLargeStartNode)
{
   Dijkstras_Alg planner(10);

   EXPECT_THROW(planner.compute("15"), StartNodeProvidedIsNonExistentException);
}

TEST(computePathFails, negativeStartNode)
{
   Dijkstras_Alg planner(20);

   EXPECT_THROW(planner.compute("-5"), StartNodeProvidedIsNonExistentException);
}

TEST(computePath, unweightedGraph)
{
   std::vector<Edge> input_edges{{"0", "1"},
                                 {"0", "2"},
                                 {"0", "3"},
                                 {"1", "3"},
                                 {"1", "4"},
                                 {"2", "3"},
                                 {"3", "4"},
                                 {"2", "5"},
                                 {"4", "5"}};

   EdgeSetBuilder edge_builder(input_edges, false);

   Dijkstras_Alg planner(6);
   EXPECT_NO_THROW(planner.addEdges(edge_builder.getEdgeSet()));
   EXPECT_NO_THROW(planner.compute("0"));

   auto output_distance_table = planner.getDistanceTable();
   EXPECT_DOUBLE_EQ(output_distance_table["0"], 0.00);
   EXPECT_DOUBLE_EQ(output_distance_table["1"], 1.00);
   EXPECT_DOUBLE_EQ(output_distance_table["2"], 1.00);
   EXPECT_DOUBLE_EQ(output_distance_table["3"], 1.00);
   EXPECT_DOUBLE_EQ(output_distance_table["4"], 2.00);
   EXPECT_DOUBLE_EQ(output_distance_table["5"], 2.00);
}

TEST(computePath, weightedGraph)
{
   std::vector<Edge> input_edges{{"0", "1", 7},
                                 {"0", "2", 14},
                                 {"0", "3", 9},
                                 {"1", "3", 10},
                                 {"1", "4", 15},
                                 {"2", "3", 2},
                                 {"3", "4", 11},
                                 {"2", "5", 9},
                                 {"4", "5", 6}};

   EdgeSetBuilder edge_builder(input_edges, false);

   Dijkstras_Alg planner(6);
   EXPECT_NO_THROW(planner.addEdges(edge_builder.getEdgeSet()));
   EXPECT_NO_THROW(planner.compute("0"));

   auto output_distance_table = planner.getDistanceTable();
   EXPECT_DOUBLE_EQ(output_distance_table["0"], 0);
   EXPECT_DOUBLE_EQ(output_distance_table["1"], 7);
   EXPECT_DOUBLE_EQ(output_distance_table["2"], 11);
   EXPECT_DOUBLE_EQ(output_distance_table["3"], 9);
   EXPECT_DOUBLE_EQ(output_distance_table["4"], 20);
   EXPECT_DOUBLE_EQ(output_distance_table["5"], 20);
}

TEST(returnPathFromStartToGivenNode, unweightedGraph)
{
   std::vector<Edge> input_edges{{"0", "1"},
                                 {"0", "2"},
                                 {"0", "3"},
                                 {"1", "3"},
                                 {"1", "4"},
                                 {"2", "3"},
                                 {"3", "4"},
                                 {"2", "5"},
                                 {"4", "5"}};

   EdgeSetBuilder edge_builder(input_edges, false);

   Dijkstras_Alg planner(6);
   EXPECT_NO_THROW(planner.addEdges(edge_builder.getEdgeSet()));
   EXPECT_NO_THROW(planner.compute("0"));

   auto output_path_00 = planner.getPathFromStartToNode("0", "0");
   auto output_path_01 = planner.getPathFromStartToNode("0", "1");
   auto output_path_02 = planner.getPathFromStartToNode("0", "2");
   auto output_path_03 = planner.getPathFromStartToNode("0", "3");
   auto output_path_04 = planner.getPathFromStartToNode("0", "4");
   auto output_path_05 = planner.getPathFromStartToNode("0", "5");

   auto expected_path_00 = std::vector<std::string>{"0"};
   auto expected_path_01 = std::vector<std::string>{"0", "1"};
   auto expected_path_02 = std::vector<std::string>{"0", "2"};
   auto expected_path_03 = std::vector<std::string>{"0", "3"};
   auto expected_path_04 = std::vector<std::string>{"0", "3", "4"};
   auto expected_path_05 = std::vector<std::string>{"0", "2", "5"};

   EXPECT_EQ(output_path_00, expected_path_00);
   EXPECT_EQ(output_path_01, expected_path_01);
   EXPECT_EQ(output_path_02, expected_path_02);
   EXPECT_EQ(output_path_03, expected_path_03);
   EXPECT_EQ(output_path_04, expected_path_04);
   EXPECT_EQ(output_path_05, expected_path_05);
}

TEST(returnPathFromStartToGivenNode, weightedGraph)
{
   std::vector<Edge> input_edges{{"0", "1", 7},
                                 {"0", "2", 14},
                                 {"0", "3", 9},
                                 {"1", "3", 10},
                                 {"1", "4", 15},
                                 {"2", "3", 2},
                                 {"3", "4", 11},
                                 {"2", "5", 9},
                                 {"4", "5", 6}};

   EdgeSetBuilder edge_builder(input_edges, false);

   Dijkstras_Alg planner(6);
   EXPECT_NO_THROW(planner.addEdges(edge_builder.getEdgeSet()));
   EXPECT_NO_THROW(planner.compute("0"));

   auto output_path_00 = planner.getPathFromStartToNode("0", "0");
   auto output_path_01 = planner.getPathFromStartToNode("0", "1");
   auto output_path_02 = planner.getPathFromStartToNode("0", "2");
   auto output_path_03 = planner.getPathFromStartToNode("0", "3");
   auto output_path_04 = planner.getPathFromStartToNode("0", "4");
   auto output_path_05 = planner.getPathFromStartToNode("0", "5");

   auto expected_path_00 = std::vector<std::string>{"0"};
   auto expected_path_01 = std::vector<std::string>{"0", "1"};
   auto expected_path_02 = std::vector<std::string>{"0", "3", "2"};
   auto expected_path_03 = std::vector<std::string>{"0", "3"};
   auto expected_path_04 = std::vector<std::string>{"0", "3", "4"};
   auto expected_path_05 = std::vector<std::string>{"0", "3", "2", "5"};

   EXPECT_EQ(output_path_00, expected_path_00);
   EXPECT_EQ(output_path_01, expected_path_01);
   EXPECT_EQ(output_path_02, expected_path_02);
   EXPECT_EQ(output_path_03, expected_path_03);
   EXPECT_EQ(output_path_04, expected_path_04);
   EXPECT_EQ(output_path_05, expected_path_05);
}
