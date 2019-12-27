#include "5_Logick.h"
#include <QThread>
#include <cmath>
#include <QPainter>


void MainScene::AddItem(QGraphicsItem *item) {
    addItem(item);
}
void MainScene::SetLine(qreal x1,qreal x2,qreal x3,qreal x4) {
    Item.named.Scope->setLine(x1,x2,x3,x4);
}

void MainScene::keyPressEvent(QKeyEvent *event) {
    if (event->nativeVirtualKey()==Keys.Inventory) KeysPressed.sInventory(true);
    if (event->key()==Keys.Right) KeysPressed.sRight(true);
    if (event->key()==Keys.Left) KeysPressed.sLeft(true);
    if (event->key()==Keys.Up) KeysPressed.sUp(true);
    if (event->key()==Keys.Down) KeysPressed.sDown(true);
    if (event->key()==Keys.Jump) KeysPressed.sJump(true);
    if (event->key()==Keys.Use)/*||(event->key()==Qt::Key_Enter))*/ KeysPressed.sUse(true);
    if (event->key()==Keys.Esc) KeysPressed.sEsc(true);

    //qDebug()<<event->key()<<" "<<event->nativeVirtualKey()<<" "<<Keys.Use;
}

void MainScene::keyReleaseEvent(QKeyEvent *event) {
    if (event->nativeVirtualKey()==Keys.Inventory) KeysPressed.sInventory(false);
    if (event->key()==Keys.Right) KeysPressed.sRight(false);
    if (event->key()==Keys.Left) KeysPressed.sLeft(false);
    if (event->key()==Keys.Up) KeysPressed.sUp(false);
    if (event->key()==Keys.Down) KeysPressed.sDown(false);
    if (event->key()==Keys.Jump) KeysPressed.sJump(false);
    if (event->key()==Keys.Use) KeysPressed.sUse(false);
    if (event->key()==Keys.Esc) KeysPressed.sEsc(false);
}

MainScene::~MainScene()
{
}

void MainScene::startGame(int playerAmount,QVector<int>* level, int gravity) {
    //this->clear();
    //this->setBackgroundBrush(QColor(128,192,255,255));
    inventoryLayout=0;
    ///currentLevel=Levels[level];
    constants.playersCount=playerAmount;
    curPlC=playerAmount;
    //currentLevel=*level;
    addRect(0,300,600,100,QPen(Qt::transparent),QBrush(QColor(128,192,255,255)));
    for (int i = 0; i<level->size(); i++) {
        currentLevel.append(new QGraphicsRectItem(QRect(/*i,400-level->at(i)*/0,0,1,level->at(i))));
        currentLevel[i]->setPos(i,400-level->at(i));
        currentLevel[i]->setPen(QPen(QColor(0,0,0,0)));
        currentLevel[i]->setBrush(QBrush(QColor(150,75,0,255)));
        addItem(currentLevel[i]);
    }
    QGraphicsRectItem* water = new QGraphicsRectItem(0,/*constants.height*/0,constants.width,constants.height);
    water->setPen(QPen(Qt::transparent));
    water->setBrush(QBrush(Qt::blue));
    water->setPos(0,constants.height);
    addItem(water);
    Item.named.Water=water;
    this->constants.gravity=gravity;
    //MoveItem(Item.named.Water,0,-40);
    Players.clear();
    for (int i = 0; i<playerAmount; i++) {
        Players.push_back(new Player(constants.width));
        Players[i]->Inventory=QVector<int>(currentPlayer,5);
        for (int k = currentStep; k<currentPlayer; k++) Players[i]->Inventory[k]=0;
        for (int j = 0; j<Players[i]->Worms.size(); j++) {
            QPixmap pm = Players[i]->Worms[j]->pointer->pixmap();
            QPainter pa(&pm);
            pa.setBrush(QBrush(QColor(i%3 * 120 + 15, i%5 * 50 + 55, i%2 * 100 + 155, 255)));
            pa.setPen(QPen(Qt::transparent));
            pa.drawRect(0,0,50,5);
            pa.end();
            Players[i]->Worms[j]->pointer->setPixmap(pm);
            this->addItem(Players[i]->Worms[j]->pointer);
            connect(Players[i]->Worms[j],SIGNAL(NextStep()),this,SLOT(NextStep()));
            connect(Players[i]->Worms[j],SIGNAL(RemoveItem(QGraphicsItem*)),this,SLOT(RemoveItem(QGraphicsItem*)));
            Players[i]->Worms[j]->pid=i;
            /*auto it = currentLevel.begin()+(int)trunc(Players[i]->Worms[i]->pointer->pos().x());
            auto ite = it + Players[i]->Worms[i]->pointer->pixmap().width();
            MoveItem(Players[i]->Worms[j]->pointer,0,constants.height-*(std::max_element(it,ite))-Players[i]->Worms[i]->pointer->pixmap().height());*/
        }
    }
    currentPlayer=0;
    currentStep=0;
    QThread *b = new QThread;
    _Physic* p = new _Physic(this);
    p->moveToThread(b);
    p->connect(b,SIGNAL(started()),p,SLOT(Draw()));
    p->connect(p,SIGNAL(MoveItem(QGraphicsItem*, int, int)),this,SLOT(MoveItem(QGraphicsItem*, int, int)));
    p->connect(p,SIGNAL(AddItem(QGraphicsItem*)),this,SLOT(AddItem(QGraphicsItem*)));
    p->connect(p,SIGNAL(RemoveItem(QGraphicsItem*)),this,SLOT(RemoveItem(QGraphicsItem*)));
    b->start();
    Phy=b;

    //MoveItem(Items.Item.named.Highlight,5.3,0);

    //QGraphicsRectItem k(QRect(400,0,200,100));
    //k.setPen(QColor(0,0,0,0)); k.setBrush(QImage(QString("inv.png")));
    //this->addItem(&k);
}

