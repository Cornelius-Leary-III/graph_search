//
// Created by carpenter on 2/1/19.
//

#ifndef BFS_ADJACENCYLIST_H
#define BFS_ADJACENCYLIST_H

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Node
{
   string        name;
   vector<Node*> neighbors;
};

class AdjacencyList
{
   public:
   AdjacencyList();
   ~AdjacencyList() = default;

   private:
   //    vector<vector<
};

#endif // BFS_ADJACENCYLIST_H
