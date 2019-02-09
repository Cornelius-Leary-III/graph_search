//
// Created by carpenter on 2/8/19.
//
// https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
//

#include <gtest/gtest.h>
#include "floyd_warshall_alg.h"

void printMatrix(vector<vector<double>>& matrix)
{
    int row = 0;
    while (row < matrix.size())
    {
        int col = 0;
        while (col < matrix[0].size())
        {
            cout << matrix[row][col] << "\t";
            ++col;
        }
        
        cout << endl;
        ++row;
    }
}

TEST(Floyd_Warshall_Shortest_Path_class, constructor_num_nodes)
{
    unsigned long numNodes = 4;
    Floyd_Warshall_Shortest_Path testObj(numNodes);
    
    auto testMatrix = testObj.getMinDistMatrix();
    EXPECT_FALSE(testMatrix.empty());
    EXPECT_FALSE(testMatrix[0].empty());
    
    EXPECT_EQ(testMatrix.size(), numNodes);
    EXPECT_EQ(testMatrix[0].size(), numNodes);
}

TEST(Floyd_Warshall_Shortest_Path_class, add_one_based_edges_and_process_graph)
{
    vector<Edge> inputEdges = {
            {1, 3, -2},
            {2, 1, 4},
            {2, 3, 3},
            {3, 4, 2},
            {4, 2, -1}
    };
    
    unsigned long numNodes = 4;
    Floyd_Warshall_Shortest_Path testObj(4);
    
    EXPECT_NO_THROW(testObj.addEdgesAsSet(inputEdges));
    EXPECT_NO_THROW(testObj.processGraph());
    
    auto testMatrix = testObj.getMinDistMatrix();
    EXPECT_FALSE(testMatrix.empty());
    EXPECT_EQ(testMatrix.size(), numNodes);
    EXPECT_EQ(testMatrix[0].size(), numNodes);
    
    vector<vector<double>> expectedMinDist = {
            {0, -1, -2, 0},
            {4, 0,  2,  4},
            {5, 1,  0,  2},
            {3, -1, 1,  0}
    };
    
    int row = 0;
    while (row < testMatrix.size())
    {
        int col = 0;
        while (col < testMatrix[0].size())
        {
            EXPECT_EQ(testMatrix[row][col], expectedMinDist[row][col]);
            ++col;
        }
        ++row;
    }
}

TEST(Floyd_Warshall_Shortest_Path_class, add_zero_based_edges_and_process_graph)
{
    vector<Edge> inputEdges = {
            {0, 2, -2},
            {1, 0, 4},
            {1, 2, 3},
            {2, 3, 2},
            {3, 1, -1}
    };
    
    unsigned long numNodes = 4;
    Floyd_Warshall_Shortest_Path testObj(4);
    
    EXPECT_NO_THROW(testObj.addEdgesAsSet(inputEdges));
    EXPECT_NO_THROW(testObj.processGraph());
    
    auto testMatrix = testObj.getMinDistMatrix();
    EXPECT_FALSE(testMatrix.empty());
    EXPECT_EQ(testMatrix.size(), numNodes);
    EXPECT_EQ(testMatrix[0].size(), numNodes);
    
    vector<vector<double>> expectedMinDist = {
            {0, -1, -2, 0},
            {4, 0,  2,  4},
            {5, 1,  0,  2},
            {3, -1, 1,  0}
    };
    
    int row = 0;
    while (row < testMatrix.size())
    {
        int col = 0;
        while (col < testMatrix[0].size())
        {
            EXPECT_EQ(testMatrix[row][col], expectedMinDist[row][col]);
            ++col;
        }
        ++row;
    }
}

TEST(Floyd_Warshall_Shortest_Path_class, get_path_through_graph)
{
    vector<Edge> inputEdges = {
            {0, 2, -2},
            {1, 0, 4},
            {1, 2, 3},
            {2, 3, 2},
            {3, 1, -1}
    };
    
    unsigned long numNodes = 4;
    Floyd_Warshall_Shortest_Path testObj(4);
    
    EXPECT_NO_THROW(testObj.addEdgesAsSet(inputEdges));
    EXPECT_NO_THROW(testObj.processGraph());
    
    vector<vector<int>> expectedPaths{
            {},
            {0, 2, 3, 1},
            {0, 2},
            {0, 2, 3},
            
            {1, 0},
            {},
            {1, 0, 2},
            {1, 0, 2, 3},
            
            {2, 3, 1, 0},
            {2, 3, 1},
            {},
            {2, 3},
            
            {3, 1, 0},
            {3, 1},
            {3, 1, 0, 2},
            {}
    };
    
    auto expectedPathIter = expectedPaths.begin();
    
    EXPECT_EQ(testObj.getPathFromFirstToSecond(0, 0), *expectedPathIter);
    EXPECT_EQ(testObj.getPathFromFirstToSecond(0, 1), *(++expectedPathIter));
    EXPECT_EQ(testObj.getPathFromFirstToSecond(0, 2), *(++expectedPathIter));
    EXPECT_EQ(testObj.getPathFromFirstToSecond(0, 3), *(++expectedPathIter));
    
    EXPECT_EQ(testObj.getPathFromFirstToSecond(1, 0), *(++expectedPathIter));
    EXPECT_EQ(testObj.getPathFromFirstToSecond(1, 1), *(++expectedPathIter));
    EXPECT_EQ(testObj.getPathFromFirstToSecond(1, 2), *(++expectedPathIter));
    EXPECT_EQ(testObj.getPathFromFirstToSecond(1, 3), *(++expectedPathIter));
    
    EXPECT_EQ(testObj.getPathFromFirstToSecond(2, 0), *(++expectedPathIter));
    EXPECT_EQ(testObj.getPathFromFirstToSecond(2, 1), *(++expectedPathIter));
    EXPECT_EQ(testObj.getPathFromFirstToSecond(2, 2), *(++expectedPathIter));
    EXPECT_EQ(testObj.getPathFromFirstToSecond(2, 3), *(++expectedPathIter));
    
    EXPECT_EQ(testObj.getPathFromFirstToSecond(3, 0), *(++expectedPathIter));
    EXPECT_EQ(testObj.getPathFromFirstToSecond(3, 1), *(++expectedPathIter));
    EXPECT_EQ(testObj.getPathFromFirstToSecond(3, 2), *(++expectedPathIter));
    EXPECT_EQ(testObj.getPathFromFirstToSecond(3, 3), *(++expectedPathIter));
}

