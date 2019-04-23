//
// Created by carpenter on 2/13/19.
//

#include <gtest/gtest.h>
#include "EdgeSetBuilder.h"



//bool operator==(Edge& lhs, Edge& rhs)
//{
//    return (lhs.source == rhs.source) &&
//           (lhs.destination == rhs.destination) &&
//           (lhs.weight == rhs.weight);
//}



//bool operator!=(Edge& lhs, Edge& rhs)
//{
//    return !(lhs == rhs);
//}

TEST(EdgeSetBuilder_class, constructor_no_params)
{
    EdgeSetBuilder testESB;
    
    auto outputEdgeSet = testESB.getEdgeSet();
    auto outputEdgeCount = testESB.getEdgeCount();
    auto outputGraphDirected = testESB.isGraphDirected();
    auto outputNegativeEdgesAllowed = testESB.areNegativeEdgesAllowed();
    auto outputSelfLoopsAllowed = testESB.areSelfLoopsAllowed();
    
    EXPECT_TRUE(outputEdgeSet.empty());
    EXPECT_EQ(outputEdgeCount, 0);
    EXPECT_TRUE(outputGraphDirected);
    EXPECT_FALSE(outputNegativeEdgesAllowed);
    EXPECT_FALSE(outputSelfLoopsAllowed);
}

TEST(EdgeSetBuilder_class, constructor_3_states)
{
    EdgeSetBuilder testESB_000(false, false, false);
    EdgeSetBuilder testESB_001(false, false, true);
    EdgeSetBuilder testESB_010(false, true, false);
    EdgeSetBuilder testESB_011(false, true, true);
    EdgeSetBuilder testESB_100(true, false, false);
    EdgeSetBuilder testESB_101(true, false, true);
    EdgeSetBuilder testESB_110(true, true, false);
    EdgeSetBuilder testESB_111(true, true, true);
    
    EXPECT_TRUE(testESB_000.getEdgeSet().empty());
    EXPECT_FALSE(testESB_000.isGraphDirected());
    EXPECT_FALSE(testESB_000.areNegativeEdgesAllowed());
    EXPECT_FALSE(testESB_000.areSelfLoopsAllowed());
    
    EXPECT_TRUE(testESB_001.getEdgeSet().empty());
    EXPECT_FALSE(testESB_001.isGraphDirected());
    EXPECT_FALSE(testESB_001.areNegativeEdgesAllowed());
    EXPECT_TRUE(testESB_001.areSelfLoopsAllowed());
    
    EXPECT_TRUE(testESB_010.getEdgeSet().empty());
    EXPECT_FALSE(testESB_010.isGraphDirected());
    EXPECT_TRUE(testESB_010.areNegativeEdgesAllowed());
    EXPECT_FALSE(testESB_010.areSelfLoopsAllowed());
    
    EXPECT_TRUE(testESB_011.getEdgeSet().empty());
    EXPECT_FALSE(testESB_011.isGraphDirected());
    EXPECT_TRUE(testESB_011.areNegativeEdgesAllowed());
    EXPECT_TRUE(testESB_011.areSelfLoopsAllowed());
    
    EXPECT_TRUE(testESB_100.getEdgeSet().empty());
    EXPECT_TRUE(testESB_100.isGraphDirected());
    EXPECT_FALSE(testESB_100.areNegativeEdgesAllowed());
    EXPECT_FALSE(testESB_100.areSelfLoopsAllowed());
    
    EXPECT_TRUE(testESB_101.getEdgeSet().empty());
    EXPECT_TRUE(testESB_101.isGraphDirected());
    EXPECT_FALSE(testESB_101.areNegativeEdgesAllowed());
    EXPECT_TRUE(testESB_101.areSelfLoopsAllowed());
    
    EXPECT_TRUE(testESB_110.getEdgeSet().empty());
    EXPECT_TRUE(testESB_110.isGraphDirected());
    EXPECT_TRUE(testESB_110.areNegativeEdgesAllowed());
    EXPECT_FALSE(testESB_110.areSelfLoopsAllowed());
    
    EXPECT_TRUE(testESB_111.getEdgeSet().empty());
    EXPECT_TRUE(testESB_111.isGraphDirected());
    EXPECT_TRUE(testESB_111.areNegativeEdgesAllowed());
    EXPECT_TRUE(testESB_111.areSelfLoopsAllowed());
}

