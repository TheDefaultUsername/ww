#include "4_Scene.h"
#include <cmath>

Player::Player(int w): currentWorm(0) {
    for (int i = 0; i < 3; i++) {
        Worms.push_back(new Worm(w));
    }
}

void Player::showInventory() {
    if (Worms.empty()) return;
    QGraphicsScene* scene = Worms.front()->pointer->scene();
    if (!scene) return;
    QVector<QGraphicsPixmapItem*> *pointers = &((MainScene*)scene)->Inventory;
    int *inventoryLayout=&((MainScene*)scene)->inventoryLayout;
    for (int i = 0; i< 8; i++) {
        pointers->at(*inventoryLayout+i)->show();
    }
}
void Player::hideInventory() {
    if (Worms.empty()) return;
    QGraphicsScene* scene = Worms.front()->pointer->scene();
    if (!scene) return;
    QVector<QGraphicsPixmapItem*> *pointers = &((MainScene*)scene)->Inventory;
    int *inventoryLayout=&((MainScene*)scene)->inventoryLayout;
    for (int i = 0; i< 8; i++) {
        pointers->at(*inventoryLayout+i)->hide();
    }
}
bool Player::moveInventoryUp() {
    if (Worms.empty()) return false;
    QGraphicsScene* scene = Worms.front()->pointer->scene();
    if (!scene) return false;
    QVector<QGraphicsPixmapItem*> *pointers = &((MainScene*)scene)->Inventory;
    int *inventoryLayout=&((MainScene*)scene)->inventoryLayout;
    if (*inventoryLayout==0) return false;
    for (int i = 0; i< 4; i++) {
        pointers->at(*inventoryLayout+4+i)->hide();
    }
    (*inventoryLayout)-=4;
    for (int i = 0; i< 4; i++) {
        pointers->at(*inventoryLayout+i)->show();
    }
    return true;
}
bool Player::moveInventoryDown() {
    if (Worms.empty()) return false;
    QGraphicsScene* scene = Worms.front()->pointer->scene();
    if (!scene) return false;
    QVector<QGraphicsPixmapItem*> *pointers = &((MainScene*)scene)->Inventory;
    int *inventoryLayout=&((MainScene*)scene)->inventoryLayout;
    if (pointers->size()==*inventoryLayout+8) return false;
    for (int i = 0; i< 4; i++) {
        pointers->at(*inventoryLayout+i)->hide();
    }
    (*inventoryLayout)+=4;
    for (int i = 0; i< 4; i++) {
        pointers->at(*inventoryLayout+4+i)->show();
    }
    return true;
}
bool Player::getWeapon(int a) {
    if (Worms.empty()) return false;
    MainScene* scene = (MainScene*)Worms.front()->pointer->scene();
    if (!scene) return false;
    int *inventoryLayout=&(scene->inventoryLayout);
    if (Inventory[*inventoryLayout+a]>0) {
        Inventory[*inventoryLayout+a]-=1;
        currentWorm=*inventoryLayout + a;
        scene->Item.named.Scope=new QGraphicsLineItem(
                    Worms[scene->currentStep%Worms.size()]->pointer->pos().x()+25,
                    Worms[scene->currentStep%Worms.size()]->pointer->pos().y()+25,
                    Worms[scene->currentStep%Worms.size()]->pointer->pos().x()+25 - 50*sin(Worms[scene->currentStep%Worms.size()]->angle),
                    Worms[scene->currentStep%Worms.size()]->pointer->pos().x()+25 - 50*cos(Worms[scene->currentStep%Worms.size()]->angle)
                    );
        QPen pen;
        pen.setDashPattern(QVector<qreal>(2,5));
        ((MainScene*)scene)->Item.named.Scope->setPen(pen);
        return true;
    }
    return false;
}
