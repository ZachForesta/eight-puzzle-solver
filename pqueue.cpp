/* 
 * File:   pqueue.cpp
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * definitions for priority queue class
 * 04/04/2015
 */

#include "utilities.h"
#include "pqueue.h"
#include "board.h"
#include "node.h"


/* *****************************************
 *  P Q U E U E                            *
 *  C L A S S - methods                    *
 * priority queue based on a binary search *
 * tree w/ non-unique priorities allowed.  *
 ******************************************/
/* *****************************************
 *  C O N S T R U C T O R                  *
 ******************************************/
PQueue::PQueue(const uint& Pri, const board *Init)
{
    head = new node(Pri, Init);
}
/* *****************************************
 *  D E S T R U C T O R                    *
 ******************************************/
PQueue::~PQueue()
{
    if (empty()) return;
    list<node *> stack;
    node *current  = head;
    bool done = false;
    
    while (done != true) {
        if (current != nullptr) {
            stack.push_back(current);
            current = current->left;
        } else {
            if (stack.empty()) {
                head = nullptr;
                done = true;
            } else {
                current = stack.back();
                node *delNode = current;
                stack.pop_back();
                current = current->right;
                delete delNode;
                delNode = nullptr;
            }
        }
    }
    
}
/* *****************************************
 *   M E T H O D   D E F I N I T I O N S   *
 ******************************************/

/* *****************************************
 *  empty ( )                              *
 * return true if queue is empty           *
 ******************************************/
bool PQueue::empty() {
    return head == nullptr;
}
/* *****************************************
 *  front ( )                              *
 * push node to front of the queue         *
 ******************************************/
node *PQueue::front() {
    if (empty()) return nullptr;
    node *current = head;
    while (current->left != nullptr) {
        current  = current->left;
    }
    node *front_node = new node(current);
    node *delNode= current;
    // removal of node
    remove(delNode);
    delNode= nullptr;
     
    return front_node;
 }
/* *****************************************
 *  push ( )                               *
 * find position to insert node based on   *
 * priority (slot)                         *
 * keep track of history (previous)        *
 ******************************************/
void PQueue::push(uint slot,const board *new_ref,const node *curr) {
    node *new_node = new node(slot, new_ref);
    new_node->previous = curr->previous;
    new_node->direction = curr->direction;
    new_node->tile = curr->tile;
    if (empty()) {
        head = new_node;
    } else {
        node *current = head;
        node *prev = nullptr;
        while (current != nullptr) {
            prev = current;
            if (slot <= current->priority) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (slot <= prev->priority) {
            prev->left = new_node;
            new_node->parent = prev;
        } else {
            prev->right = new_node;
            new_node->parent = prev;
        }
    }
}
/* *****************************************
 *  push_back ( )                          *
 * make node from board state,             *
 * insert at the back of the queue         *
 ******************************************/
void PQueue::push_back(const board *back_ref) {
    if (empty()) {
        head = new node(back_ref);
    } else {
        node *current = head;
        while (current->right != nullptr) {
            current = current->right;
        }
        current->right = new node(INT_MAX, back_ref);
        current->right->parent = current;
    }
}
/* *****************************************
 *  push_back ( )                          *
 * make node from board state,             *
 * insert at the front of the queue        *
 ******************************************/
void PQueue::push_front(const board *front_ref) {
    if (empty()) {
        head = new node(front_ref);
    } else {
        node *current = head;
        while (current->left != nullptr) {
            current = current->left;
        }
        current->left = new node(0, front_ref);
        current->left->parent = current;
    }
}
/* *****************************************
 *  pop_back ( )                           *
 * get value of board state at             *
 * end of queue and delete                 *
 ******************************************/
const board *PQueue::pop_back() {
    if (empty())
        return nullptr;
    
    node *current = head;
    while (current->right != nullptr) {
        current = current->right;
    }
    board *back_node = new board(current->state);
    node *delNode= current;
    // removal of node
    remove(delNode);

    return back_node;
}

/* *****************************************
 *  exchange ( )                           *
 * replace child node with its             *
 * descendant                              *
 ******************************************/
void PQueue::exchange(node *child, node *descendant)
{
   if (child == nullptr)
       return;
   
   node *parent = child->parent;
   bool heir = (descendant != nullptr);
   
   if (parent == nullptr) {//head
      if (heir) {
        descendant->parent = nullptr;
      }
      head = descendant;
   } else {
      if (child->left_of(parent)) {
          parent->left = descendant;
      } else {
          parent->right= descendant;
      }
      if (heir) {
          descendant->parent = parent;
      }
   }
}

/* *****************************************
 *  remove ( )                             *
 * any node and preserve BST property      *
 * cases:                                  *
 * 1) no children: delete                  *
 * 2) left or right child:                 *
 *    exchange node with its child         *
 *    and delete.                          *
 * 3) both left and right exist            *
 *    replace node with sub tree maximum   *
 *    and delete.                          *
 ******************************************/
void PQueue::remove(node *rmNode)
{
    if (rmNode== nullptr)
        return;
    
    if (rmNode->is_leaf()) { // no sub nodes
        exchange(rmNode, nullptr);
    } else {
        if (rmNode->right == nullptr) { //has only left sub node
            exchange(rmNode, rmNode->left);
        } else if (rmNode->left == nullptr) { //has only right sub node
            exchange(rmNode, rmNode->right);
        } else { //has left and right sub nodes
            node *current = rmNode;
            while (current->right != nullptr) {
                current = current->right;
            }
            
            rmNode->left->parent  = current;
            rmNode->right->parent = current;
            current->parent = rmNode->parent;
            current->left   = rmNode->left;
            current->right  = rmNode->right;
            if (rmNode == head) {
                head = current;
            }
        }
    }
    delete rmNode;
    rmNode= nullptr;
}