void MainScene::Draw() {
    this->setBackgroundBrush(QColor(128,192,255,255));
    //currentLevel=QVector<int>(600,100);
    //for (int i = 0; i<currentLevel.size(); i++) {
    //    this->addRect(QRect(i,400-currentLevel[i],1,currentLevel[i]),QPen(QColor(0,0,0,0)),QBrush(QColor(150,75,0,255)));
    //}
    //this->addRect(QRect(0,250,600,50),QPen(Qt::transparent),QBrush(Qt::blue));
    QPixmap pm(200,100);
    pm.fill(Qt::transparent);
    QPainter p(&pm);
    p.setBrush(QImage(QString("src/inv.png")));
    p.setPen(Qt::transparent);
    p.drawRect(QRectF(0,0,200,100));
    p.end();
    QGraphicsPixmapItem* k = new QGraphicsPixmapItem(pm);
    k->setPos(400,0);
    this->addItem(k);
    QPixmap pm2(50,50);
    pm2.fill(Qt::transparent);
    QPainter p2(&pm2);
    p2.setBrush(QImage(QString("src/inv2.png")));
    p2.setPen(Qt::transparent);
    p2.drawRect(QRectF(0,0,50,50));
    p2.end();
    QGraphicsPixmapItem* h = new QGraphicsPixmapItem(pm2);
    h->setPos(400,0);
    //h->setPen(QColor(0,0,0,0)); h->setBrush(QImage(QString("inv2.png")));
    this->addItem(h);
    //QGraphicsScene::addRect(0,0,50,50);
    Item.named.Inventory=k;
    Item.named.Highlight=h;
    k->hide();
    h->hide();
    //startGame(1,0,10);
    //std::this_thread::sleep_for(std::chrono::seconds(5));
    //MoveItem(h,50,0);*/
}

void MainScene::MoveItem(QGraphicsItem* item, int mX, int mY) {
    if (mX>0) {
    item->setPos(std::min(item->pos().x()+mX,(double)(constants.width-item->boundingRect().width())),
                  item->pos().y()+mY
                  );
    } else {
        item->setPos(std::max(item->pos().x()+mX,(double)0),
                      item->pos().y()+mY
                      );
    }
    //qDebug() << "Item new rect: " << item->rect();*/
}

void MainScene::RemoveItem(QGraphicsItem *item) {
    removeItem(item);
    //delete(item);
}

void MainScene::AddItem(QPixmap map, QPen pen, QBrush brush) {
    /*QPainter p(&map);
    p.setPen(pen);
    p.setBrush(brush);
    p.drawRect(0,0,map.width(),map.height());
    p.end();
    QGraphicsPixmapItem* k = new QGraphicsPixmapItem(map);
    //k->setPen(pen); k->setBrush(brush);
    //launched=k;*/
    //4to eto takoe i za4em ono tut? poteryano vremeny: 20
}

void MainScene::NextStep() {
    currentStep++;
    int pp = currentPlayer;
    pp=(pp+1%Players.size());
    while (Players[pp%Players.size()]->Worms.empty()) {pp=(pp+1%Players.size());}
    pp=pp%Players.size();
    if (pp==currentPlayer||curPlC==1) {
                    QGraphicsTextItem *WON = new QGraphicsTextItem(QString("Player %1 WON").arg(pp));
                    WON->setFont(QFont(QFont().defaultFamily(),70));
                    WON->setDefaultTextColor(Qt::red);
                    addItem(WON);
    } else currentPlayer=pp;
}
