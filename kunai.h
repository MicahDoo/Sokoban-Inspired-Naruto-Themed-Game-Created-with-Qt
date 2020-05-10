#ifndef KUNAI_H
#define KUNAI_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>

class Kunai: public QObject, public QGraphicsPixmapItem{
    //Q_OBJECT
public:
    Kunai();
};

#endif // KUNAI_H
