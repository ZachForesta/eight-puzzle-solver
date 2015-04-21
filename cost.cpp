/* 
 * File:   cost.cpp
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * definitions for cost class
 * 04/04/2015
 */

#include "utilities.h"
#include "board.h"
#include "cost.h"


/* *****************************************
 *  C O S T :                              *
 *  C L A S S - methods                    *
 * contains the heuristic for A* algorithm *
 * as well as method for calculation       *
 * and retrieval                           *
 ******************************************/
/* *****************************************
 *  O P E R A T O R S                      *
 ******************************************/
// assignment
cost& cost::operator =(const cost& newCost)
{
    if (*this != newCost) {
        depth = newCost.depth;
        heuristic = newCost.heuristic;
    }
    return *this;
}
// equal to
bool cost::operator == (const cost& compCost)
{
    return ((depth == compCost.depth) && 
            (heuristic == compCost.heuristic));
}
// not equal
bool cost::operator != (const cost& compCost)
{
    return !(*this == compCost);
}
/* *****************************************
 *  C O N S T R U C T O R                  *
 ******************************************/
// using itself
cost::cost(const cost& newCost)
{
    depth = newCost.depth;
    heuristic = newCost.heuristic;
}
/* *****************************************
 *  D E S T R U C T O R                    *
 ******************************************/
cost::~cost()
{
    depth = 0;
    heuristic = 0;
}
/* *****************************************
 *   M E T H O D   D E F I N I T I O N S   *
 ******************************************/

/* *****************************************
 *  get_depth ( )                          *
 * return number of steps to reach         *
 * current state                           *
 ******************************************/
uint cost::get_depth() const
{
    return depth;
}
/* *****************************************
 *  get_cost ( )                           *
 * return number of steps to reach         *
 * current state + current heuristic value *
 ******************************************/
uint cost::get_cost() const
{
    return depth + heuristic;
}

/* *****************************************
 *  calculate ( )                          *
 *  -> Input: current board and goal Cost  *
 *  calculate the cost based on:           *
 * 1) Number of tiles misplaced            *
 * 2) cumulative distance of tiles from    *
 *    their goal position (Manhattan dist) *
 ******************************************/
void cost::calculate(const board& newBoard, const Table<uint>& goalBoard)
{   
    uint dim = newBoard.size();
    //heuristic 1 -> out of place
    uint misplaced = 0;
    //heuristic 2 -> Manhattan block distance
    uint manhattan = 0;
    for (uint j = 0; j < dim; ++j) { //row
        for (uint i = 0; i < dim; ++i) { //col
            if (newBoard[j][i] != goalBoard[j][i]) {
                ++misplaced;
                uint coordy = newBoard[j][i] / dim;
                uint coordx = newBoard[j][i] % dim;
                uint goal_y = goalBoard[coordy][coordx] / dim;
                uint goal_x = goalBoard[coordy][coordx] % dim;
                manhattan += abs(goal_y - j) + abs(goal_x - i);
            }
        }
    }
    ++depth;
    heuristic = misplaced + manhattan;
}
