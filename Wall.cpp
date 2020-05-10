#include "Wall.h"
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

#include <QDebug>

Wall::Wall(int i, int j){
    setPixmap(QPixmap(":/res/Wall.png").scaled(100,100));
    setPos(j*100, i*100+150);
}
