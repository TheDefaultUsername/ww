#ifndef LOGICK_H
#define LOGICK_H

#include "4_Scene.h"

class _Load: public QObject {
    Q_OBJECT
public:
    _Load(MainScene* m): main(m) {}
    MainScene* main;
public slots:
    void Load();
signals:
    void AddItem(QGraphicsItem*);
    void stopped();
};

class Menu: public QObject {
    Q_OBJECT
public:
    Menu(MainScene* m);
    int current_action;
    int current_menu;
    void MoveUp();
    void MoveDown();
    void show();
    void hide();
    bool accept();
    QVector<long int> resizeTemplates;
    QVector<int> level;
    bool isLevelSand;
    int playeramount;
    int gravity;
    MainScene* main;
    QVector<QGraphicsPixmapItem*> buttons;
    QVector<QGraphicsTextItem*> texts;
signals:
    void MoveItem(QGraphicsItem* Item, int moveX, int moveY);
    void SetPlainText(QGraphicsTextItem* a,QString b);
};

class _Logick: public QObject {
    Q_OBJECT
public:
    MainScene* main;
    Menu* menu;
    _Logick(MainScene* m, Menu* mm): main(m), menu(mm), statuses({false,false,false,false,false}) {}
public slots:
    void Draw();
signals:
    void MoveItem(QGraphicsItem* Item, int moveX, int moveY);
    void AddItem(QPixmap map, QPen Pen, QBrush Brush);
    void AddItem(QGraphicsItem*);
    void RemoveItem(QGraphicsItem* Item);
    void SetLine(qreal,qreal,qreal,qreal);
    void startGame(int playerAmount,QVector<int>* level, int gravity);
    void NextStep();
public:
    union {
        bool numbered[5];
        struct {
            bool inInventory;
            bool inMenu;
            bool shooting;
        } named;
    } statuses;
};

class _Physic: public QObject {
    Q_OBJECT
public:
    MainScene* main;
    _Physic(MainScene* m): main(m), waterlevel(0) {}
    qreal waterlevel;
public slots:
    void Draw();
signals:
    void MoveItem(QGraphicsItem* Item, int moveX, int moveY);
    void RemoveItem(QGraphicsItem* Item);
    void AddItem(QGraphicsItem*);
};

#endif // LOGICK_H
