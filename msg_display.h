/* 
 * File:   msg_display.h
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * prototype of message class
 * 04/04/2015
 */

#ifndef MSG_DISPLAY_H
#define	MSG_DISPLAY_H

#include <QGraphicsTextItem>

class Message: public QGraphicsTextItem{
public:
    Message(QGraphicsItem * parent=0);
private:
};

#endif	/* MSG_DISPLAY_H */

