#include "5_Logick.h"
#include <QThread>
#include <cmath>
#include <QPainter>


void MainWindow::AddItem(QGraphicsItem *item) {
    addItem(item);
}
void MainWindow::SetLine(qreal x1,qreal x2,qreal x3,qreal x4) {
    Item.named.Scope->setLine(x1,x2,x3,x4);
}

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
    Item.named.Inventory=k;
    Item.named.Highlight=h;
    startGame(1,0,10);
    //std::this_thread::sleep_for(std::chrono::seconds(5));
    //MoveItem(h,50,0);*/
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
