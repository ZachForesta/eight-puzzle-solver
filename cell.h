/* 
 * File:   cell.h
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * prototype of cell class
 * 04/04/2015
 */

#ifndef CELL_H
#define	CELL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

class Cell : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum{WIDTH = 100, LENGTH = 100};
    Cell(int num = 0, QGraphicsItem * parent = 0);
    ~Cell() {};
    int getNumber() const {
        return number;
    }
    void keyPressEvent(QKeyEvent * event);
    bool isValid() const {
        return valid;
    }
signals:
    void moved();
private:
    int number;
    bool valid;
};

#endif	/* CELL_H */

