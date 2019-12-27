#include "4_Scene.h"

void Worm::damaged(int a) {
    if (hp<=0) return;
    hp-=a;
    onGround=false;
    onGroundV=false;
    if (hp<=0) {
        QVector<Worm*> *Worms = &(((MainScene*)(pointer->scene()))->Players.at(pid)->Worms);
        if (Worms->front()==this&&Worms->back()==this) ((MainScene*)(pointer->scene()))->curPlC--;
        if (this == Worms->at(((MainScene*)(pointer->scene()))->currentStep%Worms->size())) emit NextStep();
        auto k = Worms->begin();
        while (*k != this) k++;
        Worms->erase(k);
        emit RemoveItem(pointer); //?!!

    }
}

Worm::Worm(int w): angle(0), velocityX(0), velocityY(0), hp(1000), onGround(false), onGroundV(false) {
    QPoint pos = QPoint(rand()%(w-50),0);
    pointer = new QGraphicsPixmapItem(QPixmap(QString("src/wm.png")).scaled(QSize(50,50),Qt::KeepAspectRatio));
    pointer->setPos(pos);
}
