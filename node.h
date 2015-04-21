/* 
 * File:   node.h
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * prototype of node structure
 * 04/04/2015
 */

#ifndef NODE_H
#define	NODE_H

#include "utilities.h"
#include "board.h"

/*******************************************
 * N O D E
 *     prototype for use in queue
 *******************************************/
struct node{
    node  *parent;
    node  *left;
    node  *right;
    const node  *previous;
    const board *state;
    uint priority;
    int direction; //direction to move tile
    int tile; //tile to move
    //constructors
    node();
    node(const board *init);
    node(const uint& pri, const board *init);
    node(const node *copy);
    ~node();
    // utility functions
    bool is_leaf();
    bool left_of(const node *pNode);
    bool right_of(const node *pNode);

};

#endif	/* NODE_H */

