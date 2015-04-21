/* 
 * File:   matrix.h
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * Prototype of Matrix class
 * 04/04/2015
 */

#ifndef MATRIX_H
#define	MATRIX_H

#include <QGraphicsRectItem>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "cell.h"

class Matrix : public QGraphicsRectItem //, public QGraphicsView
{
public:
    enum{WIDTH = 300, LENGTH = 300};
    Matrix();
    ~Matrix();
    int size() const {
        return CELLS;
    }
    Cell *operator[](int idx);
    int getNumber(int idx) const {
        return order[idx];
    }
    void change_order(int num, int dir);
    int *getOrder() const {
        return order;
    }
private:
    int *order;
    enum{CELLS = 8};
    Cell *table[CELLS];
};

#endif	/* MATRIX_H */

