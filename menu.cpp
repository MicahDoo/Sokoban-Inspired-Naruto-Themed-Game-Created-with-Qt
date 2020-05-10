#include "menu.h"
#include "scrolls.h"
#include "kunai.h"
#include "MyPlayer.h"
#include "Boulder.h"
#include "Mark.h"
#include "Wall.h"
#include "mainmenu.h"
#include <unistd.h>
#include <QDir>
#include <QApplication>

#include <QDebug>

#define LEFT 1400


customGraphicsView::customGraphicsView(){


    // add scenes
    menu = new MainMenu();
    gameplay = new QGraphicsScene();
    setScene(menu);
}

void customGraphicsView::Gameplay(int mode){//mode: 0=normal, 1=saved game, 2=restart, 3=newgame, 4 = continue
    using namespace std;
    QApplication::setOverrideCursor(Qt::WaitCursor);

    if (mode != 2){ //mode==2 means restart
        // paint a background
        gameplay->setBackgroundBrush(QBrush(QImage(":/res/Ground.jpeg")));

        // clear map
        for(int i = 0; i < map.size(); ++i){
            qDebug() << "clearing map row" << i;
            QVector<int>().swap(map[i]);
            Q_ASSERT(map[i].capacity()==0);
            map[i].clear();
            map[i].squeeze();
        }
        QVector<QVector<int>>().swap(map);
        Q_ASSERT(map.capacity()==0);
        map.clear();
        map.squeeze();
        qDebug() << "StartBuildingMap";
        QFile file;

        QVector<Wall*>().swap(allWalls);
        Q_ASSERT(allWalls.capacity()==0);
        allWalls.clear();
        allWalls.squeeze();


        if(mode == 0 || mode == 3 || mode == 4){
            switch(menu->getLevel()){
            case 1:{
                file.setFileName(":/Level 1.txt");
                break;
            }
            case 2:{
                file.setFileName(":/Level 2.txt");
                break;
            }
            default:{
                file.setFileName(":/Level 1.txt");
                break;
            }
            }
        }else{
            QDir dir(":/Level 1.txt");
            QString filepath(dir.currentPath());
            qDebug() << filepath;
            filepath.append("/SavedGame.txt");
            qDebug() << filepath;
            //QFile file(filepath);
            file.setFileName(filepath);
        }

        qDebug()<<"SavedGame.txt opened";


        if(!file.exists()){
            qDebug() << "File Does not exist!";
            setScene(menu);
            QApplication::restoreOverrideCursor();
            noSaved = new QGraphicsTextItem();
            noSaved->setPlainText(QString("No game has been saved."));
            noSaved->setDefaultTextColor(Qt::magenta);
            noSaved->setFont(QFont("serif", 80));
            menu->addItem(noSaved);
            QTimer::singleShot(2000,this,SLOT(deleteWarning()));
            return;
        }
        qDebug() << "FileDoesExists!";
       if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            exit(0);
        //file.open();

        qDebug()<<"SavedGame.txt opened and ready";

        QTextStream inStream(&file);

        char numRead;
        if(mode == 0 || mode == 3 || mode == 4){
            QString A, B;
            inStream >> numRead;
            srand(time(nullptr));
            B[0] = rand()%(numRead-48)+48+1;
            B[1] = '.';

            qDebug() << "puzzle number" << B[0];

            do{
                A = inStream.readLine(2);
            }while(A.compare(&B) != 0);
            inStream >> numRead;
        }

        map.push_back(QVector<int>());

        inStream >> numRead;
        int i = 0;
        do{
            if( numRead-48 <= 6 && numRead-48 >= 0){
                map[i].push_back(numRead-48);
                qDebug() << numRead;
            }
            else if(numRead == '\n'){
                map.push_back(QVector<int>());
                ++i;
                qDebug() << "newLine";
            }
            inStream >> numRead;
        }while(numRead != '.');

        if(mode == 1){
            qDebug() << "ReadingSteps";
            int stepRead;
            inStream >> stepRead;
            qDebug() << "SettingSteps=" << stepRead;
            player = new MyPlayer(stepRead);
            inStream >> numRead;
            qDebug() << "ReadingLevel";
            int levelRead;
            inStream >> levelRead;
            menu->setLevelTo(levelRead);
        }
        else{
            player = new MyPlayer();
        }
        file.close();
    }
    else{
        player = new MyPlayer();
        gameplay->clear();
        qDebug() << "restart: previous scene cleared";
    }

    if(mode == 0 || mode == 1){
        timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this, SLOT(volumeDown()));
        timer->start(100);
    }

    scene()->addItem(player->getStepCount());
    player->getShowLevel()->setPlainText(QString("Level = ")+QString::number(menu->getLevel()));
    scene()->addItem(player->getShowLevel());
    scene()->addItem(player->getShowProgress());
    scene()->addItem(player->getStatus());
    scene()->addItem(player->getShowKeys());

    player->setToZero();

    qDebug() << map.size() << "rows";
    qDebug() << map[0].size() << "columns";

    for(int i = 0, n = map.size(); i < n; ++i){
        for(int j = 0, m = map[i].size(); j < m; ++j){
            if(map[i][j] == 4 || map[i][j] == 5 || map[i][j] == 6){
                Mark *mark = new Mark(i, j);
                player->increaseMarkCount();
                gameplay->addItem(mark);
                if(map[i][j] == 5){
                    player->increaseMatchCount();
                }
            }
        }
    }
    qDebug() << "marks counted";
    for(int i = 0, n = map.size(); i < n; ++i){
        for(int j = 0, m = map[i].size(); j < m; ++j){
            switch(map[i][j]){
            case 1:{
                qDebug() << "wall";
                Wall *wall = new Wall(i, j);
                allWalls.push_back(wall);
                gameplay->addItem(wall);
                break;
            }
            case 2:{
                qDebug() << "player";
                player -> setPos(j*100, i*100+150);

                // make player focusable
                clearFocus();
                menu->clearFocus();
                this->clearFocus();
                player->setFlag(QGraphicsItem::ItemIsFocusable);
                player->setFocus();
                break;
            }
            case 3:{
                qDebug() << "boulder";
                Boulder *boulder = new Boulder(i, j);

                // add the item to the scene
                gameplay->addItem(boulder);
                break;
            }
            case 5:{
                qDebug() << "boulder and mark";
                Boulder *boulder = new Boulder(i, j);
                boulder->setPixmap(QPixmap(":/res/BoulderMatched.png").scaled(100,100));
                // add the item to the scene
                gameplay->addItem(boulder);
                break;
            }
            case 6:{
                qDebug() << "player and mark";
                player -> setPos(j*100, i*100+150);

                // add the item to the scene
                gameplay->addItem(player);

                // make player focusable
                clearFocus();
                menu->clearFocus();
                this->clearFocus();
                player->setFlag(QGraphicsItem::ItemIsFocusable);
                player->setFocus();
                break;
            }
            }
        }
    }
    qDebug() << "map built";
    player->getShowProgress()->setPlainText(QString::number(player->getMatchCount())+QString(" stones matched, ")+QString::number(player->getMarkCount())+QString(" marks to match, ")+QString::number(player->getMarkCount()-player->getMatchCount())+QString(" more matches to break the seal"));
    qDebug() <<"game progress set";
    gameplay->addItem(player);
    setHidden(true);
    gameplay->setSceneRect(gameplay->itemsBoundingRect());
    setFixedSize(gameplay->width(),gameplay->height());
    QApplication::restoreOverrideCursor();
    showNormal();
    qDebug() << "View Show!";
}

