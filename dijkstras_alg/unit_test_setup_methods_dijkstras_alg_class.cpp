//
// Created by cornelius on 4/23/19.
//

#include <gtest/gtest.h>
#include "Dijkstras_Alg.h"

TEST(DijkstrasAlgCtor, zeroNodes)
{
   Dijkstras_Alg planner(0);

   EXPECT_TRUE(planner.getEdgeSet().empty());
   EXPECT_TRUE(planner.getUnvisitedVertices().empty());

   EXPECT_TRUE(planner.getAdjacencyList().empty());
   EXPECT_TRUE(planner.getDistanceTable().empty());
   EXPECT_TRUE(planner.getPredecessorTable().empty());
   //   EXPECT_TRUE(planner.getVisitedTable().empty());
}

TEST(DijkstrasAlgCtor, finiteNodeCount)
{
   Dijkstras_Alg planner(10);

   EXPECT_TRUE(planner.getEdgeSet().empty());
   EXPECT_TRUE(planner.getUnvisitedVertices().empty());

   EXPECT_EQ(planner.getAdjacencyList().size(), 10);
   EXPECT_EQ(planner.getDistanceTable().size(), 10);
   EXPECT_EQ(planner.getPredecessorTable().size(), 10);
   //   EXPECT_EQ(planner.getVisitedTable().size(), 10);
}

TEST(addZeroBasedEdges, unweightedEdges)
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

   Dijkstras_Alg planner(6);
   planner.addEdges(input_edges);

   EXPECT_EQ(planner.getEdgeSet(), input_edges);

   EXPECT_EQ(planner.getEdgeSet().size(), 9);
   EXPECT_EQ(planner.getAdjacencyList().size(), 6);

   auto output_adj_list = planner.getAdjacencyList();

   auto source_iter      = output_adj_list.begin();
   auto destination_iter = source_iter->second.begin();

   EXPECT_EQ(destination_iter->first, "1");
   EXPECT_DOUBLE_EQ(destination_iter->second, 1.00);

   ++destination_iter;
   EXPECT_EQ(destination_iter->first, "2");
   EXPECT_DOUBLE_EQ(destination_iter->second, 1.00);

   ++destination_iter;
   EXPECT_EQ(destination_iter->first, "3");
   EXPECT_DOUBLE_EQ(destination_iter->second, 1.00);

   ++source_iter;
   destination_iter = source_iter->second.begin();

   EXPECT_EQ(destination_iter->first, "3");
   EXPECT_DOUBLE_EQ(destination_iter->second, 1.00);

   ++destination_iter;
   EXPECT_EQ(destination_iter->first, "4");
   EXPECT_DOUBLE_EQ(destination_iter->second, 1.00);

   ++source_iter;
   destination_iter = source_iter->second.begin();

   EXPECT_EQ(destination_iter->first, "3");
   EXPECT_DOUBLE_EQ(destination_iter->second, 1.00);

   ++destination_iter;
   EXPECT_EQ(destination_iter->first, "5");
   EXPECT_DOUBLE_EQ(destination_iter->second, 1.00);

   ++source_iter;
   destination_iter = source_iter->second.begin();

   EXPECT_EQ(destination_iter->first, "4");
   EXPECT_DOUBLE_EQ(destination_iter->second, 1.00);

   ++source_iter;
   destination_iter = source_iter->second.begin();

   EXPECT_EQ(destination_iter->first, "5");
   EXPECT_DOUBLE_EQ(destination_iter->second, 1.00);
}

TEST(addZeroBasedEdges, weightedEdges)
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

   Dijkstras_Alg planner(6);
   planner.addEdges(input_edges);

   EXPECT_EQ(planner.getEdgeSet(), input_edges);

   EXPECT_EQ(planner.getEdgeSet().size(), 9);
   EXPECT_EQ(planner.getAdjacencyList().size(), 6);

   auto output_adj_list = planner.getAdjacencyList();

   auto source_iter      = output_adj_list.begin();
   auto destination_iter = source_iter->second.begin();

   EXPECT_EQ(destination_iter->first, "1");
   EXPECT_DOUBLE_EQ(destination_iter->second, 7.00);

   ++destination_iter;
   EXPECT_EQ(destination_iter->first, "2");
   EXPECT_DOUBLE_EQ(destination_iter->second, 14.00);

   ++destination_iter;
   EXPECT_EQ(destination_iter->first, "3");
   EXPECT_DOUBLE_EQ(destination_iter->second, 9.00);

   ++source_iter;
   destination_iter = source_iter->second.begin();

   EXPECT_EQ(destination_iter->first, "3");
   EXPECT_DOUBLE_EQ(destination_iter->second, 10.00);

   ++destination_iter;
   EXPECT_EQ(destination_iter->first, "4");
   EXPECT_DOUBLE_EQ(destination_iter->second, 15.00);

   ++source_iter;
   destination_iter = source_iter->second.begin();

   EXPECT_EQ(destination_iter->first, "3");
   EXPECT_DOUBLE_EQ(destination_iter->second, 2.00);

   ++destination_iter;
   EXPECT_EQ(destination_iter->first, "5");
   EXPECT_DOUBLE_EQ(destination_iter->second, 9.00);

   ++source_iter;
   destination_iter = source_iter->second.begin();

   EXPECT_EQ(destination_iter->first, "4");
   EXPECT_DOUBLE_EQ(destination_iter->second, 11.00);

   ++source_iter;
   destination_iter = source_iter->second.begin();

   EXPECT_EQ(destination_iter->first, "5");
   EXPECT_DOUBLE_EQ(destination_iter->second, 6.00);
}

TEST(addEdges, allPositiveEdgeWeights)
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

   Dijkstras_Alg planner(6);

   EXPECT_NO_THROW(planner.addEdges(input_edges));
}

TEST(addEdges, mixedPositiveNegativeEdgeWeights)
{
   std::vector<Edge> input_edges{{"0", "1", 7},
                                 {"0", "2", -14},
                                 {"0", "3", 9},
                                 {"1", "3", 10},
                                 {"1", "4", -15},
                                 {"2", "3", -2},
                                 {"3", "4", -11},
                                 {"2", "5", 9},
                                 {"4", "5", 6}};

   Dijkstras_Alg planner(6);

   EXPECT_THROW(planner.addEdges(input_edges), NegativeEdgeWeightsException);
}
