/* 
 * File:   utilities.h
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * aggregate of utility functions and type definitions
 * for project.
 * 04/04/2015
 */

#ifndef UTILITIES_H
#define	UTILITIES_H

/* *****************************************
 *          L I B R A R I E S              *
 ******************************************/
#include <iostream>
#include <climits>
#include <vector>
#include <math.h>
#include <list>
#include <fstream>
#include <map>
#include <QKeyEvent>
#include <QApplication>
#include <QGraphicsTextItem>


// namespace std objects using
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::vector;
using std::list;
using std::pair;
using std::string;

/* *****************************************
 *             T Y P E D E F S             *
 ******************************************/
// Typedef and structures
typedef unsigned int uint;
typedef unsigned long long int uint64;
typedef typename vector<uint>::const_iterator vect_iter;
// Alias templates
template<typename T>
using Table = vector<vector<T>>;
template<typename keyType, typename valueType, typename predType>
using Hash = std::multimap<keyType, valueType, predType>;

typedef enum{
    BEGIN = 1,
    END   = 2
}puzzle_t;

/* *****************************************
 *            C O N S T A N T S            *
 ******************************************/
//note limitation only allowing 3 x 3 puzzle solutions
const uint BoardSize_Max = 9;

/* *****************************************
 *  F U N C T I O N  P R O T O T Y P E S   *
 ******************************************/
//Function Prototypes
vector<uint> ReadFromFile(const char *arg);
vector<uint> stringTovector(const string& istr);
vector<uint> getState(puzzle_t type, const int& arg_count,
                      const char **arg_variable);
bool verifyBoard(const vector<uint>& start, const vector<uint>& end);
bool valid_board(const vector<uint>& board);
bool solvable(const vector<uint>& start, const vector<uint>& end);
ostream& operator << (ostream& out, const vector<uint> vect);
bool solvable(const vector<uint>& start, const vector<uint>& end);
uint greater_than_count(const vector<uint>& vect);
vector<uint> stringTovector(const string& str);


/*******************************************
 * P R E D I C A T E
 *     for hash function
 *******************************************/
template <typename KeyType>
struct Predicate {
    bool operator()(const KeyType& key1, const KeyType& key2) const {
        //sort priority
        return (key1 < key2);
    }
};

#endif	/* UTILITIES_H */

