#include "MyPlayer.h"
#include "Boulder.h"
#include "Mark.h"
#include "Wall.h"
#include "menu.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QBrush>
#include <QImage>
#include <QPixmap>
#include <QVector>
#include <stdlib.h>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <fstream>
#include <ctime>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    customGraphicsView *view = new customGraphicsView();

    view->setFixedSize(1900,1000);
    //view->fitInView(view->scene()->sceneRect(), Qt::IgnoreAspectRatio);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();


    return a.exec();
}
