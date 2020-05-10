#ifndef MAINMENU_H
#define MAINMENU_H

#include "Boulder.h"
#include "scrolls.h"
#include "MyPlayer.h"
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
#include <QMediaPlayer>

class MainMenu: public QGraphicsScene{
public:
    MainMenu();
    int getCursorPos();
    void cursorUp();
    void cursorDown();
    void setCursorPos(int number);
    int getLevel();
    void Gameplay();
    void menuOperation();
    void setLevelTo(int l);
    void increaseLevel();
    QMediaPlayer *getMusic();
    void setLevel(int number);
    void keyPressEvent(QKeyEvent *event);
public slots:
    void setCursorEffect();
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

    QMediaPlayer *music;
    QTimer *timer;

};

#endif // MAINMENU_H
