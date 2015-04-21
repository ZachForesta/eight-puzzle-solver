/* 
 * File:   cell.cpp
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * Definitions of cell class
 * 04/04/2015
 */

#include "cell.h"
#include <QPixmap>
#include <QKeyEvent>
#include <QList>
#include "puzzle.h"
#include "matrix.h"
#include <typeinfo>
#include <string>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

extern Puzzle *puzzle;

/* *****************************************
 *  C O N S T R U C T O R                  *
 *  Sets up tile with correct icon         *
 ******************************************/
Cell::Cell(int num, QGraphicsItem* parent)
:QGraphicsPixmapItem(parent), number(num), valid(false)
{
    Q_INIT_RESOURCE(icons);
    
    std::string select;
    switch(num) {
        case 1:
            select = ":/images/one.png";
            break;
        case 2:
            select = ":/images/two.png";
            break;
        case 3:
            select = ":/images/three.png";
            break;
        case 4:
            select = ":/images/four.png";
            break;
        case 5:
            select = ":/images/five.png";
            break;
        case 6:
            select = ":/images/six.png";
            break;
        case 7:
            select = ":/images/seven.png";
            break;
        default:
            select = ":/images/eight.png";
            break;
    }
    setPixmap(QPixmap(QString(select.c_str())));
}

/* *****************************************
 *  keyPressEvent (event)                  *
 *  signal linked with arrow keys          *
 *  main action of tiles is to move        *
 *  left, right, up or down if not already *
 *  constrained by puzzle or tile.         *
 ******************************************/
void Cell::keyPressEvent(QKeyEvent* event)
{
    int curr_x = pos().x();
    int curr_y = pos().y();
    // move the player left and right
    valid = false;
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 150) {
            valid = true;
            setPos(x()- WIDTH,y());
        }
        
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + WIDTH < Matrix::WIDTH + 150) {
            valid = true;
            setPos(x()+ WIDTH,y());
        }
    }
    else if (event->key() == Qt::Key_Down){
        if (pos().y() + LENGTH < Matrix::LENGTH + 150) {
            valid = true;
            setPos(x(),y() + LENGTH);
        }
    }
    else if (event->key() == Qt::Key_Up){
        if (pos().y() > 150) {
            valid = true;
            setPos(x(),y() - LENGTH);
        }
    }
    
    QList<QGraphicsItem *> collisions = collidingItems();
    
    bool cellInteraction = false;
    for (auto iter = collisions.cbegin(); iter != collisions.cend(); ++iter) {
        if (typeid(*(*iter)) == typeid(Cell)) {
            cellInteraction = true;
            break;
        }
    }
    
    if (cellInteraction) {
        // not allow movement
        setPos(curr_x,curr_y);
    } else {
        if (valid) {
            puzzle->matrix->change_order(number, event->key());
            emit moved();
        }
    }
}
