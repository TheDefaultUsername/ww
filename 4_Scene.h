#ifndef SCENE_H
#define SCENE_H

#include "3_Player.h"
#include <QGraphicsScene>

class MainScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MainScene(QObject *parent = nullptr) : QGraphicsScene(parent), launched(NULL) {}
    MainScene(qreal ax, qreal ay, qreal wid, qreal hig) : QGraphicsScene(ax,ay,wid,hig), launched(NULL), Item({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}) {}
    ~MainScene() override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override; 
    union {
        QGraphicsItem* numbered[16];
        struct {
            QGraphicsPixmapItem* Inventory;
            QGraphicsPixmapItem* Highlight;
            QGraphicsLineItem* Scope;
            QGraphicsRectItem* Water;
        } named;
    } Item;
public slots:
    void startGame(int playerAmount,QVector<int>* level, int gravity);
    void Draw();
    void MoveItem(QGraphicsItem* Item, int moveX, int moveY);
    void AddItem(QPixmap map, QPen Pen, QBrush Brush);
    void AddItem(QGraphicsItem*);
    void RemoveItem(QGraphicsItem* Item);
    void SetLine(qreal,qreal,qreal,qreal);
    void SetPlainText(QGraphicsTextItem* a,QString b) {a->setPlainText(b);}
    void NextStep();
public:
    struct {
        int gravity;
        int playersCount;
        int width;
        int height;
        int FPS;
    } constants;
    int curPlC;
    int inventoryLayout;
    int currentPlayer;
    int currentStep;
    _Keys Keys;
    _KeysPressed KeysPressed;
    QVector<QGraphicsRectItem*> currentLevel;
    QVector<Player*> Players;
    Weapon* launched;
    QVector<QGraphicsPixmapItem*> Inventory;
    class Inventory inv;
    QThread* Log;
    QThread* Phy;
};

#endif // SCENE_H
