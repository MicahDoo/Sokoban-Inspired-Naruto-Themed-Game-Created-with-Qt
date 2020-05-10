#include "title.h"

Title::Title(){
    setPixmap(QPixmap(":/res/Title.png").scaled(800,600));
    setPos(500,400);
}