TEST(EdgeSetBuilder_class, constructor_edge_set_all_positive_weights)
{
    vector<Edge> inputEdges{
            {0, 1, 1},          // reused this edge set from test_Bellman_Ford.cpp,
            {0, 2, 4},          //      but gave all edges positive weights.
            {1, 2, 3},
            {1, 3, 2},
            {1, 4, 2},
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, 3}
    };
    
    EdgeSetBuilder testESB(inputEdges);
    
    auto outputEdgeSet = testESB.getEdgeSet();
    auto outputEdgeCount = testESB.getEdgeCount();
    auto outputGraphDirected = testESB.isGraphDirected();
    auto outputNegativeEdgesAllowed = testESB.areNegativeEdgesAllowed();
    auto outputSelfLoopsAllowed = testESB.areSelfLoopsAllowed();
    
    EXPECT_FALSE(outputEdgeSet.empty());
    EXPECT_EQ(outputEdgeCount, inputEdges.size());
    EXPECT_TRUE(outputGraphDirected);
    EXPECT_FALSE(outputNegativeEdgesAllowed);
    EXPECT_FALSE(outputSelfLoopsAllowed);
}

TEST(EdgeSetBuilder_class, constructor_edge_set_some_negative_weights)
{
    vector<Edge> inputEdges{
            {0, 1, -1},         // changed this edge.
            {0, 2, 4},
            {1, 2, 3},
            {1, 3, 2},
            {1, 4, 2},
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, -3}          // changed this edge.
    };
    
    EdgeSetBuilder testESB(inputEdges);
    
    auto outputEdgeSet = testESB.getEdgeSet();
    auto outputEdgeCount = testESB.getEdgeCount();
    auto outputGraphDirected = testESB.isGraphDirected();
    auto outputNegativeEdgesAllowed = testESB.areNegativeEdgesAllowed();
    auto outputSelfLoopsAllowed = testESB.areSelfLoopsAllowed();
    
    EXPECT_FALSE(outputEdgeSet.empty());
    EXPECT_EQ(outputEdgeCount, inputEdges.size());
    EXPECT_TRUE(outputGraphDirected);
    EXPECT_TRUE(outputNegativeEdgesAllowed);
    EXPECT_FALSE(outputSelfLoopsAllowed);
}

TEST(EdgeSetBuilder_class, constructor_edge_set_self_loop)
{
    vector<Edge> inputEdges{
            {0, 1, -1},
            {0, 2, 4},
            {1, 2, 3},
            {1, 3, 2},
            {1, 1, 2},          // changed this edge.
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, -3}
    };
    
    EdgeSetBuilder testESB(inputEdges);
    
    auto outputEdgeSet = testESB.getEdgeSet();
    auto outputEdgeCount = testESB.getEdgeCount();
    auto outputGraphDirected = testESB.isGraphDirected();
    auto outputNegativeEdgesAllowed = testESB.areNegativeEdgesAllowed();
    auto outputSelfLoopsAllowed = testESB.areSelfLoopsAllowed();
    
    EXPECT_FALSE(outputEdgeSet.empty());
    EXPECT_EQ(outputEdgeCount, inputEdges.size());
    EXPECT_TRUE(outputGraphDirected);
    EXPECT_TRUE(outputNegativeEdgesAllowed);
    EXPECT_TRUE(outputSelfLoopsAllowed);
}

TEST(EdgeSetBuilder_class, constructor_copy_constructor)
{
    vector<Edge> inputEdges{
            {0, 1, -1},
            {0, 2, 4},
            {1, 2, 3},
            {1, 3, 2},
            {1, 1, 2},          // changed this edge.
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, -3}
    };
    
    EdgeSetBuilder testESB(inputEdges);
    
    auto outputEdgeSet = testESB.getEdgeSet();
    auto outputEdgeCount = testESB.getEdgeCount();
    auto outputGraphDirected = testESB.isGraphDirected();
    auto outputNegativeEdgesAllowed = testESB.areNegativeEdgesAllowed();
    auto outputSelfLoopsAllowed = testESB.areSelfLoopsAllowed();
    
    EXPECT_FALSE(outputEdgeSet.empty());
    EXPECT_EQ(outputEdgeCount, inputEdges.size());
    EXPECT_TRUE(outputGraphDirected);
    EXPECT_TRUE(outputNegativeEdgesAllowed);
    EXPECT_TRUE(outputSelfLoopsAllowed);
    
    EdgeSetBuilder copyESB(testESB);
    
    auto copyEdgeSet = copyESB.getEdgeSet();
    auto copyEdgeCount = copyESB.getEdgeCount();
    auto copyGraphDirected = testESB.isGraphDirected();
    auto copyNegEdgesAllowed = copyESB.areNegativeEdgesAllowed();
    auto copySelfLoopsAllowed = copyESB.areSelfLoopsAllowed();
    
    EXPECT_EQ(copyEdgeSet, outputEdgeSet);
    EXPECT_EQ(copyEdgeCount, outputEdgeCount);
    EXPECT_EQ(copyGraphDirected, outputGraphDirected);
    EXPECT_EQ(copyNegEdgesAllowed, outputNegativeEdgesAllowed);
    EXPECT_EQ(copySelfLoopsAllowed, outputSelfLoopsAllowed);
}

