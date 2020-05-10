#include "scrolls.h"
#include "mainmenu.h"
#include "menu.h"
#include <QApplication>
#include <QGraphicsSceneMouseEvent>

StartGame::StartGame(){
    setPixmap(QPixmap(":/res/StartGame.png").scaled(400,150));
    setPos(400, 100);

}

Level::Level(){
    setPixmap(QPixmap(":/res/StartGame.png").scaled(400,150));
}

LoadSavedGame::LoadSavedGame(){
    setPixmap(QPixmap(":/res/StartGame.png").scaled(400,150));
}

Quit::Quit(){
    setPixmap(QPixmap(":/res/StartGame.png").scaled(400,150));
}

void StartGame::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    dynamic_cast<MainMenu*>(scene())->setCursorPos(1);
    dynamic_cast<MainMenu*>(scene())->setCursorEffect();
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void StartGame::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    dynamic_cast<MainMenu*>(scene())->setCursorPos(1);
    dynamic_cast<MainMenu*>(scene())->setCursorEffect();
}

void StartGame::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QApplication::restoreOverrideCursor();
}

void Level::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    dynamic_cast<MainMenu*>(scene())->setCursorPos(2);
    dynamic_cast<MainMenu*>(scene())->setCursorEffect();
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void Level::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    dynamic_cast<MainMenu*>(scene())->setCursorPos(2);
    dynamic_cast<MainMenu*>(scene())->setCursorEffect();
}

void Level::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QApplication::restoreOverrideCursor();
}

void LoadSavedGame::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    dynamic_cast<MainMenu*>(scene())->setCursorPos(3);
    dynamic_cast<MainMenu*>(scene())->setCursorEffect();
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void LoadSavedGame::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    dynamic_cast<MainMenu*>(scene())->setCursorPos(3);
    dynamic_cast<MainMenu*>(scene())->setCursorEffect();
}

void LoadSavedGame::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QApplication::restoreOverrideCursor();
}

void Quit::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    dynamic_cast<MainMenu*>(scene())->setCursorPos(4);
    dynamic_cast<MainMenu*>(scene())->setCursorEffect();
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void Quit::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    dynamic_cast<MainMenu*>(scene())->setCursorPos(4);
    dynamic_cast<MainMenu*>(scene())->setCursorEffect();
}

void Quit::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QApplication::restoreOverrideCursor();
}

void StartGame::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        clearFocus();
        QList<QGraphicsView *> currentViews = scene()->views();
        customGraphicsView *thisView = dynamic_cast<customGraphicsView*>(currentViews[0]);
        thisView->setScene(thisView->getGameplay());
        QApplication::restoreOverrideCursor();
        thisView->Gameplay(0);
    }
}

void Level::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        if(dynamic_cast<MainMenu*>(scene())->getLevel()==1){
            dynamic_cast<MainMenu*>(scene())->setLevel(2);
        }
        else if(dynamic_cast<MainMenu*>(scene())->getLevel()==2){
            dynamic_cast<MainMenu*>(scene())->setLevel(1);
        }
        dynamic_cast<MainMenu*>(scene())->setCursorEffect();
    }
}

void LoadSavedGame::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        clearFocus();
        QList<QGraphicsView *> currentViews = scene()->views();
        customGraphicsView *thisView = dynamic_cast<customGraphicsView*>(currentViews[0]);
        thisView->setScene(thisView->getGameplay());
        QApplication::restoreOverrideCursor();
        thisView->Gameplay(1);
    }
}

void Quit::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        exit(0);
    }
}
