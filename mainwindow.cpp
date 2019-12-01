#include "mainwindow.h"
#include <QGraphicsItem>

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key()==Keys.Inventory) KeysPressed.sInventory(true);
    if (event->key()==Keys.Right) KeysPressed.sRight(true);
    if (event->key()==Keys.Left) KeysPressed.sLeft(true);
    if (event->key()==Keys.Up) KeysPressed.sUp(true);
    if (event->key()==Keys.Down) KeysPressed.sDown(true);
    if (event->key()==Keys.Jump) KeysPressed.sJump(true);
    if (event->key()==Keys.Use) KeysPressed.sUse(true);
    if (event->key()==Keys.Esc) KeysPressed.sEsc(true);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key()==Keys.Inventory) KeysPressed.sInventory(false);
    if (event->key()==Keys.Right) KeysPressed.sRight(false);
    if (event->key()==Keys.Left) KeysPressed.sLeft(false);
    if (event->key()==Keys.Up) KeysPressed.sUp(false);
    if (event->key()==Keys.Down) KeysPressed.sDown(false);
    if (event->key()==Keys.Jump) KeysPressed.sJump(false);
    if (event->key()==Keys.Use) KeysPressed.sUse(false);
    if (event->key()==Keys.Esc) KeysPressed.sEsc(false);
}

MainWindow::~MainWindow()
{
}

void MainWindow::startGame(int playerAmount, int level, int gravity) {
    //this->clear();
    //this->setBackgroundBrush(QColor(128,192,255,255));
    ///currentLevel=Levels[level];
    currentLevel=QVector<int>(600,100);
    for (int i = 0; i<currentLevel.size(); i++) {
        this->addRect(QRect(i,400-currentLevel[i],1,currentLevel[i]),QPen(QColor(0,0,0,0)),QBrush(QColor(150,75,0,255)));
    }
    this->constants.gravity=gravity;
    Players.clear();
    for (int i = 0; i<playerAmount; i++) {
        Players.push_back(new Player());
        for (int j = 0; j<Players[i]->Worms.size(); j++) {
            this->addItem(Players[i]->Worms[j]->pointer);
        }
    }
    //QGraphicsRectItem k(QRect(400,0,200,100));
    //k.setPen(QColor(0,0,0,0)); k.setBrush(QImage(QString("inv.png")));
    //this->addItem(&k);
}

void _Draw::Draw() {
    ///std::this_thread::sleep_for(std::chrono::seconds(5));
    //((QGraphicsRectItem*)(main->items()[0]))->setRect(QRect(0,0,200,100));
    /*std::this_thread::sleep_for(std::chrono::seconds(5));
    QGraphicsRectItem k(QRect(400,0,200,100));
    k.setPen(QColor(0,0,0,0)); k.setBrush(QImage(QString("inv.png")));
    this->main->addItem(&k);
    std::this_thread::sleep_for(std::chrono::seconds(15));*/
    main->Keys.Right=Qt::Key_Right;
    main->Keys.Left=Qt::Key_Left;
    main->Keys.Up=Qt::Key_Up;
    main->Keys.Down=Qt::Key_Down;
    main->Keys.Esc=Qt::Key_Escape;
    main->Keys.Use=Qt::Key_Enter;
    main->Keys.Inventory=Qt::Key_I;
    main->Keys.Jump=Qt::Key_Space;
    emit stopped();
}

void MainWindow::Draw() {
    this->setBackgroundBrush(QColor(128,192,255,255));
    currentLevel=QVector<int>(600,100);
    for (int i = 0; i<currentLevel.size(); i++) {
        this->addRect(QRect(i,400-currentLevel[i],1,currentLevel[i]),QPen(QColor(0,0,0,0)),QBrush(QColor(150,75,0,255)));
    }
    QGraphicsRectItem* k = new QGraphicsRectItem(QRect(400,0,200,100));
    k->setPen(QColor(0,0,0,0)); k->setBrush(QImage(QString("inv.png")));
    this->addItem(k);
    QGraphicsRectItem* h = new QGraphicsRectItem(QRect(400,0,50,50));
    h->setPen(QColor(0,0,0,0)); h->setBrush(QImage(QString("inv2.png")));
    this->addItem(h);
    //QGraphicsScene::addRect(0,0,50,50);
    Items.Item.named.Inventory=k;
    Items.Item.named.Highlight=h;
    startGame(1,0,10);
    //std::this_thread::sleep_for(std::chrono::seconds(5));
    //MoveItem(h,50,0);
}

