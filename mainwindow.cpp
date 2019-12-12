#include "mainwindow.h"
#include <QGraphicsItem>
#include <ctime>
#include <cmath>
#include <QDebug>
#include <QPainter>

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->nativeVirtualKey()==Keys.Inventory) KeysPressed.sInventory(true);
    if (event->key()==Keys.Right) KeysPressed.sRight(true);
    if (event->key()==Keys.Left) KeysPressed.sLeft(true);
    if (event->key()==Keys.Up) KeysPressed.sUp(true);
    if (event->key()==Keys.Down) KeysPressed.sDown(true);
    if (event->key()==Keys.Jump) KeysPressed.sJump(true);
    if (event->key()==Keys.Use) KeysPressed.sUse(true);
    if (event->key()==Keys.Esc) KeysPressed.sEsc(true);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->nativeVirtualKey()==Keys.Inventory) KeysPressed.sInventory(false);
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
    inventoryLayout=0;
    ///currentLevel=Levels[level];
    constants.playersCount=playerAmount;
    currentLevel=QVector<int>(600,100);
    for (int i = 0; i<currentLevel.size(); i++) {
        this->addRect(QRect(i,400-currentLevel[i],1,currentLevel[i]),QPen(QColor(0,0,0,0)),QBrush(QColor(150,75,0,255)));
    }
    this->constants.gravity=gravity;
    Players.clear();
    for (int i = 0; i<playerAmount; i++) {
        Players.push_back(new Player(constants.width));
        for (int j = 0; j<Players[i]->Worms.size(); j++) {
            this->addItem(Players[i]->Worms[j]->pointer);
            //if leveltype==sand
            auto it = currentLevel.begin()+(int)trunc(Players[i]->Worms[i]->pointer->pos().x());
            auto ite = it + Players[i]->Worms[i]->pointer->pixmap().width();
            MoveItem(Players[i]->Worms[j]->pointer,0,constants.height-*(std::max_element(it,ite))-Players[i]->Worms[i]->pointer->pixmap().height());
        }
    }
    currentPlayer=0;
    currentStep=0;
    QThread *b = new QThread;
    _Physic* p = new _Physic(this);
    p->moveToThread(b);
    p->connect(b,SIGNAL(started()),p,SLOT(Draw()));
    p->connect(p,SIGNAL(MoveItem(QGraphicsPixmapItem*, int, int)),this,SLOT(MoveItem(QGraphicsPixmapItem*, int, int)));
    b->start();

    //MoveItem(Items.Item.named.Highlight,5.3,0);

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
    int WeaponAmount = 9;
    int w = 0;
    while (WeaponAmount>>2 > w) w++;
    w++;
    w=w<<2;
    main->Inventory.clear();
    for (int i = 0; i<w; i++) {
        QGraphicsPixmapItem *n = new QGraphicsPixmapItem(QPixmap(QString("%1.png").arg(i)).scaled(QSize(50,50),Qt::KeepAspectRatio));
        n->setPos(QPointF((i%4)*50+main->constants.width-200,(i > 3 ? 50 : 0)));
        main->Inventory.push_back(n);
        emit AddItem(n);
    }
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
    QPixmap pm(200,100);
    pm.fill(Qt::transparent);
    QPainter p(&pm);
    p.setBrush(QImage(QString("inv.png")));
    p.setPen(Qt::transparent);
    p.drawRect(QRectF(0,0,200,100));
    p.end();
    QGraphicsPixmapItem* k = new QGraphicsPixmapItem(pm);
    k->setPos(400,0);
    this->addItem(k);
    QPixmap pm2(50,50);
    pm2.fill(Qt::transparent);
    QPainter p2(&pm2);
    p2.setBrush(QImage(QString("inv2.png")));
    p2.setPen(Qt::transparent);
    p2.drawRect(QRectF(0,0,50,50));
    p2.end();
    QGraphicsPixmapItem* h = new QGraphicsPixmapItem(pm2);
    h->setPos(400,0);
    //h->setPen(QColor(0,0,0,0)); h->setBrush(QImage(QString("inv2.png")));
    this->addItem(h);
    //QGraphicsScene::addRect(0,0,50,50);
    Items.Item.named.Inventory=k;
    Items.Item.named.Highlight=h;
    startGame(1,0,10);
    //std::this_thread::sleep_for(std::chrono::seconds(5));
    //MoveItem(h,50,0);*/
}

