/* 
 * File:   board.cpp
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * definitions for board class
 * 04/04/2015
 */

#include "utilities.h"
#include "board.h"
#include "node.h"
#include "cost.h"


/* *****************************************
 *  B O A R D :                            *
 *  C L A S S - methods                    *
 * Object defines state of Eight Puzzle    *
 * board. For example:                     *
 * tiles:                                  *
 * |0 | 1 | 2 |                            *
 * |3 | 4 | 5 |                            * 
 * |6 | 7 | 8 |                            * 
 * dimension = 3                           * 
 ******************************************/
/* *****************************************
 *  O P E R A T O R S                      *
 ******************************************/
// dereference operator
const vector<uint>& board::operator[](uint x_idx) const
{
    return tiles[x_idx];
}
// equal to
bool board::operator==(const board&  A) const {
    return (tiles == A.tiles);
}
// not equal to
bool board::operator!=(const board&  A) const {
    return !(*this == A);
}
// equal to for pointer board
bool board::operator==(const board  *A) const {
    if (A == nullptr)
        return false;

    return (tiles == A->tiles);
}
// not equal for pointer board
bool board::operator!=(const board *A) const {
    return !(*this == A);
}
// assignment
board&  board::operator=(const board&  A) {
    if (*this != A) {
        tiles    = A.tiles;
        dimension= A.dimension;
        col      = A.col;
        row      = A.row;
        distance = A.distance;
    }
    return *this;
}
board *board::operator=(const board *A)
{
    if (A == nullptr)
        return nullptr;
    
    if (*this != A) {
        tiles    = A->tiles;
        dimension= A->dimension;
        col      = A->col;
        row      = A->row;
        distance = A->distance;
    }
    return this; 
}
/* *****************************************
 *  C O N S T R U C T O R S                *
 ******************************************/
// using another board
board::board(const board *seed) : dimension(0),
                                  col(0), row(0)
{
    if (seed == nullptr)
        return;
    
    tiles    = seed->tiles;
    dimension= seed->dimension;
    col      = seed->col;
    row      = seed->row;
    distance = cost(seed->distance);
}
// using vector input
board::board(const vector<uint>& seed) {
    dimension = sqrt(seed.size());
    tiles.resize(dimension);
    for (uint i = 0; i < dimension; ++i)
        tiles[i].resize(dimension);
    
    for (uint i = 0; i < dimension; ++i) {
        for (uint j = 0; j < dimension; ++j) {
            tiles[i][j] = seed[(i * dimension) + j];
            if (tiles[i][j] == 0) {
                row = i;
                col = j;
            }
        }
    }
}
// using vector of vector input
board::board(const Table<uint>& seed) {
    dimension = seed.size();
    tiles = seed;
    
    for (uint i = 0; i < dimension; ++i) {
        for (uint j = 0; j < dimension; ++j) {
            if (tiles[i][j] == 0) {
                row = i;
                col = j;
            }
        }
    }
}

/* *****************************************
 *  D E S T R U C T O R                    *
 ******************************************/
board::~board()
{
    // stl classes have native de-constructors
    dimension = 0;
}
/* *****************************************
 *   M E T H O D   D E F I N I T I O N S   *
 ******************************************/

/* *****************************************
 *  successors ( )                         *
 *  -> Input: previous node and goal       *
 *  <- Output: list of next states nodes   *
 ******************************************/
list<const node *> board::successors(const node *previous,
                                     const Table<uint>& goal_board) const
{
    list<const node *> next;

    next.push_back(up(previous, goal_board));
    next.push_back(down(previous, goal_board));
    next.push_back(left(previous, goal_board));
    next.push_back(right(previous, goal_board));
    return next;
}
/* *****************************************
 *  move_left ( )                          *
 *  takes the board and shifts the         *
 *  empty space to the left                *
 ******************************************/