QGraphicsScene * customGraphicsView::getGameplay(){
    return gameplay;
}
MainMenu * customGraphicsView::getMenu(){
    return menu;
}

QVector<QVector<int>> customGraphicsView::getMap(){
    return map;
}

QVector<Wall*> customGraphicsView::getAllWalls(){
    return allWalls;
}

void customGraphicsView::volumeDown(){
    static QList<QGraphicsView *> currentViews = scene()->views();
    static customGraphicsView *thisView = dynamic_cast<customGraphicsView*>(currentViews[0]);
    static int downcounter = 1;
    qDebug("volume decreased");
    ++downcounter;
    if(downcounter <= 35){
        thisView->getMenu()->getMusic()->setVolume(50-downcounter);
    }
    else{
        downcounter = 1;
        timer->disconnect(this);
    }
}

void customGraphicsView::volumeUp(){
    static QList<QGraphicsView *> currentViews = scene()->views();
    static customGraphicsView *thisView = dynamic_cast<customGraphicsView*>(currentViews[0]);
    static int upcounter = 1;
    qDebug("volume increased");
    ++upcounter;
    if(upcounter <= 35){
        thisView->getMenu()->getMusic()->setVolume(15+upcounter);
    }
    else{
        upcounter = 1;
        volumetimer->disconnect(this);
    }
}

void customGraphicsView::setVolumeUp(){
    volumetimer = new QTimer();
    connect(volumetimer,SIGNAL(timeout()),this,SLOT(volumeUp()));
    volumetimer->start(100);
}

void customGraphicsView::deleteWarning(){
    menu->removeItem(noSaved);
}