void _Logick::Draw() {
    bool invMove = true;
    while(true) {
        if (statuses.named.inInventory) {
            if (main->KeysPressed.Right()) {
                if (main->Items.Item.named.Highlight->pos().x()+50<main->constants.width) {
                    if (invMove) {
                        emit MoveItem(main->Items.Item.named.Highlight,50,0);
                        invMove=false;
                        std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); invMove=true;}).detach();
                    }
                }
            }
            if (main->KeysPressed.Left()) {
                if (main->Items.Item.named.Highlight->pos().x()>main->constants.width-200) {
                    if (invMove) {
                        emit MoveItem(main->Items.Item.named.Highlight,-50,0);
                        invMove=false;
                        std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); invMove=true;}).detach();
                    }
                }
            }
            if (main->KeysPressed.Down()) {
                if (main->Items.Item.named.Highlight->pos().y()==0) {
                    if (invMove) {
                        emit MoveItem(main->Items.Item.named.Highlight,0,50);
                        invMove=false;
                        std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); invMove=true;}).detach();
                    }
                } else {
                    if (invMove) {
                        if (main->Players[main->currentPlayer]->moveInventoryDown())
                        for (int i = 0; i<4; i++) {
                            emit MoveItem(main->Inventory[main->inventoryLayout+i],0,-50);
                        }
                        invMove=false;
                        std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); invMove=true;}).detach();
                    }
                }
            }
            if (main->KeysPressed.Up()) {
                if (main->Items.Item.named.Highlight->pos().y()==50) {
                    if (invMove) {
                        emit MoveItem(main->Items.Item.named.Highlight,0,-50);
                        invMove=false;
                        std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); invMove=true;}).detach();
                    }
                } else {
                    if (invMove) {
                        if (main->Players[main->currentPlayer]->moveInventoryUp())
                        for (int i = 0; i<4; i++) {
                            emit MoveItem(main->Inventory[main->inventoryLayout+4+i],0,50);
                        }
                        invMove=false;
                        std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); invMove=true;}).detach();
                    }
                }
            }
            if (main->KeysPressed.Inventory()||main->KeysPressed.Esc()) {
                if (invMove) {
                    main->Items.Item.named.Highlight->hide();
                    main->Items.Item.named.Inventory->hide();
                    main->Players[main->currentPlayer]->hideInventory();
                    invMove=false;
                    std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(250)); invMove=true;}).detach();
                    statuses.named.inInventory=false;
                }
            }
            if (main->KeysPressed.Use()) {
                statuses.named.inInventory=false;
                main->Items.Item.named.Highlight->hide();
                main->Items.Item.named.Inventory->hide();
                int num = (main->Items.Item.named.Highlight->pos().y()*4+(200-(main->constants.width - main->Items.Item.named.Highlight->pos().x())))/50;
                invMove=false;
                if (invMove) if (main->Players[main->currentPlayer]->getWeapon(num)) {statuses.named.shooting=true;}
                std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(250)); invMove=true;}).detach();
                main->Players[main->currentPlayer]->hideInventory();
            }
        continue;}
        if (statuses.named.inMenu) {

        continue;}
        if (statuses.named.shooting) {
            if (main->KeysPressed.Up()) {
                if (main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle>90) {
                    main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle-=0.1;
                } else main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle+=0.1;
            }
            if (main->KeysPressed.Down()) {
                if (main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle<90) {
                    main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle-=0.1;
                } else main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle+=0.1;
            }
            if (main->KeysPressed.Use()) {
                int id = main->Players[main->currentPlayer]->currentWorm;
                qreal velX; //=startVel*cos(angle);
                qreal velY; //=startVel*sin(angle);
                Weapon* weap;// = new Weapon(wepons[id]);
                //emit AddItem(weap->pointer);
                main->launched=weap;
            }

        continue;}
        {
            if (main->KeysPressed.Inventory()) {
                if (invMove) {
                    statuses.named.inInventory=true;
                    main->Items.Item.named.Highlight->show();
                    main->Items.Item.named.Inventory->show();
                    main->Players[main->currentPlayer]->showInventory();
                    invMove=false;
                    std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(250)); invMove=true;}).detach();
                }
            }
            if (main->KeysPressed.Right()) {
                qreal *velX = &(main->Players[main->currentPlayer]->Worms[(main->currentStep)%(main->Players[main->currentStep]->Worms.size())]->velocityX);
                qreal *velY = &(main->Players[main->currentPlayer]->Worms[(main->currentStep)%(main->Players[main->currentStep]->Worms.size())]->velocityY);
                qreal vel=*velY * *velY + *velX * *velX;
                if (vel<1) {
                    int fps = main->constants.FPS;
                    *velX+=50/fps;
                    ///todo ONGROUND
                    //std::thread([velX,fps](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); if ((*velX>0)) *velX-=50/fps;}).detach();
                }
            }
            if (main->KeysPressed.Left()) {
                qreal *velX = &(main->Players[main->currentPlayer]->Worms[(main->currentStep)%(main->Players[main->currentStep]->Worms.size())]->velocityX);
                qreal *velY = &(main->Players[main->currentPlayer]->Worms[(main->currentStep)%(main->Players[main->currentStep]->Worms.size())]->velocityY);
                qreal vel=*velY * *velY + *velX * *velX;
                if (vel<1) {
                    int fps = main->constants.FPS;
                    *velX-=50/fps;
                    ///todo ONGROUND
                    //std::thread([velX,fps](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); if ((*velX<0)) *velX+=50/fps;}).detach();
                }
            }
            if (main->KeysPressed.Jump()) {
                qreal *velY = &(main->Players[main->currentPlayer]->Worms[(main->currentStep)%(main->Players[main->currentStep]->Worms.size())]->velocityY);
                ///todo ONGROUND
                auto it = main->currentLevel.begin() + (int)trunc(main->Players[main->currentPlayer]->Worms[(main->currentStep)%(main->Players[main->currentStep]->Worms.size())]->pointer->pos().x());
                auto ite = it+50;

                int maxLevel = *(std::max_element(it,ite));
                if (main->Players[main->currentPlayer]->Worms[(main->currentStep)%(main->Players[main->currentStep]->Worms.size())]->pointer->pos().y()+55>main->constants.height-maxLevel) {
                    *velY = -main->constants.gravity/2;
                }
                //*velY = (1 > abs(*velY) ? -5 : *velY);
            }
        }
    }
}

