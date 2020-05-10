#include "mainmenu.h"
#include "menu.h"
#include "scrolls.h"
#include "kunai.h"
#include "MyPlayer.h"
#include "Boulder.h"
#include "Mark.h"
#include "Wall.h"

#define LEFT 1400

#include <QList>
#include <QDebug>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>


MainMenu::MainMenu(){

    // add items
    pain = new MyPlayer(true);
    pain->setPixmap(QPixmap(":/res/Pain.png").scaled(400,500));
    pain->setPos(100,100);
    pain->setAcceptHoverEvents(true);
    addItem(pain);

    boulder = new Boulder();
    boulder->setPixmap(QPixmap(":/res/Boulder.png").scaled(400,400));
    boulder->setPos(10,410);
    //addItem(boulder);

    setBackgroundBrush(QBrush(QImage(":/res/BackGround.jpg")));

    setSceneRect(10,10,1900,1000);

    startgame = new StartGame();
    startgame->setPixmap(QPixmap(":/res/StartGame.png").scaled(400,150));
    startgame->setPos(LEFT,400);
    addItem(startgame);
    startgame->setAcceptHoverEvents(true);

    leveloption = new Level();
    leveloption->setPixmap(QPixmap(":/res/Level 1.png").scaled(400,150));
    leveloption->setPos(LEFT,550);
    addItem(leveloption);
    leveloption->setAcceptHoverEvents(true);

    loadsave = new LoadSavedGame();
    loadsave->setPixmap(QPixmap(":/res/LoadSavedGame.png").scaled(410,150));
    loadsave->setPos(LEFT,700);
    addItem(loadsave);
    loadsave->setAcceptHoverEvents(true);

    quit = new Quit();
    quit->setPixmap(QPixmap(":/res/Quit.png").scaled(410,150));
    quit->setPos(LEFT,850);
    addItem(quit);
    quit->setAcceptHoverEvents(true);

    kunai1 = new Kunai();
    kunai1->setPixmap(QPixmap(":/res/Kunai.png").scaled(100,100));
    kunai1->setPos(LEFT-100,430);
    addItem(kunai1);

    kunai2 = new Kunai();
    kunai2->setPos(LEFT-100,580);
    addItem(kunai2);

    kunai3 = new Kunai();
    kunai3->setPos(LEFT-100,730);
    addItem(kunai3);

    kunai4 = new Kunai();
    kunai4->setPos(LEFT-100,850);
    addItem(kunai4);

    title = new Title();
    addItem(title);

    addItem(pain->getGamepremise());

    startgame->setFlag(QGraphicsItem::ItemIsFocusable);
    startgame->setFocus();


    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/res/Girei.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music= new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
    music->setVolume(50);



    setCursorEffect();
}

