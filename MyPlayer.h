#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QKeyEvent>
#include <QObject>
#include <QVector>

class MyPlayer: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    MyPlayer(int i,int j);
    MyPlayer(bool a);
    MyPlayer();
    MyPlayer(int s);
    void stepIncrease();
    void stepDecrease();
    void setStepTo(int s);
    void increaseMarkCount();
    void increaseMatchCount();
    void decreaseMatchCount();
    int getMatchCount();
    int getMarkCount();
    QGraphicsPixmapItem* getGamepremise();
    void setToZero();
    QGraphicsTextItem *getStepCount();
    QGraphicsTextItem *getShowLevel();
    QGraphicsTextItem *getShowKeys();
    QGraphicsTextItem *getShowProgress();
    QGraphicsTextItem *getStatus();
    void keyPressEvent(QKeyEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
public slots:
    void playerEscape();
private:
    int markCount;
    int matchCount;
    int step;
    int stepThisTime;
    int directionLog;
    QGraphicsTextItem *stepCount;
    QGraphicsTextItem *showLevel;
    QGraphicsTextItem *showKeys;
    QGraphicsTextItem *showProgress;
    QGraphicsTextItem *status;
    QGraphicsPixmapItem *gamepremise;
    QTimer *timer;
    QTimer *volumetimer;
};

#endif // PLAYER_H
