#ifndef GAME_H
#define GAME_H

#include "MyPlayer.h"
#include "Boulder.h"
#include "scrolls.h"
#include "kunai.h"
#include "title.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
#include <stdlib.h>

class Game: public QGraphicsScene{
public:
    Game();
    int getCursorPos();
    void cursorUp();
    void cursorDown();
    int getLevel();
    void keyPressEvent(QKeyEvent *event);
public slots:
    int setCursorEffect();
private:
    int cursorPos = 1;
    int level = 1;
    MyPlayer *pain;
    Boulder *boulder;

    StartGame *startgame;
    Level *leveloption;
    LoadSavedGame *loadsave;
    Quit *quit;

    Kunai *kunai1;
    Kunai *kunai2;
    Kunai *kunai3;
    Kunai *kunai4;

    Title *title;
};




#endif // GAME_H