TEST(EdgeSetBuilder_class, create_and_append_edges)
{
    vector<Edge> inputEdges{
            {0, 1, -1},
            {0, 2, 4},
            {1, 2, 3},
            {1, 3, 2},
            {1, 4, 2},
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, -3}
    };
    
    EdgeSetBuilder testESB(true, true, false);
    
    auto inputEdgeIter = inputEdges.begin();
    auto inputEdgesEnd = inputEdges.end();
    
    while (inputEdgeIter != inputEdgesEnd)
    {
        testESB.createAndAppendEdge(inputEdgeIter->source,
                                    inputEdgeIter->destination,
                                    inputEdgeIter->weight);
        
        ++inputEdgeIter;
    }
    
    auto outputEdgeSet = testESB.getEdgeSet();
    auto outputEdgeCount = testESB.getEdgeCount();
    auto outputGraphDirected = testESB.isGraphDirected();
    auto outputNegativeEdgesAllowed = testESB.areNegativeEdgesAllowed();
    auto outputSelfLoopsAllowed = testESB.areSelfLoopsAllowed();
    
    EXPECT_FALSE(outputEdgeSet.empty());
    EXPECT_EQ(outputEdgeCount, inputEdges.size());
    EXPECT_TRUE(outputGraphDirected);
    EXPECT_TRUE(outputNegativeEdgesAllowed);
    EXPECT_FALSE(outputSelfLoopsAllowed);
    
    auto outputEdgeIter = outputEdgeSet.begin();
    auto outputEdgesEnd = outputEdgeSet.end();
    
    inputEdgeIter = inputEdges.begin();
    
    while (outputEdgeIter != outputEdgesEnd &&
           inputEdgeIter != inputEdgesEnd)
    {
        EXPECT_EQ(outputEdgeIter->source, inputEdgeIter->source);
        EXPECT_EQ(outputEdgeIter->destination, inputEdgeIter->destination);
        EXPECT_EQ(outputEdgeIter->weight, inputEdgeIter->weight);
        
        ++inputEdgeIter;
        ++outputEdgeIter;
    }
}

TEST(EdgeSetBuilder_class, create_and_append_edges_default_weights_only)
{
    vector<Edge> inputEdges{
            {0, 1, -1},
            {0, 2, 4},
            {1, 2, 3},
            {1, 3, 2},
            {1, 4, 2},
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, -3}
    };
    
    EdgeSetBuilder testESB(true, true, false);
    
    auto inputEdgeIter = inputEdges.begin();
    auto inputEdgesEnd = inputEdges.end();
    
    while (inputEdgeIter != inputEdgesEnd)
    {
        testESB.createAndAppendEdge(inputEdgeIter->source,
                                    inputEdgeIter->destination);
        
        ++inputEdgeIter;
    }
    
    auto outputEdgeSet = testESB.getEdgeSet();
    auto outputEdgeCount = testESB.getEdgeCount();
    auto outputGraphDirected = testESB.isGraphDirected();
    auto outputNegativeEdgesAllowed = testESB.areNegativeEdgesAllowed();
    auto outputSelfLoopsAllowed = testESB.areSelfLoopsAllowed();
    
    EXPECT_FALSE(outputEdgeSet.empty());
    EXPECT_EQ(outputEdgeCount, inputEdges.size());
    EXPECT_TRUE(outputGraphDirected);
    EXPECT_TRUE(outputNegativeEdgesAllowed);
    EXPECT_FALSE(outputSelfLoopsAllowed);
    
    auto outputEdgeIter = outputEdgeSet.begin();
    auto outputEdgesEnd = outputEdgeSet.end();
    
    inputEdgeIter = inputEdges.begin();
    
    while (outputEdgeIter != outputEdgesEnd &&
           inputEdgeIter != inputEdgesEnd)
    {
        EXPECT_EQ(outputEdgeIter->source, inputEdgeIter->source);
        EXPECT_EQ(outputEdgeIter->destination, inputEdgeIter->destination);
        EXPECT_EQ(outputEdgeIter->weight, 1.00);
        
        ++inputEdgeIter;
        ++outputEdgeIter;
    }
}

