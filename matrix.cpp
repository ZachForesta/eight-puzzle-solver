/* 
 * File:   matrix.cpp
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * definitions for matrix class
 * 04/04/2015
 */

#include "matrix.h"
#include <QDebug>


Matrix::Matrix()
{
    setRect(0,0,WIDTH,LENGTH);
    int cube = std::sqrt(size() + 1);
    order = new int[9];
    for (int i = 0; i < size(); ++i) {
        order[i] = i + 1;
        table[i] = new Cell(i + 1);
        int row = i / cube;
        int col = i % cube;
        table[i]->setPos(Cell::WIDTH * col, Cell::LENGTH * row);
    }
    order[size()] = 0;
}

Cell *Matrix::operator [](int idx)
{
    return table[idx];
}

void Matrix::change_order(int num, int dir)
{
    int i;
    for (i = 0; i <= size(); i++) {
        if (order[i] == num)
            break;
    }
    /* [0, 1, 2
     *  3. 4. 5
     *  6, 7, 8]
     */
    int temp = num;
    switch(dir) {
        case Qt::Key_Right:
            order[i] = order[i + 1];
            order[i + 1] = temp;
            break;
        case Qt::Key_Left:
            order[i] = order[i - 1];
            order[i - 1] = temp;
            break;
        case Qt::Key_Up:
            order[i] = order[i - 3];
            order[i - 3] = temp;
            break;
        case Qt::Key_Down:
            order[i] = order[i + 3];
            order[i + 3] = temp;
            break;
    }
//    for (i = 0; i <= size(); i++) {
//        qDebug() << order[i] << " | ";
//    }
//    qDebug() << " ";
}

Matrix::~Matrix()
{
//    delete table;
    delete [] order;
}
