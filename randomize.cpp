/* 
 * File:   randomize.cpp
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * Definitions of randomize class
 * 04/04/2015
 */

#include "randomize.h"
#include "puzzle.h"
#include <QString>
#include <QFont>
#include <QGraphicsTextItem>


extern Puzzle *puzzle;
/* *****************************************
 *  accept ()                              *
 *  action taken when random button        *
 *  pressed. Re-order tiles on board.      *
 ******************************************/
void Randomize::accept() {
        
    const int keyArray[4] = {Qt::Key_Right,
                             Qt::Key_Left,
                             Qt::Key_Up,
                             Qt::Key_Down};
    // simulate random key presses!
    for (int i = 0; i < std::rand(); ++i) {
        int idx = std::rand() % puzzle->matrix->size();
        Cell *cell = (*puzzle->matrix)[idx];
        QKeyEvent *keyevent = new QKeyEvent(QEvent::Type::None, keyArray[std::rand() % 4], 0);
        cell->keyPressEvent(keyevent);
        delete keyevent;
    }
    puzzle->msg->setFont(QFont("times",16));
    puzzle->msg->setPlainText(QString("Board has been Randomized")); 
};