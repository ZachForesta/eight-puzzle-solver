/* 
 * File:   solve.h
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * prototype of solution and solve classes
 * 04/04/2015
 */

#ifndef SOLVE_H
#define	SOLVE_H

#include <QWidget>
#include <QTimer>
#include "utilities.h"
#include "pqueue.h"
#include "node.h"
typedef unsigned int uint;

/*******************************************
 *  S O L U T I O N
 *     class prototyping
 *******************************************/

class solution
{
private:
    const board  *start;     //starting state
    const board  *goal;      //goal state to be achieved
    PQueue *open;            //priority queue of potential states
    std::list<const node *> *closed;    //set of visited states
    list<const node *> *path;      //list of path taken toward solution
    Table<uint> goal_cost;  //goal cost vector for use in cost calculation
public:
    list<const node *> *play;      //path in order
    solution(const board& begin, const board& end);
    ~solution();
    bool search();                        //A* iterative BFS search algorithm
    void rebuild();                       //reconstruct path taken
    ostream& print(ostream& out) const;   //print path taken
    void cost_function();                 //build the goal_cost vector
    friend ostream& operator<< (ostream &out, const solution& Solved);
};



class Solve : public QWidget
{
    Q_OBJECT
public:
    Solve()
    : solve(nullptr), timer(nullptr)
    { };
    ~Solve() { 
        delete solve;
        delete timer;
    }
    void updateSolution(const solution *sol);
signals:
    void timedout();
public slots:
    void play();
    void accept();
    void move();
    void reject();
private:
    list<const node *> *solve;
    QTimer *timer;
    bool time_out;
};




#endif	/* SOLVE_H */

