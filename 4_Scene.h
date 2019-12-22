#ifndef SCENE_H
#define SCENE_H

#include "3_Player.h"
#include <QGraphicsScene>

class MainWindow : public QGraphicsScene
{
    Q_OBJECT

public:
    MainWindow(QObject *parent = nullptr) : QGraphicsScene(parent), launched(NULL) {}
    MainWindow(qreal ax, qreal ay, qreal wid, qreal hig) : QGraphicsScene(ax,ay,wid,hig), launched(NULL), Item({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}) {}
    ~MainWindow() override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void startGame(int playerAmount,int level, int gravity);
    union {
        QGraphicsItem* numbered[16];
        struct {
            QGraphicsPixmapItem* Inventory;
            QGraphicsPixmapItem* Highlight;
            QGraphicsLineItem* Scope;
        } named;
    } Item;
public slots:
    void Draw();
    void MoveItem(QGraphicsPixmapItem* Item, int moveX, int moveY);
    void AddItem(QPixmap map, QPen Pen, QBrush Brush);
    void AddItem(QGraphicsItem*);
    void RemoveItem(QGraphicsItem* Item);
    void SetLine(qreal,qreal,qreal,qreal);
    void SetPlainText(QGraphicsTextItem* a,QString b) {a->setPlainText(b);}
public:
    struct {
        int gravity;
        int playersCount;
        int width;
        int height;
        int FPS;
    } constants;
    int inventoryLayout;
    int currentPlayer;
    int currentStep;
    _Keys Keys;
    _KeysPressed KeysPressed;
    QVector<int> currentLevel;
    QVector<Player*> Players;
    Weapon* launched;
    QVector<QGraphicsPixmapItem*> Inventory;
};

#endif // SCENE_H
