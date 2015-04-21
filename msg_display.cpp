/* 
 * File:   msg_display.cpp
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * definition of message class
 * 04/04/2015
 */

#include "msg_display.h"
#include <QFont>

Message::Message(QGraphicsItem* parent)
: QGraphicsTextItem(parent)
{
    setPlainText(QString("8 Puzzle Solver - select an option"));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));
}
