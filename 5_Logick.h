#ifndef LOGICK_H
#define LOGICK_H

#include "4_Scene.h"

class _Load: public QObject {
    Q_OBJECT
public:
    _Load(MainWindow* m): main(m) {}
    MainWindow* main;
public slots:
    void Load();
signals:
    void AddItem(QGraphicsItem*);
    void stopped();
};

class Menu: public QObject {
    Q_OBJECT
public:
    Menu(MainWindow* m);
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
    MainWindow* main;
    QVector<QGraphicsPixmapItem*> buttons;
    QVector<QGraphicsTextItem*> texts;
signals:
    void MoveItem(QGraphicsPixmapItem* Item, int moveX, int moveY);
    void SetPlainText(QGraphicsTextItem* a,QString b);
};

class _Logick: public QObject {
    Q_OBJECT
public:
    MainWindow* main;
    Menu* menu;
    _Logick(MainWindow* m, Menu* mm): main(m), menu(mm), statuses({false,false,false,false,false}) {}
public slots:
    void Draw();
signals:
    void MoveItem(QGraphicsPixmapItem* Item, int moveX, int moveY);
    void AddItem(QPixmap map, QPen Pen, QBrush Brush);
    void AddItem(QGraphicsItem*);
    void RemoveItem(QGraphicsItem* Item);
    void SetLine(qreal,qreal,qreal,qreal);
    void startGame(int playerAmount,QVector<int>* level, int gravity);
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
    MainWindow* main;
    _Physic(MainWindow* m): main(m) {}
public slots:
    void Draw();
signals:
    void MoveItem(QGraphicsPixmapItem* Item, int moveX, int moveY);
    void RemoveItem(QGraphicsItem* Item);
    void AddItem(QGraphicsItem*);
};

#endif // LOGICK_H
