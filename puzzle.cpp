/* 
 * File:   puzzle.cpp
 * Author: Zach Foresta 
 * email : zachary.foresta@gmail.com
 * 
 * Definitions of Puzzle class
 * 04/04/2015
 */

#include "puzzle.h"
#include <QApplication>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>
#include <QImage>
#include <QVBoxLayout>
#include "randomize.h"

/* *****************************************
 *  C O N S T R U C T O R                  *
 *  Sets up program environment.           *
 ******************************************/
Puzzle::Puzzle()
 {
     scene = new QGraphicsScene;
     scene->setSceneRect(0,0,WIDTH,LENGTH);
     
     setScene(scene);
     setFixedSize(WIDTH,LENGTH);
     
     setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     setWindowTitle(tr("8 Puzzle Solver"));
     
     solveButton = new UIButton;
     solveButton->setObjectName(QStringLiteral("solveButton"));
     solveButton->setDefault(true);
     solveButton->setText(QApplication::translate("Dialog", "&Solve", 0));
     solveButton->setGeometry(WIDTH - 200,LENGTH/2 - 50, 100, 50);
     
     solver = new Solve();
     
     playButton = new UIButton;
     playButton->setObjectName(QStringLiteral("playButton"));
     playButton->setDefault(true);
     playButton->setText(QApplication::translate("Dialog", "&Play", 0));
     playButton->setGeometry(WIDTH - 200,LENGTH/2 - 100, 100, 50);
     
     randomizer = new Randomize;
     
     randButton = new UIButton;
     randButton->setObjectName(QStringLiteral("randButton"));
     randButton->setDefault(true);
     randButton->setText(QApplication::translate("Dialog", "&Random", 0));
     randButton->setGeometry(WIDTH - 200,LENGTH/2 - 150, 100, 50);
     
     exitButton = new UIButton;
     exitButton->setObjectName(QStringLiteral("exitButton"));
     exitButton->setDefault(true);
     exitButton->setText(QApplication::translate("Dialog", "E&xit", 0));
     exitButton->setGeometry(WIDTH - 200,LENGTH/2, 100, 50);
     
     scene->addWidget(solveButton);
     scene->addWidget(playButton);
     scene->addWidget(randButton);
     scene->addWidget(exitButton);
     
     
     matrix = new Matrix();
     matrix->setPos(150, 150);
     scene->addItem(matrix);
     
     for (int i = 0; i < matrix->size(); ++i) {
         Cell *cell = (*matrix)[i];
         cell->setPos(cell->x() + 150,
                      cell->y() + 150);
         cell->setFlag(QGraphicsItem::ItemIsFocusable);
         cell->setFocus();
         scene->addItem(cell);
         QObject::connect(cell, SIGNAL(moved()), solveButton, SLOT(enable()));
         QObject::connect(cell, SIGNAL(moved()), playButton, SLOT(disable()));
     }
     
     msg = new Message;
     msg->setPos(10, 10);
     scene->addItem(msg);
     
     playButton->setEnabled(false);
     
     QObject::connect(randButton, SIGNAL(clicked()), randomizer, SLOT(accept()));
     QObject::connect(solveButton, SIGNAL(clicked()), solver, SLOT(accept()));
     QObject::connect(playButton, SIGNAL(clicked()), solver, SLOT(play()));
     QObject::connect(exitButton, SIGNAL(clicked()), solver, SLOT(reject()));
     
     QObject::connect(solveButton, SIGNAL(clicked()), randButton, SLOT(disable()));
     QObject::connect(solveButton, SIGNAL(released()), playButton, SLOT(enable()));
     
     QObject::connect(randButton, SIGNAL(clicked()), playButton, SLOT(disable()));
     QObject::connect(randButton, SIGNAL(clicked()), solveButton, SLOT(enable()));
     
     QObject::connect(playButton, SIGNAL(clicked()), playButton, SLOT(disable()));
     QObject::connect(playButton, SIGNAL(clicked()), solveButton, SLOT(disable()));
     QObject::connect(solver, SIGNAL(timedout()), randButton, SLOT(enable()));
     QObject::connect(solver, SIGNAL(timedout()), solveButton, SLOT(enable()));
     
     show();
 }

 Puzzle::~Puzzle()
 {
     delete msg;
     delete solveButton;
     delete playButton;
     delete randButton;
     delete exitButton;
     delete matrix;
     delete scene;
 }