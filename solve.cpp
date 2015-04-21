/* 
 * File:   solve.cpp
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * Definitions of solve and solution classes
 * 04/04/2015
 */

#include "utilities.h"
#include "solve.h"
#include "puzzle.h"
#include <QTimer>

extern Puzzle *puzzle;
/* *****************************************
 *  S O L V E :                            *
 *  C L A S S                              *
 ******************************************/

/* *****************************************
 *   M E T H O D   D E F I N I T I O N S   *
 ******************************************/

/* *****************************************
 *  updateSolution (solution)              *
 *  storage of puzzle solution             *
 *  moves for playback                     *
 *  assignment operator                    *
 ******************************************/
void Solve::updateSolution(const solution *sol)
{
    delete solve;
    solve = new list<const node *>;
    for (auto iter = sol->play->cbegin();
            iter != sol->play->cend(); ++iter) {
        solve->push_front(*iter);
    }
}

/* *****************************************
 *  accept ( )                             *
 *  action taken when solve button         *
 *  pressed. Runs solve routine with       *
 *  current board.                         *
 ******************************************/
void Solve::accept()
{
    vector<uint> bg = vector<uint>(puzzle->matrix->getOrder(),
                             puzzle->matrix->getOrder() + 9);
    vector<uint> end = vector<uint>{1,2,3,4,5,6,7,8,0};
    solution *solver = new solution(bg, end);
    if(solver->search())  { // show solution
        cout << *solver;
        updateSolution(solver);
    }
}

/* *****************************************
 *  reject ()                              *
 *  action taken when quit button          *
 *  pressed.                               *
 ******************************************/
void Solve::reject()
{
    std::exit(0);
}

/* *****************************************
 *  play ()                                *
 *  action taken when play button          *
 *  pressed. Begin playback of solution,   *
 *  if one exists.                         *
 ******************************************/
void Solve::play() {
    if (solve != nullptr &&
        solve->empty() == false &&
        timer == nullptr) {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(move()));
        timer->start(1000); //wait 1 sec between moves
        time_out = false;
    } else {
        if (solve == nullptr ||
            solve->empty())
            emit timedout();
    }
}
/* *****************************************
 *  move ()                                *
 *  action taken after play button         *
 *  pressed. move the tiles in sequence    *
 *  they were solved.                      *
 ******************************************/
void Solve::move()
{
    if (solve == nullptr ||
        solve->empty()) {
        puzzle->msg->setFont(QFont("times",16));
        puzzle->msg->setPlainText(QString("Solution Finished\n"));
        delete timer;
        timer = nullptr;
        emit timedout();
        return;
    }
    int dir;
    Cell *cell = nullptr;

    const node *playNode = solve->front();
    solve->pop_front();
    if (playNode->direction == Qt::Key_Up) {
        dir = Qt::Key_Down;
    }
    else if (playNode->direction == Qt::Key_Down) {
        dir = Qt::Key_Up;
    }
    else if (playNode->direction == Qt::Key_Right) {
        dir = Qt::Key_Left;
    }
    else if (playNode->direction == Qt::Key_Left) {
        dir = Qt::Key_Right;
    }
    else {
        return;
    }
    //search for tile
    for (int i = 0; i < puzzle->matrix->size(); ++i) {
        if( ((*(puzzle->matrix))[i])->getNumber() == playNode->tile) {
            cell = (*(puzzle->matrix))[i];
            break;
        }
    }
    //simulate move!
    QKeyEvent *keyevent = new QKeyEvent(QEvent::KeyPress, dir, 0);
    cell->keyPressEvent(keyevent);

    delete keyevent;

    if (cell->isValid() == false) {//abort solution play if tampered
        while (solve->empty() == false) {
            solve->pop_back();
        }
        delete timer;
        timer = nullptr;
        emit timedout();
    }
}

/* *****************************************
 *  S O L U T I O N :                      *
 *  C L A S S - methods                    *
 * Object defines A* algorithm             *
 * given a start and goal state board      *
 * return the optimal path/plan to reach   *
 * the goal.                               *
 * iterative BFS                           * 
 ******************************************/
/* *****************************************
 *  C O N S T R U C T O R S                *
 ******************************************/
solution::solution(const board& begin, const board& end)
{
    start = new board(begin);
    goal  = new board(end);
    open  = new PQueue;                    //priority queue of potential states
    closed= new list<const node *>;       //set of visited states
    path  = new list<const node *>;       //list of path taken toward solution
    play  = new list<const node *>;
    cost_function();                      //determine goal cost vector
}

/* *****************************************
 *  D E S T R U C T O R                    *
 ******************************************/