int board::move_left()
{
    int mv_tile = -1;
    if (col > 0) {
        mv_tile = tiles[row][col - 1];
        tiles[row][col] = tiles[row][col - 1];
        tiles[row][col - 1] = 0;
        --col;
    }
    return mv_tile;
}
/* *****************************************
 *  move_right ( )                         *
 *  takes the board and shifts the         *
 *  empty space to the right               *
 ******************************************/
int board::move_right()
{
    int mv_tile = -1;
    if (col < (size() - 1)) {
        mv_tile = tiles[row][col + 1];
        tiles[row][col] = tiles[row][col + 1];
        tiles[row][col + 1] = 0;
        ++col;
    }
    return mv_tile;
}
/* *****************************************
 *  move_up ( )                            *
 *  takes the board and shifts the         *
 *  empty space up a row                   *
 ******************************************/
int board::move_up()
{
    int mv_tile = -1;
    if (row > 0) {
        mv_tile = tiles[row - 1][col];
        tiles[row][col] = tiles[row - 1][col];
        tiles[row - 1][col] = 0;
        --row;
    }
    return mv_tile;
}
/* *****************************************
 *  move_down ( )                          *
 *  takes the board and shifts the         *
 *  empty space up a row                   *
 ******************************************/
int board::move_down()
{
    int mv_tile = -1;
    if (row < (size() - 1)) {
        mv_tile = tiles[row + 1][col];
        tiles[row][col] = tiles[row + 1][col];
        tiles[row + 1][col] = 0;
        ++row;
    }
    return mv_tile;
}
/* *****************************************
 *  left ( )                               *
 *  -> Input: previous node and goal       *
 *  <- Output: next left state node        *
 ******************************************/
const node *board::left(const node *previous,
                        const Table<uint>& goal_board) const
{
    //check for validity of move
    if (col <= 0) 
        return nullptr;
    
    board *newBoard;
    newBoard = new board(this);
    // move empty tile in direction
    int tile = newBoard->move_left();
   // calculate the cost for this new state
    newBoard->distance.calculate(*newBoard, goal_board);
    // create node for queue placement
    node *left_state;
    left_state = new node(newBoard->get_cost(), newBoard);
    // keep track of history
    left_state->previous = previous;
    left_state->direction = (Qt::Key_Left);
    left_state->tile = tile;
    return left_state;
}
/* *****************************************
 *  right ( )                              *
 *  -> Input: previous node and goal       *
 *  <- Output: next right state node       *
 ******************************************/
const node *board::right(const node *previous,
                         const Table<uint>& goal_board) const
{
    //check for validity of move
    if (col >= (size() - 1))
        return nullptr;
    
    board *newBoard;
    newBoard = new board(this);
    // move empty tile in direction
    int tile = newBoard->move_right();
   // calculate the cost for this new state
    newBoard->distance.calculate(*newBoard, goal_board);
    // create node for queue placement
    node *right_state;
    right_state =  new node(newBoard->get_cost(), newBoard);
    // keep track of history
    right_state->previous = previous;
    right_state->direction = (Qt::Key_Right);
    right_state->tile = tile;
    return right_state;    
}
/* *****************************************
 *  up ( )                                 *
 *  -> Input: previous node and goal       *
 *  <- Output: next up state node          *
 ******************************************/
const node *board::up(const node *previous,
                      const Table<uint>& goal_board) const
{
    //check for validity of move
    if (row <= 0)
        return nullptr;
    
    board *newBoard;
    newBoard = new board(this);
    // move empty tile in direction
    int tile = newBoard->move_up();
   // calculate the cost for this new state
    newBoard->distance.calculate(*newBoard, goal_board);
    // create node for queue placement
    node *up_state;
    up_state =  new node(newBoard->get_cost(), newBoard);
    // keep track of history    
    up_state->previous = previous;
    up_state->direction = (Qt::Key_Up);
    up_state->tile = tile;
    return up_state;      
}
/* *****************************************
 *  down ( )                               *
 *  -> Input: previous node and goal       *
 *  <- Output: next down state node        *
 ******************************************/
