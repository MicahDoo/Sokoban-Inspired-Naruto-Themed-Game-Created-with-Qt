#include "Boulder.h"
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

#include <QDebug>

Boulder::Boulder(int i, int j){
    setPixmap(QPixmap(":/res/Boulder.png").scaled(100,100));
    setPos(j*100, i*100+150);
}

Boulder::Boulder(){
    setPixmap(QPixmap(":/res/Boulder.png").scaled(100,100));
}