void MainWindow::MoveItem(QGraphicsPixmapItem* item, int mX, int mY) {
    if (mX>0) {
    item->setPos(std::min(item->pos().x()+mX,(double)(constants.width-item->pixmap().width())),
                  item->pos().y()+mY
                  );
    } else {
        item->setPos(std::max(item->pos().x()+mX,(double)0),
                      item->pos().y()+mY
                      );
    }
    //qDebug() << "Item new rect: " << item->rect();*/
}

void MainWindow::RemoveItem(QGraphicsItem *item) {
    this->RemoveItem(item);
}

void MainWindow::AddItem(QPixmap map, QPen pen, QBrush brush) {
    QPainter p(&map);
    p.setPen(pen);
    p.setBrush(brush);
    p.drawRect(0,0,map.width(),map.height());
    p.end();
    QGraphicsPixmapItem* k = new QGraphicsPixmapItem(map);
    //k->setPen(pen); k->setBrush(brush);
    //launched=k;
}

Player::Player(int w): currentWorm(0), Inventory(20,0) {
    for (int i = 0; i < 5; i++) {
        Worms.push_back(new Worm(w));
    }
}

Worm::Worm(int w): angle(0), velocityX(0), velocityY(0), hp(1000) {
    QPoint pos = QPoint(rand()%(w-50),0);
    //QPixmap pm(50,50);
    //pm.fill(Qt::transparent);
    //QPainter p(&pm);
    //p.setPen(Qt::transparent);
    //p.setBrush(QBrush(QImage(QString("wm.png"))));
    //p.drawRect(QRectF(0,0,50,50));
    //p.end();
    pointer = new QGraphicsPixmapItem(QPixmap(QString("wm.png")).scaled(QSize(50,50),Qt::KeepAspectRatio));
    pointer->setPos(pos);
    //QRect(rand()%(w-50),0,50,50);
    //pointer = new QGraphicsPixmapItem(pos);
    //pointer->setBrush(QBrush(QPixmap(QString("wm.png")).scaled(QSize(50,50),Qt::KeepAspectRatio)));

    //pointer->setPen(QPen(QColor(0,0,0,0)));*/
}

