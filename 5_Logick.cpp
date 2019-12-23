#include "5_Logick.h"
#include <thread>
#include <chrono>
#include <cmath>
#include <QFile>

#include <QDebug>

#define JUMP_VELOCITY 10
#define DEFAULT_GRAVITY 10

void _Load::Load() {
    ///std::this_thread::sleep_for(std::chrono::seconds(5));
    //((QGraphicsRectItem*)(main->items()[0]))->setRect(QRect(0,0,200,100));
    /*std::this_thread::sleep_for(std::chrono::seconds(5));
    QGraphicsRectItem k(QRect(400,0,200,100));
    k.setPen(QColor(0,0,0,0)); k.setBrush(QImage(QString("inv.png")));
    this->main->addItem(&k);
    std::this_thread::sleep_for(std::chrono::seconds(15));*/
    QFile weap("src/weap.txt");
    weap.open(QFile::ReadOnly);
    int WeaponAmount = QString(weap.readLine()).toInt();
    int w = 0;
    main->currentStep=WeaponAmount;
    while (WeaponAmount>>2 > w) w++;
    w++;
    w=w<<2;
    main->currentPlayer=w;
    main->Inventory.clear();
    for (int i = 0; i<w; i++) {
        QGraphicsPixmapItem *n = new QGraphicsPixmapItem(QPixmap(QString("src/%1.png").arg(i)).scaled(QSize(50,50)));
        n->setPos(QPointF((i%4)*50+main->constants.width-200,(i > 3 ? 50 : 0)));
        main->Inventory.push_back(n);
        emit AddItem(n);
        n->hide();
    }
    for (int i = 0; i<WeaponAmount; i++) {
        main->inv.weapons.append(Weapon(
                                     QString(weap.readLine()).at(0)=='t',
                                     QString(weap.readLine()).at(0)=='t',
                                     QString(weap.readLine()).toDouble(),
                                     QString(weap.readLine()).toDouble(),
                                     QString(weap.readLine()).toInt(),
                                     QString(weap.readLine()).toInt(),
                                     QString(weap.readLine()).toInt()
                                     ));
        main->inv.WeapIm.append(new QGraphicsPixmapItem(QPixmap(QString("src/%1_.png").arg(i)).scaled(QSize(50,50))));
    }
    weap.close();
    QFile key(QString("src/keys.txt"));
    key.open(QFile::ReadOnly);
    main->Keys.Right=QString(key.readLine()).toInt();
    main->Keys.Left=QString(key.readLine()).toInt();
    main->Keys.Up=QString(key.readLine()).toInt();
    main->Keys.Down=QString(key.readLine()).toInt();
    main->Keys.Esc=QString(key.readLine()).toInt();
    main->Keys.Use=QString(key.readLine()).toInt();
    main->Keys.Inventory=QString(key.readLine()).toInt();
    main->Keys.Jump=QString(key.readLine()).toInt();
    emit stopped();
}

