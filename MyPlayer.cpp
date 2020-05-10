#include "MyPlayer.h"
#include "Boulder.h"
#include "Mark.h"
#include "menu.h"
#include "mainmenu.h"
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QObject>
#include <QDebug>
#include <QDir>
#include <QtGlobal>
#include <QFont>
#include <unistd.h>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#define FONT "serif"
#define FONT_SIZE 16


MyPlayer::MyPlayer(int i, int j){
    setPixmap(QPixmap(":/res/PainShadow.png").scaled(100,100));
    setPos(j*100, i*100+150);

}

MyPlayer::MyPlayer(bool a){
    setPixmap(QPixmap(":/res/PainShadow.png").scaled(100,100));
    gamepremise = new QGraphicsPixmapItem();
    //gamepremise->setPixmap(QPixmap(":/res/GamePremise.png").scaled(1000,400));
    gamepremise->setPos(500,10);
}

MyPlayer::MyPlayer(){
    setPixmap(QPixmap(":/res/PainShadow.png").scaled(100,100));
    step = 0;
    stepThisTime = 0;
    stepCount = new QGraphicsTextItem();
    stepCount->setPlainText(QString("Step Count = ")+QString::number(step));
    stepCount->setDefaultTextColor(Qt::blue);
    stepCount->setFont(QFont(FONT, FONT_SIZE));
    showLevel = new QGraphicsTextItem();
    showLevel->setDefaultTextColor(Qt::darkGreen);
    showLevel->setFont(QFont(FONT, FONT_SIZE));
    showLevel->setPos(showLevel->x()+300,showLevel->y());
    showKeys = new QGraphicsTextItem();
    showKeys->setPlainText(QString("Esc: quit, S: save, R: restart, Z: rewind, N: new game"));
    showKeys->setFont(QFont(FONT, FONT_SIZE));
    showKeys->setDefaultTextColor(Qt::darkMagenta);
    showKeys->setPos(showKeys->x(),showKeys->y()+35);
    showProgress = new QGraphicsTextItem();
    showProgress->setDefaultTextColor(Qt::darkRed);
    showProgress->setFont(QFont(FONT, FONT_SIZE));
    showProgress->setPos(showProgress->x(),showProgress->y()+70);
    status = new QGraphicsTextItem();
    status->setPlainText(QString("Starting a New Game!"));
    status->setDefaultTextColor(Qt::black);
    status->setFont(QFont(FONT, FONT_SIZE));
    status->setPos(status->x(),status->y()+105);
}

MyPlayer::MyPlayer(int s){
    setPixmap(QPixmap(":/res/PainShadow.png").scaled(100,100));
    step = s;
    stepThisTime = 0;
    stepCount = new QGraphicsTextItem();
    stepCount->setPlainText(QString("Step Count = ")+QString::number(step));
    stepCount->setDefaultTextColor(Qt::blue);
    stepCount->setFont(QFont(FONT, FONT_SIZE));
    showLevel = new QGraphicsTextItem();
    showLevel->setDefaultTextColor(Qt::darkGreen);
    showLevel->setFont(QFont(FONT, FONT_SIZE));
    showLevel->setPos(showLevel->x()+300,showLevel->y());
    showKeys = new QGraphicsTextItem();
    showKeys->setPlainText(QString("Esc: quit, S: save, R: restart, Z: rewind, N: new game"));
    showKeys->setFont(QFont(FONT, FONT_SIZE));
    showKeys->setDefaultTextColor(Qt::darkMagenta);
    showKeys->setPos(showKeys->x(),showKeys->y()+35);
    showProgress = new QGraphicsTextItem();
    showProgress->setDefaultTextColor(Qt::darkRed);
    showProgress->setFont(QFont(FONT, FONT_SIZE));
    showProgress->setPos(showProgress->x(),showProgress->y()+70);
    status = new QGraphicsTextItem();
    status->setPlainText(QString("Resume Saved Game!"));
    status->setDefaultTextColor(Qt::black);
    status->setFont(QFont(FONT, FONT_SIZE));
    status->setPos(status->x(),status->y()+105);

}

