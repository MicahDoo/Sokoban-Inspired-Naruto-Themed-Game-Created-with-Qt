#ifndef MENU_H
#define MENU_H

#include "MyPlayer.h"
#include "Boulder.h"
#include "scrolls.h"
#include "kunai.h"
#include "title.h"
#include "Wall.h"
#include "mainmenu.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
#include <stdlib.h>

class customGraphicsView: public QGraphicsView{
    Q_OBJECT
public:
    customGraphicsView();
    QVector<QVector<int>> getMap();
    int getCursorPos();
    QGraphicsScene *getGameplay();
    MainMenu *getMenu();
    QVector<Wall*> getAllWalls();
    void setVolumeUp();
    void Gameplay(int mode);
public slots:
    void volumeDown();
public slots:
    void volumeUp();
public slots:
    void deleteWarning();
private:
    MainMenu *menu;
    QGraphicsScene *gameplay;
    QGraphicsTextItem *noSaved;
    QVector<QVector<int>> map;
    MyPlayer *player;
    QVector<Wall*> allWalls;
    QTimer *timer;
    QTimer *volumetimer;

};

#endif // MENU_H
