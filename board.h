/* 
 * File:   board.h
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * prototype of board class
 * 04/04/2015
 */

#ifndef BOARD_H
#define	BOARD_H

#include "utilities.h"
#include "cost.h"
#include "node.h"

struct node;

/*******************************************
 *  B O A R D
 *     class prototyping
 *******************************************/
class board
{
private:
    uint dimension;     //the dim(row) = dim(col) square
    uint col;           //empty (0) tile location (col)
    uint row;           //empty (0) tile location (row)
    Table<uint> tiles; //state of board
    cost distance;      //"distance" cost towards the goal
public:
    //constructors
    board() : dimension(0), col(0), row(0) { }
    board(const vector<uint>& seed);
    board(const Table<uint>& seed);
    board(const board *seed);
    ~board();
    //operators
    bool operator==(const board& A) const;
    bool operator!=(const board& A) const;
    bool operator==(const board *A) const;
    bool operator!=(const board *A) const;
    board& operator=(const board& A);
    board *operator=(const board *A);
    const vector<uint>& operator[](const uint x_idx) const;
    //generate the successor nodes
    list<const node *> successors(const node *previous,
                                  const Table<uint>& goal_board) const;
    // moves in board space
    const node *left(const node *previous,
                     const Table<uint>& goal_board) const;
    const node *right(const node *previous,
                      const Table<uint>& goal_board) const;
    const node *up(const node *previous,
                   const Table<uint>& goal_board) const;
    const node *down(const node *previous,
                     const Table<uint>& goal_board) const;
    //mutators
    int move_left();
    int move_right();
    int move_up();
    int move_down();
    //reference information
    vect_iter cbegin();
    vect_iter cend();
    uint get_depth() const;
    uint get_cost() const;
    uint size() const;
    uint index() const;
    // for ease of view in debugging
    friend ostream& operator<< (ostream &out,const board& cBoard);
    friend ostream& operator<< (ostream &out,const board *cBoard);
};

uint64 keygen(const board *valBoard);

#endif	/* BOARD_H */

