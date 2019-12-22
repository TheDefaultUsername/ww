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
    Menu(MainWindow* m): main(m) {}
    int current_action;
    int current_menu;
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void accept();
    QVector<int> gravityVariables;
    QVector<long int> resizeTemplates;
    QVector<int> level;
    bool isLevelSand;
    MainWindow* main;
};

class _Logick: public QObject {
    Q_OBJECT
public:
    MainWindow* main;
    Menu* menu;
    _Logick(MainWindow* m, Menu* mm): main(m), menu(mm) {}
public slots:
    void Draw();
signals:
    void MoveItem(QGraphicsPixmapItem* Item, int moveX, int moveY);
    void AddItem(QPixmap map, QPen Pen, QBrush Brush);
    void AddItem(QGraphicsItem*);
    void RemoveItem(QGraphicsItem* Item);
    void SetLine(qreal,qreal,qreal,qreal);
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
