/* 
 * File:   cost.h
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * prototype of cost class
 * 04/04/2015
 */

#ifndef COST_H
#define	COST_H

#include "utilities.h"

class board;
/*******************************************
 *  C O S T
 *     class prototyping
 *******************************************/
class cost {
private:
    uint depth;   //number of iterations
    uint heuristic;
public:
    cost() : depth(0), heuristic(0) {}
    cost(const cost& newCost);
    ~cost();
    //operators
    cost& operator =(const cost& newCost);
    bool operator == (const cost& compCost);
    bool operator != (const cost& compCost);
    void calculate(const board& newBoard, const Table<uint>& goalBoard);
    uint get_cost() const;
    uint get_depth() const;
};

#endif	/* COST_H */