void _Logick::Draw() {
    bool invMove = true;
    while(true) {
        if (statuses.named.inInventory) {
            if (main->KeysPressed.Right()) {
                if (main->Items.Item.named.Highlight->rect().x()+50<main->constants.width) {
                    if (invMove) {
                        emit MoveItem(main->Items.Item.named.Highlight,50,0);
                        invMove=false;
                        std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); invMove=true;}).detach();
                    }
                }
            }
            if (main->KeysPressed.Left()) {
                if (main->Items.Item.named.Highlight->rect().x()>main->constants.width-200) {
                    if (invMove) {
                        emit MoveItem(main->Items.Item.named.Highlight,-50,0);
                        invMove=false;
                        std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); invMove=true;}).detach();
                    }
                }
            }
            if (main->KeysPressed.Down()) {
                if (main->Items.Item.named.Highlight->rect().y()==0) {
                    if (invMove) {
                        emit MoveItem(main->Items.Item.named.Highlight,0,50);
                        invMove=false;
                        std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); invMove=true;}).detach();
                    }
                } else {
                    if (invMove) {
                        //main->Players[1/*current*/]->moveInvUp();
                        invMove=false;
                        std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); invMove=true;}).detach();
                    }
                }
            }
            if (main->KeysPressed.Up()) {
                if (main->Items.Item.named.Highlight->rect().y()==50) {
                    if (invMove) {
                        emit MoveItem(main->Items.Item.named.Highlight,0,-50);
                        invMove=false;
                        std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); invMove=true;}).detach();
                    }
                } else {
                    if (invMove) {
                        //main->Players[1/*current*/]->moveInvDown();
                        invMove=false;
                        std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); invMove=true;}).detach();
                    }
                }
            }
            if (main->KeysPressed.Inventory()||main->KeysPressed.Esc()) {
                if (invMove) {
                    main->Items.Item.named.Highlight->hide();
                    main->Items.Item.named.Inventory->hide();
                    //main->Players[]->hideInv();
                    invMove=false;
                    std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(250)); invMove=true;}).detach();
                    statuses.named.inInventory=false;
                }
            }
            if (main->KeysPressed.Use()) {
                statuses.named.inInventory=false;
                main->Items.Item.named.Highlight->hide();
                main->Items.Item.named.Inventory->hide();
                int num = (main->Items.Item.named.Highlight->rect().y()*4+(200-(main->constants.width - main->Items.Item.named.Highlight->rect().x())))/50;
                //main->Players[]->getWeap(num);
                //main->Players[]->hideInv();
            }
        } else if (statuses.named.inMenu) {

        } else if (statuses.named.shooting) {

        } else {
            if (main->KeysPressed.Inventory()) {
                if (invMove) {
                    statuses.named.inInventory=true;
                    main->Items.Item.named.Highlight->show();
                    main->Items.Item.named.Inventory->show();
                    //main->Players[]->showInv()
                    invMove=false;
                    std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(250)); invMove=true;}).detach();
                }
            }
        }
    }
}

void MainWindow::MoveItem(QGraphicsRectItem* item, int mX, int mY) {
    item->setRect(
                item->rect().x()+mX,
                item->rect().y()+mY,
                item->rect().width(),
                item->rect().height()
                );
}

void MainWindow::RemoveItem(QGraphicsItem *item) {
    this->RemoveItem(item);
}

void MainWindow::AddItem(QRect rect, QPen pen, QBrush brush) {
    QGraphicsRectItem* k = new QGraphicsRectItem(rect);
    k->setPen(pen); k->setBrush(brush);
    //Players[1]->Worms[currentWorm].addWeapon()
}

Player::Player(): currentWorm(0), Inventory(20,0) {
    for (int i = 0; i < 5; i++) {
        Worms.push_back(new Worm());
    }
}

Worm::Worm(): angle(0), velocityX(0), velocityY(0) {
    pos=QRect(rand()%600,0,50,50);
    pointer = new QGraphicsRectItem(pos);
    //pointer->setPen(QPen(QColor(0,0,0,0)));
}
