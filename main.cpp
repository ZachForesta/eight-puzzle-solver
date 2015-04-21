/*
 * File:   main.cpp
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * Copyright (C) 2015 under GNU GPL, see <http://www.gnu.org/licenses/>
 * 
 * This project was created to illustrate the functionality of Qt
 * and the deep iterative search algorithm.
 * 04/04/2015
 */

#include <QApplication>
#include "puzzle.h"

Puzzle *puzzle;
int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    puzzle = new Puzzle;
    
    // create and show puzzle
    puzzle->show();
    return app.exec();
}
