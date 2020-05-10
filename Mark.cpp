#include "Mark.h"
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

#include <QDebug>

Mark::Mark(int i, int j){
    setPixmap(QPixmap(":/res/Mark.png").scaled(100,100));
    setPos(j*100, i*100+150);
}
