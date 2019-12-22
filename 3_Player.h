#ifndef PLAYER_H
#define PLAYER_H

#include "2_Weap.h"

class Inventory{
public:
    Inventory();
    QVector<QGraphicsPixmapItem*> WeapIm;
};

class Player {
public:
    Player(int);
public:
    void showInventory();
    void hideInventory();
    bool moveInventoryUp();
    bool moveInventoryDown();
    bool getWeapon(int);
    QVector<Worm*> Worms;
    int  currentWorm;
    QVector<int> Inventory;
};

#endif // PLAYER_H