void MyPlayer::keyPressEvent(QKeyEvent *event){

    static QList<QGraphicsView *> currentViews = scene()->views();
    static customGraphicsView *thisView = dynamic_cast<customGraphicsView*>(currentViews[0]);
    static QVector<QVector<int>> map;
    static QVector<QVector<int>> path;
    static QVector<int> moveTypeLog(sizeof(int)*1000);
    static QVector<int> moveDirLog(sizeof(int)*1000);
    static int n, m;
    static int player_x, player_y;
    static int xChange, yChange;

    if(markCount == matchCount){
        clearFocus();
        scene()->clear();
        if(thisView->getMenu()->getLevel()==1){
            qDebug() << "on to next level";
            thisView->getMenu()->increaseLevel();
            thisView->Gameplay(4);
        }
        else{
            qDebug() << "game over";
            thisView->setFixedSize(1900,1000);
            thisView->setVolumeUp();
            thisView->setScene(thisView->getMenu());
            thisView->getMenu()->setCursorEffect();
        }
        return;
    }

    int *start = NULL, *first = NULL, *second = NULL;

    if(stepThisTime==0){
        map = thisView->getMap();
        n = map.size();
        m = map[0].size();
        qDebug() << n << "rows";
        qDebug() << m << "columns";
        path.reserve(sizeof(int)*100*20);
        path.squeeze();

        qDebug() << "allocated";
        for(int i = 0; i < n; ++i){
            path.push_back(QVector<int>());
            path[i].reserve(sizeof(int)*20);
            path[i].squeeze();
            for(int j = 0; j < m; ++j){
                path[i].push_back(int());
                qDebug() << "row" << i << "col" << j;
                if((path[i][j]=map[i][j])==2 || path[i][j] == 6){
                    player_x=i;
                    player_y=j;
                    qDebug() << "player is at row" << i << "col" << j;
                }
            }
        }
    }


    qDebug() << "MyPlayer knows that you pressed a key!";


    // identify starting spot, first spot, second spot according to direction input
    if (event->key() == Qt::Key_Left){
        if(player_y-2 >= 0){
            second = &(path[player_x][player_y-2]);
        }
        else {
            qDebug() << "player hits the wall";
            status->setPlainText(QString("Player hits the wall"));
            return;
        }
        start = &(path[player_x][player_y]);
        first = &(path[player_x][player_y-1]);
        xChange = 0;
        yChange = -1;
        directionLog = 1;
    }
    else if (event->key() == Qt::Key_Right){
        if(player_y+2 < path[player_x].size()){
            second = &(path[player_x][player_y+2]);
        }
        else {
            qDebug() << "player hits the wall";
            status->setPlainText(QString("Player hits the wall"));
            return;
        }
        start = &(path[player_x][player_y]);
        first = &(path[player_x][player_y+1]);
        xChange = 0;
        yChange = 1;
        directionLog = 2;
    }
    else if (event->key() == Qt::Key_Up){
        if(player_x-2 >= 0){
            second = &(path[player_x-2][player_y]);
        }
        else {
            status->setPlainText(QString("Player hits the wall"));
            return;
        }
        start = &(path[player_x][player_y]);
        first = &(path[player_x-1][player_y]);
        xChange = -1;
        yChange = 0;
        directionLog = 3;
    }
    else if (event->key() == Qt::Key_Down){
        if(player_x+2 < path.size()){
            second = &(path[player_x+2][player_y]);
        }
        else {
            status->setPlainText(QString("Player hits the wall"));
            return;
        }
        start = &(path[player_x][player_y]);
        first = &(path[player_x+1][player_y]);
        xChange = 1;
        yChange = 0;
        directionLog = 4;
    }
    else if(event->key() == Qt::Key_Escape){
        qDebug() << "You pressed the Esc key!";
        clearFocus();
        QList<QGraphicsView *> currentViews = scene()->views();
        customGraphicsView *thisView = dynamic_cast<customGraphicsView*>(currentViews[0]);
        thisView->setFixedSize(1900,1000);
        scene()->clear();
        thisView->setVolumeUp();
        thisView->setScene(thisView->getMenu());
        thisView->getMenu()->setCursorEffect();
        return;
    }
    else if(event->key() == Qt::Key_S){
        QDir dir(":/Level 1.txt");
        QString filepath(dir.currentPath());
        filepath.append("/SavedGame.txt");
        qDebug() << "file saved to " << filepath;
        QFile file(filepath);

        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            qDebug() << "can't save";
            exit(0);

        }
        QTextStream outStream(&file);

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                outStream << path[i][j];
                outStream << " ";
            }
            if(i != n-1)
                outStream << "\n";
        }
        outStream <<".";

        outStream << step;

        outStream << ".";

        outStream << thisView->getMenu()->getLevel();
        return;
    }
    else if(event->key() == Qt::Key_R){
        clearFocus();
        QList<QGraphicsView *> currentViews = scene()->views();
        customGraphicsView *thisView = dynamic_cast<customGraphicsView*>(currentViews[0]);
        thisView->setScene(thisView->getGameplay());
        thisView->Gameplay(2);
        return;
    }
    else if(event->key() == Qt::Key_Z){
        if(step == 0){
            status->setPlainText(QString("Can't move back anymore"));
            return;
        }
        if(moveTypeLog.last() == 1){//last step only player moves
            switch(moveDirLog.last()){
            case 1:{//left->right
                stepDecrease();
                qDebug() << "player moves back right";
                status->setPlainText(QString("Player moves back right"));
                path[player_x][player_y] = (path[player_x][player_y] == 2) ? 0 : 4;
                path[player_x][player_y+1] = (path[player_x][player_y+1] == 4) ? 6 : 2;
                ++player_y;
                setPos(x()+100,y());
                break;
            }
            case 2:{//right->left
                stepDecrease();
                qDebug() << "player moves back left";
                status->setPlainText(QString("Player moves back left"));
                path[player_x][player_y] = (path[player_x][player_y] == 2) ? 0 : 4;
                path[player_x][player_y-1] = (path[player_x][player_y-1] == 4) ? 6 : 2;
                --player_y;
                setPos(x()-100,y());
                break;
            }
            case 3:{//up->down
                stepDecrease();
                qDebug() << "player moves back down";
                status->setPlainText(QString("Player moves back down"));
                path[player_x][player_y] = (path[player_x][player_y] == 2) ? 0 : 4;
                path[player_x+1][player_y] = (path[player_x+1][player_y] == 4) ? 6 : 2;
                ++player_x;
                setPos(x(),y()+100);
                break;
            }
            case 4:{//down->up
                stepDecrease();
                qDebug() << "player moves back up";
                status->setPlainText(QString("Player moves back up"));
                path[player_x][player_y] = (path[player_x][player_y] == 2) ? 0 : 4;
                path[player_x-1][player_y] = (path[player_x-1][player_y] == 4) ? 6 : 2;
                --player_x;
                setPos(x(),y()-100);
                break;
            }
            }
            moveTypeLog.removeLast();
            moveDirLog.removeLast();
        }
        else if(moveTypeLog.last() == 2){//pushed a boulder
            switch(moveDirLog.last()){
            case 1:{//left->right
                stepDecrease();
                qDebug() << "player and boulder move back right";
                status->setPlainText(QString("Player moves back"));
                path[player_x][player_y+1] = (path[player_x][player_y+1] == 4) ? 6 : 2;
                if(path[player_x][player_y] == 6){
                    increaseMatchCount();
                    path[player_x][player_y] = 5;
                }
                else{
                    path[player_x][player_y] = 3;
                }
                if(path[player_x][player_y-1] == 5){
                    decreaseMatchCount();
                    path[player_x][player_y-1] = 4;
                }
                else{
                    path[player_x][player_y-1] = 0;
                }
                xChange = 0;
                yChange = 1;
                break;
            }
            case 2:{//right->left
                stepDecrease();
                qDebug() << "player and boulder move back left";
                status->setPlainText(QString("Player moves back"));
                path[player_x][player_y-1] = (path[player_x][player_y-1] == 4) ? 6 : 2;
                if(path[player_x][player_y] == 6){
                    increaseMatchCount();
                    path[player_x][player_y] = 5;
                }
                else{
                    path[player_x][player_y] = 3;
                }
                if(path[player_x][player_y+1] == 5){
                    decreaseMatchCount();
                    path[player_x][player_y+1] = 4;
                }
                else{
                    path[player_x][player_y+1] = 0;
                }
                xChange = 0;
                yChange = -1;
                break;
            }
            case 3:{//up->down
                stepDecrease();
                qDebug() << "player and boulder move back down";
                status->setPlainText(QString("Player moves back"));
                path[player_x+1][player_y] = (path[player_x+1][player_y] == 4) ? 6 : 2;
                if(path[player_x][player_y] == 6){
                    increaseMatchCount();
                    path[player_x][player_y] = 5;
                }
                else{
                    path[player_x][player_y] = 3;
                }
                if(path[player_x-1][player_y] == 5){
                    decreaseMatchCount();
                    path[player_x-1][player_y] = 4;
                }
                else{
                    path[player_x-1][player_y] = 0;
                }
                xChange = 1;
                yChange = 0;
                break;
            }
            case 4:{//down->up
                stepDecrease();
                qDebug() << "player and boulder move back up";
                status->setPlainText(QString("Player moves back"));
                path[player_x-1][player_y] = (path[player_x-1][player_y] == 4) ? 6 : 2;
                if(path[player_x][player_y] == 6){
                    increaseMatchCount();
                    path[player_x][player_y] = 5;
                }
                else{
                    path[player_x][player_y] = 3;
                }
                if(path[player_x+1][player_y] == 5){
                    decreaseMatchCount();
                    path[player_x+1][player_y] = 4;
                }
                else{
                    path[player_x+1][player_y] = 0;
                }
                xChange = -1;
                yChange = 0;
                break;
            }
            }
            setPos(x()-100*yChange,y()-100*xChange);
            QList<QGraphicsItem *> colliding_items = collidingItems();
            Boulder *thisBoulder = dynamic_cast<Boulder*>(colliding_items[0]);
            if(path[player_x][player_y]==5){
                thisBoulder->setPixmap(QPixmap(":/res/BoulderMatched.png").scaled(100,100));
            }
            else {
                thisBoulder->setPixmap(QPixmap(":/res/Boulder.png").scaled(100,100));
            }
            thisBoulder -> setPos(x()+100*yChange,y()+100*xChange);
            player_x += xChange;
            player_y += yChange;
            setPos(x()+200*yChange,y()+200*xChange);
            moveTypeLog.removeLast();
            moveDirLog.removeLast();

        }
        return;
    }
    else if(event->key() == Qt::Key_N){
        clearFocus();
        QList<QGraphicsView *> currentViews = scene()->views();
        customGraphicsView *thisView = dynamic_cast<customGraphicsView*>(currentViews[0]);
        scene()->clear();
        thisView->setScene(thisView->getGameplay());
        thisView->Gameplay(3);
        return;
    }
    else{
        return;
    }
    // determine the final movement according to the three variables

    if(*first == 0){
        qDebug() << "player walks casually";
        status->setPlainText(QString("Player walks"));
        qDebug() << "plain text set";
        stepIncrease();
        *start = (*start == 2) ? 0 : 4;
        *first = 2;
        player_x += xChange;
        player_y += yChange;
        setPos(x()+100*yChange,y()+100*xChange);
        qDebug() << "about to log move";
        moveTypeLog.push_back(1);
        qDebug()<<"moveTypeLog stored";
        moveDirLog.push_back(directionLog);
    }
    else if(*first == 1){
        qDebug() << "player hits the wall";
        status->setPlainText(QString("Player hits the wall"));
    }
    else if(*first == 3){
        if(*second == 0){
            qDebug() << "player moves boulder casually";
            status->setPlainText(QString("Player moves a boulder"));
            stepIncrease();

            *start = (*start == 2) ? 0 : 4;
            *first = 2;
            *second = 3;
            player_x += xChange;
            player_y += yChange;
            setPos(x()+100*yChange,y()+100*xChange);
            QList<QGraphicsItem *> colliding_items = collidingItems();
            Boulder *thisBoulder = dynamic_cast<Boulder*>(colliding_items[0]);
            thisBoulder -> setPos(x()+100*yChange,y()+100*xChange);
            moveTypeLog.push_back(2);
            moveDirLog.push_back(directionLog);
        }
        else if(*second == 3){
            qDebug() << "player fails to push two or more boulders at the same time";
            status->setPlainText(QString("Player can't push two or more stones simultaneously"));
        }
        else if(*second == 4){
            qDebug() << "player moves boulder onto a mark";
            status->setPlainText(QString("Player successfully matches a stone!"));
            stepIncrease();

            *start = (*start == 2) ? 0 : 4;
            *first = 2;
            *second = 5;
            player_x += xChange;
            player_y += yChange;
            increaseMatchCount();
            qDebug() << matchCount << "matches" << markCount-matchCount << "more to go";
            setPos(x()+100*yChange,y()+100*xChange);
            QList<QGraphicsItem *> colliding_items = collidingItems();
            Boulder *thisBoulder = dynamic_cast<Boulder*>(colliding_items[0]);
            thisBoulder->setPixmap(QPixmap(":/res/BoulderMatched.png").scaled(100,100));
            thisBoulder -> setPos(x()+100*yChange,y()+100*xChange);
            moveTypeLog.push_back(2);
            moveDirLog.push_back(directionLog);
        }
        else if(*second == 5){
            qDebug() << "player fails to push two or more boulders at the same time";
            status->setPlainText(QString("Player can't push two or more stones simultaneously"));
        }
    }
    else if(*first == 4){
        qDebug() << "player walks onto a mark";
        status->setPlainText(QString("Player walks"));
        stepIncrease();
        *start = (*start == 2) ? 0 : 4;
        *first = 6;
        player_x += xChange;
        player_y += yChange;
        setPos(x()+100*yChange,y()+100*xChange);
        moveTypeLog.push_back(1);
        moveDirLog.push_back(directionLog);
    }
    else if(*first == 5){
        if(*second == 0){
            qDebug() << "player pushes boulder off of a mark";
            status->setPlainText(QString("Player unmatches a stone"));
            stepIncrease();

            *start = (*start == 2) ? 0 : 4;
            *first = 6;
            *second = 3;
            player_x += xChange;
            player_y += yChange;
            decreaseMatchCount();
            qDebug() << matchCount << "matches" << markCount-matchCount << "more to go";
            setPos(x()+100*yChange,y()+100*xChange);
            QList<QGraphicsItem *> colliding_items = collidingItems();
            Boulder *thisBoulder = dynamic_cast<Boulder*>(colliding_items[0]);
            thisBoulder->setPixmap(QPixmap(":/res/Boulder.png").scaled(100,100));
            thisBoulder -> setPos(x()+100*yChange,y()+100*xChange);
            moveTypeLog.push_back(2);
            moveDirLog.push_back(directionLog);
        }
        else if(*second == 1){
            qDebug() << "player fails to push boulder into the wall";
            status->setPlainText(QString("Player can't push stone into wall"));
        }
        else if(*second == 3){
            qDebug() << "player fails to push two or more boulders at the same time";
            status->setPlainText(QString("Player can't push two or more stones simultaneously"));
        }
        else if(*second == 4){
            qDebug() << "player pushes boulder onto another mark";
            status->setPlainText(QString("Player pushes a stone"));
            stepIncrease();

            *start = (*start == 2) ? 0 : 4;
            *first = 6;
            *second = 5;
            player_x += xChange;
            player_y += yChange;
            setPos(x()+100*yChange,y()+100*xChange);
            QList<QGraphicsItem *> colliding_items = collidingItems();
            Boulder *thisBoulder = dynamic_cast<Boulder*>(colliding_items[0]);
            thisBoulder -> setPos(x()+100*yChange,y()+100*xChange);
            moveTypeLog.push_back(2);
            moveDirLog.push_back(directionLog);
        }
    }
    if(markCount == matchCount){
        qDebug() << "You won!";
        QMediaPlayer *feelthepain = new QMediaPlayer();
        feelthepain->setMedia(QUrl("qrc:/res/FeelThePain.mp3"));
        feelthepain->play();
        status->setPlainText(QString("Congratulations! You broke the seal! Press any key to continue"));
        QList<QGraphicsView *> currentViews = scene()->views();
        customGraphicsView *thisView = dynamic_cast<customGraphicsView*>(currentViews[0]);
        for(int i = 0, n = thisView->getAllWalls().size(); i < n; ++i){
            thisView->getAllWalls()[i]->setPixmap(QPixmap(":/res/CollapsedWall.png").scaled(100,100));
        }
        usleep(100);
        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(playerEscape()));
        timer->start(1);
    }
}