void _Logick::Draw() {
    bool invMove = true;
    while(true) {
        //qDebug()<<"statuses"<<statuses.named.inMenu<<statuses.named.shooting<<statuses.named.inInventory;
        if (statuses.named.inInventory) {
            if (main->KeysPressed.Right()) {
                if (main->Item.named.Highlight->pos().x()+50<main->constants.width) {
                    if (invMove) {
                        emit MoveItem(main->Item.named.Highlight,50,0);
                        invMove=false;
                        std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); invMove=true;}).detach();
                    }
                }
            }
            if (main->KeysPressed.Left()) {
                if (main->Item.named.Highlight->pos().x()>main->constants.width-200) {
                    if (invMove) {
                        emit MoveItem(main->Item.named.Highlight,-50,0);
                        invMove=false;
                        std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); invMove=true;}).detach();
                    }
                }
            }
            if (main->KeysPressed.Down()) {
                if (main->Item.named.Highlight->pos().y()==0) {
                    if (invMove) {
                        emit MoveItem(main->Item.named.Highlight,0,50);
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
                if (main->Item.named.Highlight->pos().y()==50) {
                    if (invMove) {
                        emit MoveItem(main->Item.named.Highlight,0,-50);
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
                    main->Item.named.Highlight->hide();
                    main->Item.named.Inventory->hide();
                    main->Players[main->currentPlayer]->hideInventory();
                    invMove=false;
                    std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(250)); invMove=true;}).detach();
                    statuses.named.inInventory=false;
                }
            }
            if (main->KeysPressed.Use()) {
                statuses.named.inInventory=false;
                main->Item.named.Highlight->hide();
                main->Item.named.Inventory->hide();
                int num = (main->Item.named.Highlight->pos().y()*4+(200-(main->constants.width - main->Item.named.Highlight->pos().x())))/50;
                if (invMove) if (main->Players[main->currentPlayer]->getWeapon(num)) {statuses.named.shooting=true; emit AddItem(main->Item.named.Scope);}
                invMove=false;
                std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(250)); invMove=true;}).detach();
                main->Players[main->currentPlayer]->hideInventory();
            }
        continue;}
        if (statuses.named.inMenu) {
            if (main->KeysPressed.Up()&&invMove) {
                menu->MoveUp();
                invMove=false;
                std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(250)); invMove=true;}).detach();
            }
            if (main->KeysPressed.Down()&&invMove) {
                menu->MoveDown();
                invMove=false;
                std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(250)); invMove=true;}).detach();
            }
            if (main->KeysPressed.Use()&&invMove) {
                if(menu->accept()) {
                    statuses.named.inMenu=false;
                    emit startGame(menu->playeramount,(menu->isLevelSand? &(menu->level) : new QVector<int>(600,100)),menu->gravity);
                    menu->hide();
                }
                invMove=false;
                std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(250)); invMove=true;}).detach();
            }
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
                qreal velX = -main->constants.gravity*cos(main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle/180*3.14); //=startVel*cos(angle);
                qreal velY = -main->constants.gravity*sin(main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()]->angle/180*3.14); //=startVel*sin(angle);
                Weapon* weap = new Weapon(main->inv.weapons[id]);//new Weapon(false,false,velX,velY,1,5,0);// = new Weapon(wepons[id]);
                weap->velocityX=velX;
                weap->velocityY=velY;
                weap->creator=main->Players[main->currentPlayer]->Worms[main->currentStep%main->Players[main->currentPlayer]->Worms.size()];
                weap->pointer=  new QGraphicsPixmapItem(main->inv.WeapIm[id]->pixmap());
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
                    main->Item.named.Highlight->show();
                    main->Item.named.Inventory->show();
                    main->Players[main->currentPlayer]->showInventory();
                    invMove=false;
                    std::thread([&invMove](){std::this_thread::sleep_for(std::chrono::milliseconds(250)); invMove=true;}).detach();
                }
            }
            if (main->KeysPressed.Right()) {
                qreal *velX = &(main->Players[main->currentPlayer]->Worms[(main->currentStep)%(main->Players[main->currentStep]->Worms.size())]->velocityX);
                bool *onG = &(main->Players[main->currentPlayer]->Worms[(main->currentStep)%(main->Players[main->currentStep]->Worms.size())]->onGround);
                if (*onG) {
                    int fps = main->constants.FPS;
                    *velX+=50/fps;
                    *onG=false;
                    std::thread([velX,onG](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); while(!*onG) {} *velX=0;}).detach();
                }
            }
            if (main->KeysPressed.Left()) {
                qreal *velX = &(main->Players[main->currentPlayer]->Worms[(main->currentStep)%(main->Players[main->currentStep]->Worms.size())]->velocityX);
                bool *onG = &(main->Players[main->currentPlayer]->Worms[(main->currentStep)%(main->Players[main->currentStep]->Worms.size())]->onGround);
                if (*onG) {
                    int fps = main->constants.FPS;
                    *velX-=50/fps;
                    *onG=false;
                    std::thread([velX,onG](){std::this_thread::sleep_for(std::chrono::milliseconds(100)); while(!*onG) {} *velX=0;}).detach();
                }
            }
            if (main->KeysPressed.Jump()) {
                qreal *velY = &(main->Players[main->currentPlayer]->Worms[(main->currentStep)%(main->Players[main->currentStep]->Worms.size())]->velocityY);
                bool *onGV = &(main->Players[main->currentPlayer]->Worms[(main->currentStep)%(main->Players[main->currentStep]->Worms.size())]->onGroundV);
                //auto it = main->currentLevel.begin() + (int)trunc(main->Players[main->currentPlayer]->Worms[(main->currentStep)%(main->Players[main->currentStep]->Worms.size())]->pointer->pos().x());
                //auto ite = it+50;

                //int maxLevel = *(std::max_element(it,ite));
                if (*onGV) {
                    *velY = -JUMP_VELOCITY;
                    *onGV=false;
                }
                //*velY = (1 > abs(*velY) ? -5 : *velY);
            }
            if (main->KeysPressed.Esc()) {
                menu->show();
                statuses.named.inMenu=true;
            }
        }
    }
}

