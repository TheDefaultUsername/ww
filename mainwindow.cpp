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

    //qDebug()<<event->key()<<" "<<event->nativeVirtualKey()<<" "<<Keys.Use;
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
    p->connect(p,SIGNAL(AddItem(QGraphicsItem*)),this,SLOT(AddItem(QGraphicsItem*)));
    p->connect(p,SIGNAL(RemoveItem(QGraphicsItem*)),this,SLOT(RemoveItem(QGraphicsItem*)));
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
    main->Keys.Use=Qt::Key_Return;//Qt::Key_Enter; //its magic, harry
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
    //this->addRect(QRect(0,250,600,50),QPen(Qt::transparent),QBrush(Qt::blue));
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
                if (invMove) if (main->Players[main->currentPlayer]->getWeapon(num)) {statuses.named.shooting=true; emit AddItem(main->Items.Item.named.Scope);}
                invMove=false;
                std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(250)); invMove=true;}).detach();
                main->Players[main->currentPlayer]->hideInventory();
            }
        continue;}
        if (statuses.named.inMenu) {

        continue;}
        if (statuses.named.shooting) {
            if (main->KeysPressed.Up()&&invMove) {
                if (main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle>90) {
                    main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle-=0.1;
                } else main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle+=0.1;
                invMove=false;
                std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(5)); invMove=true;}).detach();
            }
            if (main->KeysPressed.Down()&&invMove) {
                if (main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle<90) {
                    main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle-=0.1;
                } else main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle+=0.1;
                invMove=false;
                std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(5)); invMove=true;}).detach();
            }
            if (main->KeysPressed.Right()&&invMove) {
                main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle=135;
                invMove=false;
                std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(5)); invMove=true;}).detach();
            }
            if (main->KeysPressed.Left()&&invMove) {
                main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle=45;
                invMove=false;
                std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(5)); invMove=true;}).detach();
            }
            if (!invMove)
            {
                qreal angle = main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle;
                if (angle<-45) main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle=-45;
                if (angle>225) main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle=225;
                QPointF poS = main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->pointer->pos();
                emit SetLine(poS.x()+25,poS.y()+25,poS.x()+25-50*cos(angle/180*3.14),poS.y()+25-50*sin(angle/180*3.14));
            //main->Items.Item.named.Scope->line().setP2(QPointF(main->Items.Item.named.Scope->line().p1().x() - 50*cos(angle/*angle/180*3.14*/)
                                                              // ,main->Items.Item.named.Scope->line().p1().y()/* - 50*sin(angle/180*3.14)*/));
            //qDebug()<<angle<<"\t"<<main->Items.Item.named.Scope->line();
            }

            if (main->KeysPressed.Use()&&invMove) {
                int id = main->Players[main->currentPlayer]->currentWorm;
                qreal velX = -10*cos(main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle/180*3.14); //=startVel*cos(angle);
                qreal velY = -10*sin(main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle/180*3.14); //=startVel*sin(angle);
                Weapon* weap = new Weapon(false,false,velX,velY,1,5,0);// = new Weapon(wepons[id]);
                weap->pointer=new QGraphicsPixmapItem(QPixmap(main->Inventory[id]->pixmap()));
                weap->pointer->setPos(main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->pointer->pos());
                emit AddItem(weap->pointer);
                main->launched=weap;
                invMove=false;
                std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(1000)); invMove=true;}).detach();
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
    //delete(item);
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
    for (int i = 0; i < 6; i++) {
        Worms.push_back(new Worm(w));
    }
    Inventory[0]=1;
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
            if (!main->launched->bananed) {
                emit MoveItem(main->launched->pointer,main->launched->velocityX,main->launched->velocityY);
                //if (main->launched->pointer->collidesWithItem(main->Players[0]->Worms[0]->pointer)) {}
                /*if (main->launched->pointer->collidingItems().size()) {
                QList<QGraphicsItem*> coll = main->launched->pointer->collidingItems();
                for (int i = 0; i<coll.size(); i++) {
                    if (coll[i]!=main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->pointer) {
                        main->launched->detonate();
                    }
                }
                }*/
                for(int i = 0; i<main->constants.playersCount; i++)
                    for (int j = 0; j<main->Players[i]->Worms.size(); j++) {
                    QGraphicsItem *pointer = main->Players[i]->Worms[j]->pointer;
                    //if (pointer!=main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->pointer)
                        if (main->launched->pointer->collidesWithItem(pointer))
                        {QGraphicsItem* pointer = main->launched->detonate(); if (pointer) {emit RemoveItem(pointer); main->launched=NULL;}}
                }
                if (main->launched) {
                    auto it = main->currentLevel.begin() + (int)trunc(main->launched->pointer->pos().x());
                    auto ite = it+50;
                    int maxLevel = *(std::max_element(it,ite));
                    if (main->launched->pointer->pos().y()+50>main->constants.height-maxLevel) {QGraphicsItem* pointer = main->launched->detonate(); if (pointer) {emit RemoveItem(pointer); main->launched=NULL;}}
                }
            }
            if (main->launched) if ((main->launched->isBanana)&&(main->launched->bananed)) {
                for (int i = 0; i<main->launched->bananaChilds.size(); i++) {
                    emit MoveItem(main->launched->bananaChilds[i]->pointer,main->launched->bananaChilds[i]->velocityX,main->launched->bananaChilds[i]->velocityY);
                /*if (main->launched->pointer->collidingItems().size()) {
                    QList<QGraphicsItem*> coll = main->launched->pointer->collidingItems();
                    for (int j = 0; j<coll.size(); j++) {
                        if (coll[j]!=main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->pointer) {
                            main->launched->detonate();
                        }
                    }
                }*/
                for(int k = 0; k<main->constants.playersCount; k++)
                    for (int j = 0; j<main->Players[k]->Worms.size(); j++) {
                        QGraphicsItem *pointer = main->Players[k]->Worms[j]->pointer;
                        //if (pointer!=main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->pointer)
                        if (main->launched->bananaChilds[i]->pointer->collidesWithItem(pointer))
                           {QGraphicsItem* pointer = main->launched->bananaChilds[i]->detonate(); if (pointer) {emit RemoveItem(pointer); main->launched=NULL;}}
                }
                if (main->launched) {
                    auto it = main->currentLevel.begin() + (int)trunc(main->launched->bananaChilds[i]->pointer->pos().x());
                    auto ite = it+50;
                    int maxLevel = *(std::max_element(it,ite));
                    if (main->launched->bananaChilds[i]->pointer->pos().y()+50>maxLevel) {QGraphicsItem* pointer = main->launched->bananaChilds[i]->detonate(); if (pointer) {emit RemoveItem(pointer); main->launched=NULL;}}
                }
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
    MainWindow* scene = (MainWindow*)Worms.front()->pointer->scene();
    if (!scene) return false;
    int *inventoryLayout=&(scene->inventoryLayout);
    if (Inventory[*inventoryLayout+a]>0) {
        Inventory[*inventoryLayout+a]-=1;
        currentWorm=*inventoryLayout + a;
        scene->Items.Item.named.Scope=new QGraphicsLineItem(
                    Worms[scene->currentStep%Worms.size()]->pointer->pos().x()+25,
                    Worms[scene->currentStep%Worms.size()]->pointer->pos().y()+25,
                    Worms[scene->currentStep%Worms.size()]->pointer->pos().x()+25 - 50*sin(Worms[scene->currentStep%Worms.size()]->angle),
                    Worms[scene->currentStep%Worms.size()]->pointer->pos().x()+25 - 50*cos(Worms[scene->currentStep%Worms.size()]->angle)
                    );
        QPen pen;
        pen.setDashPattern(QVector<qreal>(2,2));
        ((MainWindow*)scene)->Items.Item.named.Scope->setPen(pen);
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
void MainWindow::SetLine(qreal x1,qreal x2,qreal x3,qreal x4) {
    Items.Item.named.Scope->setLine(x1,x2,x3,x4);
}
QGraphicsItem* Weapon::detonate() {
    MainWindow* scene = (MainWindow*)(pointer->scene());
    if (isSpecific) {

    } else {
        //scene->launched=NULL;
        //velocityX=0;
        //velocityY=0;
        QVector<Worm*> vec;
        for (int i = 0; i<radius*2; i++)
            for (int j = 0; j<radius*2; j++) {
                QPointF pos(pointer->pos().x()-radius+i,pointer->pos().y()-radius+j);
                //if (pos.y()>scene->constants.height-scene->currentLevel[((int)pos.x())%scene->constants.width ]) scene->currentLevel[((int)pos.x())%scene->constants.width]-=1;
                if (sqrt((pointer->pos().x()-radius+i)*(pointer->pos().x()-radius+i)+(pointer->pos().y()-radius+j)*(pointer->pos().y()-radius+j))<radius) {
                    scene->addRect(pointer->pos().x()-radius+i,pointer->pos().y()-radius+j,1,1,QPen(Qt::transparent),QBrush(scene->backgroundBrush()));
                    for (int k = 0; k<scene->constants.playersCount; k++)
                        for (int t = 0; t<scene->Players[k]->Worms.size(); t++) {
                            if ((pos.x()>=scene->Players[k]->Worms[t]->pointer->pos().x())&&(pos.y()>=scene->Players[k]->Worms[t]->pointer->pos().y())
                                &&(pos.x()<=scene->Players[k]->Worms[t]->pointer->pos().x()+50)&&(pos.y()<=scene->Players[k]->Worms[t]->pointer->pos().y()+50))
                            {
                                bool flag = true;
                                for (int m = 0; m<vec.size(); m++) {
                                    if (vec[m]==scene->Players[k]->Worms[t]) flag = false;
                                }
                                if (flag) vec.append(scene->Players[k]->Worms[t]);
                            }
                        }
                }
            }
        for (int m = 0; m<vec.size(); m++) {
            vec[m]->damaged(damage);
        }
        //scene->addRect();
        return pointer;
    }
    return NULL;
}