void MyPlayer::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    gamepremise->setPixmap(QPixmap(":/res/GamePremise.png").scaled(1000,400));
}
void MyPlayer::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    gamepremise->setPixmap(QPixmap(":/res/GamePremise.png").scaled(0,0));
}

void MyPlayer::increaseMarkCount(){
    ++markCount;
    qDebug() << "mark count = " << markCount;
}

void MyPlayer::increaseMatchCount(){
    ++matchCount;
    qDebug() << "match count = " << matchCount;
    showProgress->setPlainText(QString::number(matchCount)+QString(" stones matched, ")+QString::number(markCount)+QString(" marks to match, ")+QString::number(markCount-matchCount)+QString(" more matches to break the seal"));
}

void MyPlayer::setToZero(){
    markCount=0;
    matchCount=0;
}

void MyPlayer::setStepTo(int s){
    qDebug() << "SettingSteps ing!";
    step = s;
    qDebug() << "StepSettingDone!";
}

void MyPlayer::stepIncrease(){
    ++step;
    ++stepThisTime;
    qDebug()<<"step increased";
    stepCount->setPlainText(QString("Step Count = ")+QString::number(step));
}

QGraphicsTextItem* MyPlayer::getStepCount(){
    return stepCount;
}

QGraphicsTextItem* MyPlayer::getShowLevel(){
    return showLevel;
}

