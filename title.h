#ifndef TITLE_H
#define TITLE_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>

class Title: public QObject, public QGraphicsPixmapItem{
    //Q_OBJECT
public:
    Title();
};


#endif // TITLE_H