solution::~solution()
{
    delete start;
    delete goal;
    delete open;
    delete closed;
    delete path;
    delete play;
}
/* *****************************************
 *   M E T H O D   D E F I N I T I O N S   *
 ******************************************/

/* *****************************************
 *  cost_function ( )                      *
 *  build goal cost based on goal state    *
 *  goal cost vector is a map of where     *
 *  tile number is by index                *
 ******************************************/
void solution::cost_function()
{
    if (goal == nullptr)
        return;
    
    uint dim = goal->size();
    //sizing
    goal_cost.resize(dim);
    for (uint i = 0; i < dim; ++i)
        goal_cost[i].resize(dim);
    //create goal cost
    for (uint j = 0; j < dim; ++j) {
        for (uint i = 0; i < dim; ++i) {
            uint coordy = (*goal)[j][i] / dim;
            uint coordx = (*goal)[j][i] % dim;
            goal_cost[coordy][coordx] = (j * dim) + i;
        }
    }
}
/* *****************************************
 *  rebuild ( )                            *
 *  end state and trace back the steps     *
 *  taken to build the path/plan           *
 ******************************************/
void solution::rebuild()
{
    const node *end_state = closed->front();
    while (end_state != nullptr) {
        path->push_front(end_state);
        end_state = end_state->previous;
    }
}
/* *****************************************
 *  print ( )                              *
 *  print out path/plan for humans to see  *
 ******************************************/
ostream& solution::print(ostream& out) const
{
    uint opt_steps = 0;
    uint tile;
    QString stepsTaken;
    string direction;
    while(path->empty() == false) {
        ++opt_steps;
        const node *printNode= path->front();
        play->push_front(printNode);
        path->pop_front();
      
//        out << printNode->state << endl;
        tile = printNode->tile;//puzzle->matrix->getNumber(idx);
        if (printNode->direction == Qt::Key_Up) {
            direction = "Down";
        }
        else if (printNode->direction == Qt::Key_Down) {
            direction = "Up";
        }
        else if (printNode->direction == Qt::Key_Right) {
            direction = "Left";
        }
        else if (printNode->direction == Qt::Key_Left) {
            direction = "Right";
        }
        else {
            continue;
        }
        stepsTaken += QString::number(opt_steps - 1) + QString(": ") +
                      QString::number(tile);
        stepsTaken += QString(" ") + QString(direction.c_str()) + QString("\n");
        
    }
    puzzle->msg->setFont(QFont("times",12));
    puzzle->msg->setPlainText(QString("Optimal Solution took:") + 
                              QString::number(opt_steps - 1) +
                              QString(" steps!\n") + stepsTaken);
    return out;
}

/* *****************************************
 *  search ( )                             *
 *  iterative BFS A* Algorithm for finding *
 *  optimal (shortest) solution from       *
 *  initial to end state                   *
 ******************************************/
bool solution::search()
{
    if(start == nullptr ||
       goal  == nullptr ||
       *start == *goal)
        return false;
    // Hash table of visited states and cost per state
    Hash<uint, uint, Predicate<uint>> costHash;
     
    // To start push node onto queue.
    open->push_front(start);

    while (open->empty() == false) {
        //pop off the current min
        node *current = open->front();
        //add current node to list of visited for tracking
        closed->push_front(current);
        if (*(current->state) == goal) {
            rebuild();
            return true;
        }
        list<const node *> neighbors =
                                current->state->successors(current, goal_cost);
        //Inspect current neighbors
        for (list<const node *>::const_iterator iter = neighbors.cbegin()
                ;iter != neighbors.cend()
                ;++iter) {
            const node *candidate = (*iter);
            //neighbor is valid
            if (candidate != nullptr) {
                const board *next = candidate->state;
                bool repeat = false;
                const uint64 key = keygen(next);
                uint prev_cost = 0;
                //check for duplicated states in hash
                if (costHash.empty() == false) {
                    Hash<uint, uint, Predicate<uint>>::iterator visited;
                    visited = costHash.find(key);
                    // state found
                    if (visited != costHash.cend()) {
                       prev_cost = visited->second;
                       repeat = true;
                    }
                }
                //next state is unique or "cheaper"
                if ((repeat == false) || (prev_cost > next->get_cost())) {
                    
                    // replace previous state with cheaper one
                    if (repeat == true) {
                        costHash.erase (key);
                    }
                    // insert new or cheaper state into hash
                    costHash.insert((pair <uint, uint>(key, next->get_cost())));
                    // push next state into queue based on it's cost.
                    open->push(next->get_cost(), next, candidate);
                }
            }
        }
        
    }
//    cout << "No solution was found!" << endl;
    return false;
}

ostream& operator<< (ostream &out,const solution& Solved)
{
    return Solved.print(out);
}