//TEST(EdgeSetBuilder_class, read_edges_from_input_file_that_cannot_be_opened)
//{
//    EdgeSetBuilder testESB;
//
//    string fileThatDoesNotExist("nonExistentFile.txt");
//    testESB.readEdgesFromFile(fileThatDoesNotExist);
//
//    auto outputEdgeSet = testESB.getEdgeSet();
//    auto outputEdgeCount = testESB.getEdgeCount();
//    auto outputGraphDirected = testESB.isGraphDirected();
//    auto outputNegativeEdgesAllowed = testESB.areNegativeEdgesAllowed();
//    auto outputSelfLoopsAllowed = testESB.areSelfLoopsAllowed();
//
//    EXPECT_TRUE(outputEdgeSet.empty());
//    EXPECT_EQ(outputEdgeCount, 0);
//    EXPECT_TRUE(outputGraphDirected);
//    EXPECT_FALSE(outputNegativeEdgesAllowed);
//    EXPECT_FALSE(outputSelfLoopsAllowed);
//}
//
//TEST(EdgeSetBuilder_class, read_edges_from_input_file_first_8_edges)
//{
//    EdgeSetBuilder testESB;
//
//    string fileName("/home/carpenter/software/cpp/graphs/search/dijkstras_alg/input1.txt");
//
//    testESB.readEdgesFromFile(fileName);
//    auto outputEdgeSet = testESB.getEdgeSet();
//    auto outputGraphDirected = testESB.isGraphDirected();
//    auto outputNegativeEdgesAllowed = testESB.areNegativeEdgesAllowed();
//    auto outputSelfLoopsAllowed = testESB.areSelfLoopsAllowed();
//
//    EXPECT_TRUE(outputGraphDirected);
//    EXPECT_FALSE(outputNegativeEdgesAllowed);
//    EXPECT_FALSE(outputSelfLoopsAllowed);
//
//    auto outputEdgeIter = outputEdgeSet.begin();
//
//    EXPECT_EQ(outputEdgeIter->source, 1);
//    EXPECT_EQ(outputEdgeIter->destination, 2);
//    EXPECT_EQ(outputEdgeIter->weight, 1.000000);
//
//    ++outputEdgeIter;
//    EXPECT_EQ(outputEdgeIter->source, 1);
//    EXPECT_EQ(outputEdgeIter->destination, 12);
//    EXPECT_EQ(outputEdgeIter->weight, 1.000000);
//
//    ++outputEdgeIter;
//    EXPECT_EQ(outputEdgeIter->source, 2);
//    EXPECT_EQ(outputEdgeIter->destination, 1);
//    EXPECT_EQ(outputEdgeIter->weight, 1.000000);
//
//    ++outputEdgeIter;
//    EXPECT_EQ(outputEdgeIter->source, 2);
//    EXPECT_EQ(outputEdgeIter->destination, 3);
//    EXPECT_EQ(outputEdgeIter->weight, 1.000000);
//
//    ++outputEdgeIter;
//    EXPECT_EQ(outputEdgeIter->source, 2);
//    EXPECT_EQ(outputEdgeIter->destination, 13);
//    EXPECT_EQ(outputEdgeIter->weight, 1.000000);
//
//    ++outputEdgeIter;
//    EXPECT_EQ(outputEdgeIter->source, 3);
//    EXPECT_EQ(outputEdgeIter->destination, 2);
//    EXPECT_EQ(outputEdgeIter->weight, 1.000000);
//
//    ++outputEdgeIter;
//    EXPECT_EQ(outputEdgeIter->source, 3);
//    EXPECT_EQ(outputEdgeIter->destination, 4);
//    EXPECT_EQ(outputEdgeIter->weight, 1.000000);
//
//    ++outputEdgeIter;
//    EXPECT_EQ(outputEdgeIter->source, 3);
//    EXPECT_EQ(outputEdgeIter->destination, 14);
//    EXPECT_EQ(outputEdgeIter->weight, 1.000000);
//}

