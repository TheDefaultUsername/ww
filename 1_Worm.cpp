#include "4_Scene.h"

void Worm::damaged(int a) {
    hp-=a;
    if (hp<=0) {
        QVector<Worm*> *Worms = &(((MainWindow*)(pointer->scene()))->Players[((MainWindow*)(pointer->scene()))->currentPlayer]->Worms);
        Worms->erase(Worms->begin()+(((MainWindow*)(pointer->scene()))->currentStep)%Worms->size());
        pointer->scene()->removeItem(pointer); //?!!

        ///EMT
    }
}

Worm::Worm(int w): angle(0), velocityX(0), velocityY(0), hp(1000) {
    QPoint pos = QPoint(rand()%(w-50),0);
    pointer = new QGraphicsPixmapItem(QPixmap(QString("src/wm.png")).scaled(QSize(50,50),Qt::KeepAspectRatio));
    pointer->setPos(pos);
}
