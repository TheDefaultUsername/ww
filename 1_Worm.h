#ifndef WORM_H
#define WORM_H

#include "0_KeyPress.h"
#include <QGraphicsItem>

class Worm {
public:
    Worm(int);
    qreal angle;
    qreal velocityX;
    qreal velocityY;
    QGraphicsPixmapItem* pointer;
    int hp;
    bool onGround;
    bool onGroundV;
    void damaged(int);
};

#endif //WORM_H
