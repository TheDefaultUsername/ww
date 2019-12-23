#ifndef WEAP_H
#define WEAP_H

#include "1_Worm.h"
#include <thread>
#include <chrono>

class Weapon {
public:
    bool isSpecific;
    qreal velocityX;
    qreal velocityY;
    bool isBanana;
    bool bananed;
    int damage;
    int radius;
    int specID;
    void* creator;
    QVector<Weapon*> bananaChilds;
    QGraphicsPixmapItem *pointer;
    Weapon(bool iss,
           bool isb,
           qreal velX,
           qreal velY,
           int dam,
           int rad,
           int spid) :
        isSpecific(iss),
        velocityX(velX),
        velocityY(velY),
        isBanana(isb),
        damage(dam),
        radius(rad),
        specID(spid),
        pointer(NULL) {}
    QGraphicsItem* detonate();
};

#endif // WEAP_H
