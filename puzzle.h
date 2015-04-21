/* 
 * File:   puzzle.h
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * Prototype of Puzzle class
 * 04/04/2015
 */

#ifndef PUZZLE_H
#define	PUZZLE_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "matrix.h"
#include "solve.h"
#include <QPushButton>
#include "randomize.h"
#include "msg_display.h"

class UIButton : public QPushButton
{
    Q_OBJECT
public:
    UIButton() : QPushButton() {}
public slots:
    void disable() {
        setEnabled(false);
    }
    void enable() {
        setEnabled(true);
    }
};

class Puzzle : public QGraphicsView
{
    public:
        enum {WIDTH = 800, LENGTH = 600};
        Puzzle();
        ~Puzzle();
         Matrix *matrix;
         Message *msg;
    private: 
        UIButton *solveButton;
        UIButton *playButton;
        UIButton *randButton;
        UIButton *exitButton;
        Randomize *randomizer;
        Solve *solver;
        QGraphicsScene *scene;
        
};

#endif	/* PUZZLE_H */

