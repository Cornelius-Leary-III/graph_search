//
// Created by carpenter on 1/28/19.
//

#include "BreadthFirstSearchPlanner.h"

BreadthFirstSearchPlanner::BreadthFirstSearchPlanner()
{
    finalPath;
    goalNodesSet;
    goalReached = true;
    startNode = 0;
}

BreadthFirstSearchPlanner::~BreadthFirstSearchPlanner()
{
}

bool BreadthFirstSearchPlanner::hasGoalBeenReached()
{
    return true;
}

vector<int>& BreadthFirstSearchPlanner::recoverFinalPath()
{
    return finalPath;
}

void BreadthFirstSearchPlanner::setStartNode()
{
}

void BreadthFirstSearchPlanner::setGoalNodesSet()
{
}

