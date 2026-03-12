/*
Author: Donavan Sirois
Date: Febuary 1, 2026
File name: mainwindow.cpp
Description: Header file which implements the main window for the Qt application.
Modifications:
    Date: Febuary 2, 2026
        Author: Donavan Sirois
        Description: Added the paintEvent method which paints polygons to the screen. This
        method is no meant to be permanent and should be deleted eventually.
    Date: Febuary 24, 2026
        Author: Léanne Héroux
        Description: Added the gamePage the menuPage and the levelPage to the mainWindow
    Date: March 1, 2026
        Author: Léanne Héroux
        Description: Fixed the class hierarchy
*/
#include "mainwindow.h"

#include <QStackedWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800, 600); //aggrandi un peu la page par défaut
    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsView  *view  = new QGraphicsView(scene);
    scene->setSceneRect(0, 0, view->width(), view->height());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFrameStyle(0);
    engine = new Engine(scene, view->width(), view->height(), this, view);
    setCentralWidget(engine->getuiManager());
}

MainWindow::~MainWindow()
{}