void _Physic::Draw() {
    int FPS=main->constants.FPS;
    while (true) {
        //time_t a = time(NULL);
        std::thread th([FPS](){std::this_thread::sleep_for(std::chrono::milliseconds(1000/FPS));});
        //gravity
        for(int i = 0; i<main->constants.playersCount; i++) {
            for (int j = 0; j<main->Players[i]->Worms.size(); j++) {
                if (!main->Players[i]->Worms[j]->onGround)
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

                auto it = main->currentLevel.begin() + (int)trunc(main->Players[i]->Worms[j]->pointer->pos().x());
                auto ite = it+50;

                int maxLevel = *(std::max_element(it,ite)); //,[](int a, int b){return a>b;}));


                if (main->Players[i]->Worms[j]->pointer->pos().y()+50 > main->constants.height - maxLevel) {
                    main->Players[i]->Worms[j]->onGround=true;
                    main->Players[i]->Worms[j]->onGroundV=true;
                    emit MoveItem(main->Players[i]->Worms[j]->pointer,0,(main->constants.height-maxLevel)-(main->Players[i]->Worms[j]->pointer->pos().y()+50));
                    if (main->Players[i]->Worms[j]->velocityY>JUMP_VELOCITY*2) main->Players[i]->Worms[j]->damaged(trunc(main->Players[i]->Worms[j]->velocityY));
                    if (main->Players[i]->Worms[j]->velocityY>JUMP_VELOCITY) main->Players[i]->Worms[j]->velocityX=0;
                    main->Players[i]->Worms[j]->velocityY=0;
                }
            }
        }
        //todo : move
        if (main->launched) {
            if (!main->launched->bananed) {
                emit MoveItem(main->launched->pointer,main->launched->velocityX,main->launched->velocityY);
                for(int i = 0; i<main->constants.playersCount; i++)
                    for (int j = 0; (j<main->Players[i]->Worms.size())&&(main->launched); j++) {
                    QGraphicsItem *pointer = main->Players[i]->Worms[j]->pointer;
                        if (((void*)pointer)!=main->launched->creator)
                        if (main->launched->pointer->collidesWithItem(pointer))
                        {QGraphicsItem* Wpointer = main->launched->detonate(); if (Wpointer) {emit RemoveItem(Wpointer); main->launched=NULL;}}
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
                for(int k = 0; k<main->constants.playersCount; k++)
                    for (int j = 0; j<main->Players[k]->Worms.size(); j++) {
                        QGraphicsItem *pointer = main->Players[k]->Worms[j]->pointer;
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

void Menu::MoveUp() {
    //qDebug()<<"su";
    if (!current_action) return;
    current_action--;
    //qDebug()<<"u";
    emit MoveItem(buttons[5],0,-55);
}
void Menu::MoveDown() {
    //qDebug()<<"sd";
    //play
    //gravity
    //playeramount
    //level
    if (current_action==4) return;
    current_action++;
    //qDebug()<<"d";
    emit MoveItem(buttons[5],0,55);
}
void Menu::show() {
    for (int i = 0; i<5; i++) {
        texts[i]->show();
        buttons[i]->show();
    }
    buttons[5]->show();
}
void Menu::hide() {
    for (int i = 0; i<5; i++) {
        texts[i]->hide();
        buttons[i]->hide();
    }
    buttons[5]->hide();
}
bool Menu::accept() {
    if (current_action==4) exit(0);
    if (current_action==2) {
        if ((gravity>0)&&(gravity<100)) {gravity++;} else {gravity=1;}
        emit SetPlainText(texts[2],QString("Gravity %1").arg(gravity));
    }
    if (current_action==3) {
        if ((playeramount>1)&&(playeramount<5)) {playeramount++;} else {playeramount=2;}
        emit SetPlainText(texts[3],QString("Players %1").arg(playeramount));
    }
    if (current_action==1) {
        if (isLevelSand) {
            emit SetPlainText(texts[1],QString("Level flat"));
        } else {
            emit SetPlainText(texts[1],QString("Level loaded"));
        }
        isLevelSand=!isLevelSand;
    }
    if (current_action==0)
        if ((playeramount>=2)&&(playeramount<=5))
            if ((gravity>0)&&(gravity<=100))
                return true;
    return false;
}

Menu::Menu(MainWindow* m): main(m) {
    texts.append(new QGraphicsTextItem(QString("Start Game")));
    texts.append(new QGraphicsTextItem(QString("Level")));
    texts.append(new QGraphicsTextItem(QString("Gravity")));
    texts.append(new QGraphicsTextItem(QString("Players")));
    texts.append(new QGraphicsTextItem(QString("Exit")));

    for (int i = 0; i<5; i++) {
        buttons.append(new QGraphicsPixmapItem(QPixmap(QString("src/but.png")).scaled(QSize(200,50))));
        buttons[i]->setPos(200,i*55);
        texts[i]->setPos(200,i*55);
        texts[i]->setFont(QFont(QFont().defaultFamily(),30));
        main->addItem(texts[i]);
        main->addItem(buttons[i]);
    }
    buttons.append(new QGraphicsPixmapItem(QPixmap(QString("src/inv4.png")).scaled(QSize(200,50))));
    buttons[5]->setPos(200,0);
    main->addItem(buttons[5]);
    current_action=0;
    QFile f(QString("src/lvl.txt"));
    f.open(QFileDevice::ReadOnly);
    for (int i = 0; i<600; i++) {
        level.append(QString(f.readLine()).toInt());
    }
    f.close();
}
