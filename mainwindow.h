#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define JUMP_VELOCITY 10
#define DEFAULT_GRAVITY 10

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QVector>
#include <QThread>
#include <thread>
#include <chrono>

class _KeysPressed {
public:
    _KeysPressed(): key({0,0}) {}
    bool Inventory() {return key.named._Inventory;}
    bool Right() {return key.named._Right;}
    bool Left() {return key.named._Left;}
    bool Up() {return key.named._Up;}
    bool Down() {return key.named._Down;}
    bool Jump() {return key.named._Jump;}
    bool Use() {return key.named._Use;}
    bool Esc() {return key.named._Esc;}
    void sInventory(bool c) {key.named._Inventory=c;}
    void sRight(bool c) {key.named._Right=c;}
    void sLeft(bool c) {key.named._Left=c;}
    void sUp(bool c) {key.named._Up=c;}
    void sDown(bool c) {key.named._Down=c;}
    void sJump(bool c) {key.named._Jump=c;}
    void sUse(bool c) {key.named._Use=c;}
    void sEsc(bool c) {key.named._Esc=c;}
public:
    union {
        int a[2];
        struct {
            bool _Inventory;
            bool _Right;
            bool _Left;
            bool _Up;
            bool _Down;
            bool _Jump;
            bool _Use;
            bool _Esc;
        } named;
    } key;
};

class _Keys{
public:
    _Keys() {}
    int Inventory;
    int Right;
    int Left;
    int Up;
    int Down;
    int Jump;
    int Use;
    int Esc;
};

class Worm {
public:
    Worm(int);
    qreal angle;
    qreal velocityX;
    qreal velocityY;
    QGraphicsPixmapItem* pointer;
    int hp;
    void damaged(int);
};

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

class MainWindow : public QGraphicsScene
{
    Q_OBJECT

public:
    MainWindow(QObject *parent = nullptr) : QGraphicsScene(parent), launched(NULL) {}
    MainWindow(qreal ax, qreal ay, qreal wid, qreal hig) : QGraphicsScene(ax,ay,wid,hig), launched(NULL), Items({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}) {}
    ~MainWindow() override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void startGame(int playerAmount,int level, int gravity);
    struct {
        union {
            QGraphicsItem* numbered[16];
            struct {
                QGraphicsPixmapItem* Inventory;
                QGraphicsPixmapItem* Highlight;
                QGraphicsLineItem* Scope;
            } named;
        } Item;
    } Items;
public slots:
    void Draw();
    void MoveItem(QGraphicsPixmapItem* Item, int moveX, int moveY);
    void AddItem(QPixmap map, QPen Pen, QBrush Brush);
    void AddItem(QGraphicsItem*);
    void RemoveItem(QGraphicsItem* Item);
    void SetLine(qreal,qreal,qreal,qreal);
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

class _Draw: public QObject {
    Q_OBJECT
public:
    _Draw(MainWindow* m): main(m) {}
    MainWindow* main;
public slots:
    void Draw();
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

#endif // MAINWINDOW_H
