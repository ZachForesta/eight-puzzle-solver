/* 
 * File:   pqueue.h
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * prototype of priority queue class
 * 04/04/2015
 */

#ifndef PQUEUE_H
#define	PQUEUE_H

#include "utilities.h"
#include "node.h"

/*******************************************
 *  P Q U E U E
 *     class prototyping
 *******************************************/
class PQueue {
private:
    node *head;
public:
    PQueue() : head(nullptr) { }
    PQueue(const uint& Pri, const board *Init);
    ~PQueue();
    node *front();
    bool empty();
    void push(uint slot,const board *new_ref,const node *previous);
    void push_back(const board *back_ref);
    void push_front(const board *front_ref);
    void remove(node *rmNode);
    const board *pop_back();
    void exchange(node *child, node *descendant);
};

#endif	/* PQUEUE_H */