void MainMenu::setCursorEffect(){
    switch(cursorPos){
    case 1:{
        startgame->setPixmap(QPixmap(":/res/StartGame.png").scaled(420,157));
        startgame->setPos(LEFT-3,390);
        if(level == 1){
            leveloption->setPixmap(QPixmap(":/res/Level 1.png").scaled(400,150));
        }
        else if(level == 2){
            leveloption->setPixmap(QPixmap(":/res/Level 2.png").scaled(400,150));
        }
        leveloption->setPos(LEFT-3,550);
        loadsave->setPixmap(QPixmap(":/res/LoadSavedGame.png").scaled(400,150));
        loadsave->setPos(LEFT,700);
        quit->setPixmap(QPixmap(":/res/Quit.png").scaled(400,150));
        quit->setPos(LEFT,850);
        kunai1->setPixmap(QPixmap(":/res/Kunai.png").scaled(100,100));
        kunai2->setPixmap(QPixmap(":/res/Kunai.png").scaled(0,0));
        kunai3->setPixmap(QPixmap(":/res/Kunai.png").scaled(0,0));
        kunai4->setPixmap(QPixmap(":/res/Kunai.png").scaled(0,0));
        break;
    }
    case 2:{
        if(level == 1){
            leveloption->setPixmap(QPixmap(":/res/Level 1.png").scaled(420,157));
        }
        else if(level == 2){
            leveloption->setPixmap(QPixmap(":/res/Level 2.png").scaled(428,158));
        }
        leveloption->setPos(LEFT-3,540);
        startgame->setPixmap(QPixmap(":/res/StartGame.png").scaled(400,150));
        startgame->setPos(LEFT,400);
        loadsave->setPixmap(QPixmap(":/res/LoadSavedGame.png").scaled(400,150));
        loadsave->setPos(LEFT,700);
        quit->setPixmap(QPixmap(":/res/Quit.png").scaled(400,150));
        quit->setPos(LEFT,850);
        kunai1->setPixmap(QPixmap(":/res/Kunai.png").scaled(0,0));
        kunai2->setPixmap(QPixmap(":/res/Kunai.png").scaled(100,100));
        kunai3->setPixmap(QPixmap(":/res/Kunai.png").scaled(0,0));
        kunai4->setPixmap(QPixmap(":/res/Kunai.png").scaled(0,0));
        break;
    }
    case 3:{
        startgame->setPixmap(QPixmap(":/res/StartGame.png").scaled(400,150));
        startgame->setPos(LEFT,400);
        loadsave->setPixmap(QPixmap(":/res/LoadSavedGame.png").scaled(420,157));
        loadsave->setPos(LEFT-3,690);
        if(level == 1){
            leveloption->setPixmap(QPixmap(":/res/Level 1.png").scaled(400,150));
        }
        else if(level == 2){
            leveloption->setPixmap(QPixmap(":/res/Level 2.png").scaled(400,150));
        }
        leveloption->setPos(LEFT,550);
        quit->setPixmap(QPixmap(":/res/Quit.png").scaled(400,150));
        quit->setPos(LEFT,850);
        kunai1->setPixmap(QPixmap(":/res/Kunai.png").scaled(0,0));
        kunai2->setPixmap(QPixmap(":/res/Kunai.png").scaled(0,0));
        kunai3->setPixmap(QPixmap(":/res/Kunai.png").scaled(100,100));
        kunai4->setPixmap(QPixmap(":/res/Kunai.png").scaled(0,0));
        break;
    }
    case 4:{
        startgame->setPixmap(QPixmap(":/res/StartGame.png").scaled(400,150));
        startgame->setPos(LEFT,400);
        quit->setPixmap(QPixmap(":/res/Quit.png").scaled(420,157));
        quit->setPos(LEFT-3,840);
        loadsave->setPixmap(QPixmap(":/res/LoadSavedGame.png").scaled(400,150));
        loadsave->setPos(LEFT,700);
        if(level == 1){
            leveloption->setPixmap(QPixmap(":/res/Level 1.png").scaled(400,150));
        }
        else if(level == 2){
            leveloption->setPixmap(QPixmap(":/res/Level 2.png").scaled(400,150));
        }
        kunai1->setPixmap(QPixmap(":/res/Kunai.png").scaled(0,0));
        kunai2->setPixmap(QPixmap(":/res/Kunai.png").scaled(0,0));
        kunai3->setPixmap(QPixmap(":/res/Kunai.png").scaled(0,0));
        kunai4->setPixmap(QPixmap(":/res/Kunai.png").scaled(100,100));
        break;
    }
    }
}

void MainMenu::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Up){
        if(cursorPos>1){
            --cursorPos;
            setCursorEffect();
        }
    }
    else if (event->key() == Qt::Key_Down){
        if(cursorPos<4){
            ++cursorPos;
            setCursorEffect();
        }
    }
    else if (event->key() == Qt::Key_Left){
        if(cursorPos==2){
            if(level==1){
                level = 2;
            }
            else if(level==2){
                level = 1;
            }
            setCursorEffect();
        }
    }
    else if (event->key() == Qt::Key_Right){
        if(cursorPos==2){
            if(level==1){
                level = 2;
            }
            else if(level==2){
                level = 1;
            }
            setCursorEffect();
        }
    }
    else if (event->key() == Qt::Key_Return){
        qDebug()<<"Enter";
        switch(cursorPos){
        case 1:{
            clearFocus();
            QList<QGraphicsView *> currentViews = this->views();
            customGraphicsView *thisView = dynamic_cast<customGraphicsView*>(currentViews[0]);
            thisView->setScene(thisView->getGameplay());
            thisView->Gameplay(0);
            timer = new QTimer();
            connect(timer,SIGNAL(timeout()),this, SLOT(volumeDown()));
            timer->start(100);
            break;
        }
        case 2:{
            break;
        }
        case 3:{
            clearFocus();
            QList<QGraphicsView *> currentViews = this->views();
            customGraphicsView *thisView = dynamic_cast<customGraphicsView*>(currentViews[0]);
            thisView->setScene(thisView->getGameplay());
            thisView->Gameplay(1);
            timer = new QTimer();
            connect(timer,SIGNAL(timeout()),this, SLOT(volumeDown()));
            timer->start(100);
            break;
        }
        case 4:{
            qDebug() << "exit";
            exit(0);
        }
        }
    }
}

int MainMenu::getLevel(){
    return level;
}

void MainMenu::increaseLevel(){
    ++level;
}

void MainMenu::setLevelTo(int l){
    level = l;
}

void MainMenu::setCursorPos(int number){
    cursorPos=number;
}

void MainMenu::setLevel(int number){
    level = number;
}

QMediaPlayer * MainMenu::getMusic(){
    return music;
}

