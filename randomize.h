/* 
 * File:   randomize.h
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * prototype of randomize class
 * 04/04/2015
 */

#ifndef RANDOMIZE_H
#define	RANDOMIZE_H

#include <QWidget>
#include <QKeyEvent>
#include <cstdio>
#include "matrix.h"

class Randomize : public QWidget
{
    Q_OBJECT
public:
    Randomize() {};
public slots:
    void accept();
private:
};

#endif	/* RANDOMIZE_H */

