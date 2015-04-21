/* 
 * File:   node.cpp
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * definitions for node structure
 * 04/04/2015
 */

#include "utilities.h"
#include "node.h"


/* *****************************************
 *  N O D E                                *
 *  S T R U C T - methods                  *
 *  basis element for queue used in A*     *
 *  search.                                *
 *  consists of binary search tree (BST)   *
 *  structure.                             *
 ******************************************/
/* *****************************************
 *  C O N S T R U C T O R S                *
 ******************************************/
// default
node::node() : parent(nullptr), left(nullptr),
               right(nullptr), previous(nullptr),
               state(nullptr), priority(0), direction(0), tile(0) 
{
}
// using board class
node::node(const board *init) : parent(nullptr), left(nullptr),
                          right(nullptr), previous(nullptr),
                          state(init), priority(0), direction(0), tile(0) 

{
}
// using priority and board
node::node(const uint& pri, const board *init) : parent(nullptr), left(nullptr),
                                    right(nullptr), previous(nullptr),
                                    state(nullptr), priority(0), direction(0), tile(0) 
{
    state = init;
    priority = pri;
}
// using self
node::node(const node *copy) : parent(nullptr), left(nullptr),
                                right(nullptr), previous(nullptr),
                                state(nullptr), priority(0), direction(0), tile(0) 
{
    if (copy != nullptr) {
        parent = copy->parent;
        left   = copy->left;
        right  = copy->right;
        state    = copy->state;
        previous = copy->previous;
        priority = copy->priority;
        direction = copy->direction;
        tile = copy->tile;
    }
}
/* *****************************************
 *  D E C O N S T R U C T O R S            *
 ******************************************/
node::~node() {
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    state = nullptr;
    previous = nullptr;
}
/* *****************************************
 *   M E T H O D   D E F I N I T I O N S   *
 ******************************************/

/* *****************************************
 *  is_leaf ( )                            *
 *  returns true if node has no children   *
 ******************************************/
bool node::is_leaf()
{
    return (left == nullptr) && (right == nullptr);
}
/* *****************************************
 *  left_of ( )                            *
 *  returns true if object node is the     *
 *  left child of a given node.            *
 ******************************************/
bool node::left_of(const node *pNode)
{
    if (pNode == nullptr)
        return false;
    return pNode->left == this;
}
/* *****************************************
 *  right_of ( )                           *
 *  returns true if object node is the     *
 *  right child of a given node.           *
 ******************************************/
bool node::right_of(const node *pNode)
{
    if (pNode == nullptr)
        return false;
    return pNode->right == this;
}