const node *board::down(const node *previous,
                        const Table<uint>& goal_board) const
{
    //check for validity of move
    if (row >= (size() - 1))
        return nullptr;
    
    board *newBoard;
    newBoard = new board(this);
    // move empty tile in direction
    int tile = newBoard->move_down();
   // calculate the cost for this new state
    newBoard->distance.calculate(*newBoard, goal_board);
    // create node for queue placement
    node *down_state;
    down_state =  new node(newBoard->get_cost(),newBoard);
    // keep track of history    
    down_state->previous = previous;
    down_state->direction = (Qt::Key_Down);
    down_state->tile = tile;
    return down_state;     
}

/* *****************************************
 *  cbegin ( )                             *
 *  return reference to beginning of       *
 *  tile vector                            *
 ******************************************/
vect_iter board::cbegin()
{
    return tiles.cbegin()->cbegin();
}
/* *****************************************
 *  cend ( )                               *
 *  return reference to end of             *
 *  tile vector                            *
 ******************************************/
vect_iter board::cend()
{
    return tiles.cend()->cend();
}
/* *****************************************
 *  get_depth ( )                          *
 *  return number of previous states       *
 *  to reach current state                 *
 ******************************************/
uint board::get_depth() const
{
    return distance.get_depth();
}
/* *****************************************
 *  get_cost ( )                           *
 *  return cost associated with            *
 *  reaching current state                 *
 ******************************************/
uint board::get_cost() const
{
    return distance.get_cost();
}
/* *****************************************
 *  size ( )                               *
 *  return dimension of tile board         *
 *  i.e: 3x3 matrix -> dim = 3             *
 ******************************************/
uint board::size() const
{
    return dimension;
}
/* *****************************************
 *  index ( )                              *
 *  return current index of blank          *
 ******************************************/
uint board::index() const
{
    return col + row * 3;
}


ostream& operator<< (ostream &out, const board& cBoard)
{
    out << "start = " << cBoard.col << " , " << cBoard.row
    << " | cost = " << cBoard.get_cost() << endl;

    for (uint i = 0; i < cBoard.size(); ++i) {
        out << "| ";
        for (uint j = 0; j < cBoard.size(); ++j)
            out << cBoard[i][j] << " | ";
        out << endl;
    }
    out << endl;
    return out;
}

ostream& operator<< (ostream &out,const board *cBoard)
{
    if (cBoard == nullptr)
        return out;
    
    out << "start = " << cBoard->col << " , " << cBoard->row
    << " | cost = " << cBoard->get_cost() << endl;

    for (uint i = 0; i < cBoard->size(); ++i) {
        out << "| ";
        for (uint j = 0; j < cBoard->size(); ++j)
            out << (*cBoard)[i][j] << " | ";
        out << endl;
    }
    out << endl;
    return out;
}

ostream& operator << (ostream& out,const vector<uint> vect)
{
    if (vect.size() <= 0) return out;
    for (uint i = 0; i < vect.size(); ++i) {
        out << " | ";
        out << vect[i];
    }
    out << " | ";
    return out;
} // end of << vector


/* *****************************************
 *  keygen( )                              *
 *  hash function for use in A* algorithm  *
 *  in search class                        *
 *  converts tile values into unique key   *
 *  identifier.                            *
 ******************************************/
uint64 keygen(const board *valBoard) {
    if (valBoard == nullptr)
        return 0;
    
    uint64 sum = 0;
    uint place = 1;
    uint dim =  valBoard->size();
    for (uint row = 0; row < dim; ++row) {
        for (uint col = 0; col < dim; ++col) {
            uint elem = (*valBoard)[row][col];
            sum += (elem * place);
            place *= BoardSize_Max;
        }
    }
    return sum;
}
