/* 
 * File:   utilitis.cpp
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * definitions for common utility functions
 * 04/04/2015
 */

#include "utilities.h"

/* *****************************************
 *          U T I L I T I E S              *
 ******************************************/

/* *****************************************
 *  Global Functions:                      *
 * > Used to support subtasks across       *
 *   class objects
 ******************************************/


/* *****************************************
 *  getState( )                            *
 *  based on input, either reads puzzle    *
 *  states from a file input or user       *
 *  console input string                   *
 ******************************************/
vector<uint> getState(puzzle_t type, const int& arg_count,
                      const char **arg_variable)
{
    vector<uint> state;
    if ((arg_count == 3) &&
        (type < arg_count)) { //read from files
        state = ReadFromFile(arg_variable[type]);
    } else { //prompt user for input
        string input = "";
        
        if (type == BEGIN)
            cout << "Please enter the beginning board state: " << endl;
        else
            cout << "Please enter a ending board state: " << endl;
        
        cout << "Please enter a valid board 3 x 3 w/ values [0,8] : ";
        getline(cin, input);
        state = stringTovector(input);
    }
    return state;
}
/* *****************************************
 *  stringTovector( )                      *
 *  converts string input into vector<uint>*
 ******************************************/
vector<uint> stringTovector(const string& istr)
{
    vector<uint> retvector;
    
    for (uint i = 0; i < istr.size(); ++i)
        retvector.push_back(istr[i] -'0');
    
    return retvector;
}
/* *****************************************
 *  verifyBoard( )                         *
 *  returns a true if both boards are      *
 *  solvable and valid.                    *
 ******************************************/
bool verifyBoard(const vector<uint>& start, const vector<uint>& end)
{
    //verify board inputs before solving
    if (valid_board(start) != true) {
        cout << "Error Starting Board selection invalid!" << endl;
        cout << start << endl;
        return false;
    }
    if (valid_board(end) != true) {
        cout << "Error Ending Board selection invalid!" << endl;
        cout << end << endl;
        return false;
    }
    if (solvable(start, end) == false) {
        cout << "Solution not possible" << endl;
        return false;
    }
    return true;
}
/* *****************************************
 *  vaild_board( )                         *
 *  returns a true if a board state is     *
 *  the correct size, has unique tiles     *
 *  tiles are between 0 and max limit      *
 ******************************************/
bool valid_board(const vector<uint>& board)
{
    if (board.size() != BoardSize_Max)
        return false;
    //Check for valid range and unique elements
    vector<bool> tile_exists(BoardSize_Max);
    for (uint i = 0; i < BoardSize_Max; ++i) {
        uint current =  board[i];
        //tiles within bounds
        if (current < BoardSize_Max) {
            //check for repeats
            if (tile_exists[current] == true)
                return false;
            else
                tile_exists[current] = true;
            
        } else {
            return false;
        }
    }
    return true;
}

/* *****************************************
 *  ReadFromFile( )                        *
 *  read from given input file             *
 *  convert input into vector<uint> tiles  *
 ******************************************/
vector<uint> ReadFromFile(const char *arg) {
    vector<uint> states;

    if (arg != nullptr) {
        ifstream in_stream;
        uint line;
        in_stream.open(arg);
        do {
            in_stream >> line;
            if (in_stream.eof())
                break;

            states.push_back(line);
        } while (true);
        in_stream.close();
    }
    return states;
}

/* *****************************************
 *  solvable( )                            *
 *  returns true if both start and end     *
 *  states have same # of inversions       *
 ******************************************/
bool solvable(const vector<uint>& start, const vector<uint>& end)
{
    uint start_count = greater_than_count(start);
    uint end_count = greater_than_count(end);
    if ((start_count % 2) == (end_count % 2))
        return true;
    else
        return false;
}
/* *****************************************
 *  greater_than_count( )                  *
 *  find the total # of elements outside   *
 *  of numerical order.                    *
 ******************************************/
uint greater_than_count(const vector<uint>& vect)
{
    uint size = vect.size();
    uint greater_than_count = 0;
    for (uint i = 0; i < size; ++i) {
        if (vect[i] > 1) {
            for (uint j = i + 1; j < size; ++j) {
                if ((vect[j] != 0) &&
                    (vect[i] > vect[j]))
                    ++greater_than_count;
            }
        }
    }
    return greater_than_count;
}