QGraphicsTextItem* MyPlayer::getStatus(){
    return status;
}

QGraphicsTextItem* MyPlayer::getShowProgress(){
    return showProgress;
}

void MyPlayer::decreaseMatchCount(){
    --matchCount;
    showProgress->setPlainText(QString::number(matchCount)+QString(" stones matched, ")+QString::number(markCount)+QString(" marks to match, ")+QString::number(markCount-matchCount)+QString(" more matches to break the seal"));
}

int MyPlayer::getMatchCount(){
    return matchCount;
}

int MyPlayer::getMarkCount(){
    return markCount;
}

void MyPlayer::stepDecrease(){
    --step;
    --stepThisTime;
    qDebug()<<"step decreased";
    stepCount->setPlainText(QString("Step Count = ")+QString::number(step));
}

QGraphicsTextItem* MyPlayer::getShowKeys(){
    return showKeys;
}

QGraphicsPixmapItem* MyPlayer::getGamepremise(){
    return gamepremise;
}

void MyPlayer::playerEscape(){
    static int timeElapsed = 0;
    static double speed = 0.5;
    ++timeElapsed;
    speed += 0.0001;
    if(timeElapsed >=500 && timeElapsed <= 1500){
        setPos(x()+1,y()+speed);
    }
    if(timeElapsed > 1500){
        timeElapsed = 0;
        speed = 0.5;
        qDebug()<<"out of bounds";
        timer->disconnect(this);
    }
}