void _Physic::Draw() {
    int FPS=main->constants.FPS;
    while (true) {
        //time_t a = time(NULL);
        std::thread th([FPS](){std::this_thread::sleep_for(std::chrono::milliseconds(1000/FPS));});
        //gravity
        for(int i = 0; i<main->constants.playersCount; i++) {
            for (int j = 0; j<main->Players[i]->Worms.size(); j++) {
                main->Players[i]->Worms[j]->velocityY+=((double)main->constants.gravity)/FPS;
            }
        }
        if (main->launched) {
            main->launched->velocityY+=((double)main->constants.gravity)/FPS;
            if ((main->launched->isBanana)&&(main->launched->bananed)) {
                for (int i = 0; i<main->launched->bananaChilds.size(); i++) {
                    main->launched->bananaChilds[i]->velocityY+=((double)main->constants.gravity)/FPS;
                }
            }
        }
        //move
        for(int i = 0; i<main->constants.playersCount; i++) {
            for (int j = 0; j<main->Players[i]->Worms.size(); j++) {
                emit MoveItem(main->Players[i]->Worms[j]->pointer,main->Players[i]->Worms[j]->velocityX,main->Players[i]->Worms[j]->velocityY);
                /*if (main->Players[i]->Worms[j]->pointer->rect().x()>main->constants.width-50) {
                    main->Players[i]->Worms[j]->velocityX=0;
                    emit MoveItem(main->Players[i]->Worms[j]->pointer,600 - 50 - main->Players[i]->Worms[j]->pointer->rect().x(),0);
                    //std::this_thread::sleep_for(std::chrono::milliseconds(200));
                }
                if (main->Players[i]->Worms[j]->pointer->rect().x()<0) {
                    main->Players[i]->Worms[j]->velocityX=0;
                    emit MoveItem(main->Players[i]->Worms[j]->pointer,0-main->Players[i]->Worms[j]->pointer->rect().x(),0);
                }*/
                auto it = main->currentLevel.begin() + (int)trunc(main->Players[i]->Worms[i]->pointer->pos().x());
                auto ite = it+50;

                int maxLevel = *(std::max_element(it,ite)); //,[](int a, int b){return a>b;}));


                if (main->Players[i]->Worms[j]->pointer->pos().y()+50 > main->constants.height - maxLevel) {
                    emit MoveItem(main->Players[i]->Worms[j]->pointer,0,(main->constants.height-maxLevel)-(main->Players[i]->Worms[j]->pointer->pos().y()+50));
                    if (main->Players[i]->Worms[j]->velocityY>JUMP_VELOCITY*2) main->Players[i]->Worms[j]->damaged(trunc(main->Players[i]->Worms[j]->velocityY));
                    //main->Players[i]->Worms[j]->velocityX=std::max((double)0,main->Players[i]->Worms[j]->velocityX-main->Players[i]->Worms[j]->velocityY);
                    if (main->Players[i]->Worms[j]->velocityY>JUMP_VELOCITY) main->Players[i]->Worms[j]->velocityX=0;
                    main->Players[i]->Worms[j]->velocityY=0;
                }
            }
        }
        //todo : move
        if (main->launched) {
            main->launched->velocityY+=((double)main->constants.gravity)/FPS;
            if ((main->launched->isBanana)&&(main->launched->bananed)) {
                for (int i = 0; i<main->launched->bananaChilds.size(); i++) {
                    main->launched->bananaChilds[i]->velocityY+=((double)main->constants.gravity)/FPS;
                }
            }
        }

        th.join();
    }
}

void Player::showInventory() {
    if (Worms.empty()) return;
    QGraphicsScene* scene = Worms.front()->pointer->scene();
    if (!scene) return;
    QVector<QGraphicsPixmapItem*> *pointers = &((MainWindow*)scene)->Inventory;
    int *inventoryLayout=&((MainWindow*)scene)->inventoryLayout;
    for (int i = 0; i< 8; i++) {
        pointers->at(*inventoryLayout+i)->show();
    }
}
void Player::hideInventory() {
    if (Worms.empty()) return;
    QGraphicsScene* scene = Worms.front()->pointer->scene();
    if (!scene) return;
    QVector<QGraphicsPixmapItem*> *pointers = &((MainWindow*)scene)->Inventory;
    int *inventoryLayout=&((MainWindow*)scene)->inventoryLayout;
    for (int i = 0; i< 8; i++) {
        pointers->at(*inventoryLayout+i)->hide();
    }
}
bool Player::moveInventoryUp() {
    if (Worms.empty()) return false;
    QGraphicsScene* scene = Worms.front()->pointer->scene();
    if (!scene) return false;
    QVector<QGraphicsPixmapItem*> *pointers = &((MainWindow*)scene)->Inventory;
    int *inventoryLayout=&((MainWindow*)scene)->inventoryLayout;
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
    QVector<QGraphicsPixmapItem*> *pointers = &((MainWindow*)scene)->Inventory;
    int *inventoryLayout=&((MainWindow*)scene)->inventoryLayout;
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
    QGraphicsScene* scene = Worms.front()->pointer->scene();
    if (!scene) return false;
    int *inventoryLayout=&((MainWindow*)scene)->inventoryLayout;
    if (Inventory[*inventoryLayout+a]>0) {
        Inventory[*inventoryLayout+a]-=1;
        return true;
    }
    return false;
}
void Worm::damaged(int a) {
    hp-=a;
    if (hp<=0) {
        QVector<Worm*> *Worms = &(((MainWindow*)(pointer->scene()))->Players[((MainWindow*)(pointer->scene()))->currentPlayer]->Worms);
        Worms->erase(Worms->begin()+(((MainWindow*)(pointer->scene()))->currentStep)%Worms->size());
        pointer->scene()->removeItem(pointer); //?!!
    }
}
void MainWindow::AddItem(QGraphicsItem *item) {
    addItem(item);
}
