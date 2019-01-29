//
// Created by carpenter on 1/28/19.
//

#ifndef BREADTH_FIRST_SEARCH_HOMEMADE_BREADTHFIRSTSEARCHPLANNER_H
#define BREADTH_FIRST_SEARCH_HOMEMADE_BREADTHFIRSTSEARCHPLANNER_H

#include <map>
#include <queue>
#include <vector>
#include <iostream>
#include <sstream>

using std::map;
using std::pair;
using std::make_pair;
using std::queue;
using std::vector;
using std::cout;
using std::endl;
using std::stringstream;


class BreadthFirstSearchPlanner
{
public:
    
    BreadthFirstSearchPlanner();
    
    ~BreadthFirstSearchPlanner();

    void setStartNode();
    
    void setGoalNodesSet();

    bool hasGoalBeenReached();
    
    vector<int>& recoverFinalPath();
    
    
    
private:

    int startNode;
    vector<int> goalNodesSet;
    bool goalReached;
    vector<int> finalPath;
    
    

};


#endif //BREADTH_FIRST_SEARCH_HOMEMADE_BREADTHFIRSTSEARCHPLANNER_H