TEST(EdgeSetBuilder_class, create_and_append_undirected_edges)
{
    vector<Edge> inputEdges{
            {0, 1, -1},
            {0, 2, 4},
            {1, 2, 3},
            {1, 3, 2},
            {1, 4, 2},
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, -3}
    };
    
    vector<Edge> testEdges{
            {0, 1, -1},
            {1, 0, -1},
            {0, 2, 4},
            {2, 0, 4},
            {1, 2, 3},
            {2, 1, 3},
            {1, 3, 2},
            {3, 1, 2},
            {1, 4, 2},
            {4, 1, 2},
            {3, 1, 1},
            {1, 3, 1},
            {3, 2, 5},
            {2, 3, 5},
            {4, 3, -3},
            {3, 4, -3}
    };
    
    EdgeSetBuilder testESB(false, true, false);
    
    auto inputEdgeIter = inputEdges.begin();
    auto inputEdgesEnd = inputEdges.end();
    
    while (inputEdgeIter != inputEdgesEnd)
    {
        testESB.createAndAppendEdge(inputEdgeIter->source,
                                    inputEdgeIter->destination,
                                    inputEdgeIter->weight);
        
        ++inputEdgeIter;
    }
    
    auto outputEdgeSet = testESB.getEdgeSet();
    auto outputEdgeCount = testESB.getEdgeCount();
    auto outputGraphDirected = testESB.isGraphDirected();
    auto outputNegativeEdgesAllowed = testESB.areNegativeEdgesAllowed();
    auto outputSelfLoopsAllowed = testESB.areSelfLoopsAllowed();
    
    EXPECT_FALSE(outputEdgeSet.empty());
    EXPECT_EQ(outputEdgeCount, 2 * inputEdges.size());
    EXPECT_FALSE(outputGraphDirected);
    EXPECT_TRUE(outputNegativeEdgesAllowed);
    EXPECT_FALSE(outputSelfLoopsAllowed);
    
    auto outputEdgeIter = outputEdgeSet.begin();
    auto outputEdgesEnd = outputEdgeSet.end();
    
    auto testEdgeIter = testEdges.begin();
    auto testEdgesEnd = testEdges.end();
    
    while (outputEdgeIter != outputEdgesEnd &&
           testEdgeIter != testEdgesEnd)
    {
        EXPECT_EQ(outputEdgeIter->source, testEdgeIter->source);
        EXPECT_EQ(outputEdgeIter->destination, testEdgeIter->destination);
        EXPECT_EQ(outputEdgeIter->weight, testEdgeIter->weight);
        
        ++testEdgeIter;
        ++outputEdgeIter;
    }
}

TEST(EdgeSetBuilder_class, constructor_undirected_edge_set)
{
    vector<Edge> inputEdges{
            {0, 1, -1},
            {0, 2, 4},
            {1, 2, 3},
            {1, 3, 2},
            {1, 4, 2},
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, -3}
    };
    
    vector<Edge> testEdges{
            {0, 1, -1},
            {1, 0, -1},
            {0, 2, 4},
            {2, 0, 4},
            {1, 2, 3},
            {2, 1, 3},
            {1, 3, 2},
            {3, 1, 2},
            {1, 4, 2},
            {4, 1, 2},
            {3, 1, 1},
            {1, 3, 1},
            {3, 2, 5},
            {2, 3, 5},
            {4, 3, -3},
            {3, 4, -3}
    };
    
    EdgeSetBuilder testESB(inputEdges, false);
    
    //    auto inputEdgeIter = inputEdges.begin();
    //    auto inputEdgesEnd = inputEdges.end();
    //
    //    while (inputEdgeIter != inputEdgesEnd)
    //    {
    //        testESB.createAndAppendEdge(inputEdgeIter->source,
    //                                    inputEdgeIter->destination,
    //                                    inputEdgeIter->weight);
    //
    //        ++inputEdgeIter;
    //    }
    
    auto outputEdgeSet = testESB.getEdgeSet();
    auto outputEdgeCount = testESB.getEdgeCount();
    auto outputGraphDirected = testESB.isGraphDirected();
    auto outputNegativeEdgesAllowed = testESB.areNegativeEdgesAllowed();
    auto outputSelfLoopsAllowed = testESB.areSelfLoopsAllowed();
    
    EXPECT_FALSE(outputEdgeSet.empty());
    EXPECT_EQ(outputEdgeCount, 2 * inputEdges.size());
    EXPECT_FALSE(outputGraphDirected);
    EXPECT_TRUE(outputNegativeEdgesAllowed);
    EXPECT_FALSE(outputSelfLoopsAllowed);
    
    auto outputEdgeIter = outputEdgeSet.begin();
    auto outputEdgesEnd = outputEdgeSet.end();
    
    auto testEdgeIter = testEdges.begin();
    auto testEdgesEnd = testEdges.end();
    
    while (outputEdgeIter != outputEdgesEnd &&
           testEdgeIter != testEdgesEnd)
    {
        EXPECT_EQ(outputEdgeIter->source, testEdgeIter->source);
        EXPECT_EQ(outputEdgeIter->destination, testEdgeIter->destination);
        EXPECT_EQ(outputEdgeIter->weight, testEdgeIter->weight);
        
        ++testEdgeIter;
        ++outputEdgeIter;
    }
}
























