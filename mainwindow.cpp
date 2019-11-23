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
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key()==Keys.Inventory) KeysPressed.sInventory(false);
    if (event->key()==Keys.Right) KeysPressed.sRight(false);
    if (event->key()==Keys.Left) KeysPressed.sLeft(false);
    if (event->key()==Keys.Up) KeysPressed.sUp(false);
    if (event->key()==Keys.Down) KeysPressed.sDown(false);
    if (event->key()==Keys.Jump) KeysPressed.sJump(false);
    if (event->key()==Keys.Use) KeysPressed.sUse(false);
}

MainWindow::~MainWindow()
{
}

void MainWindow::startGame(int playerAmount, int level, int gravity) {
    this->clear();
    this->setBackgroundBrush(QColor(128,192,255,255));
    currentLevel=QVector<int>(600,100);
    for (int i = 0; i<currentLevel.size(); i++) {
        this->addRect(QRect(i,400-currentLevel[i],1,currentLevel[i]),QPen(QColor(0,0,0,0)),QBrush(QColor(150,75,0,255)));
    }
    QGraphicsRectItem k(QRect(400,0,200,100));
    k.setPen(QColor(0,0,0,0)); k.setBrush(QImage(QString("inv.png")));
    this->addItem(&k);
}

void _Draw::Draw() {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    //((QGraphicsRectItem*)(main->items()[0]))->setRect(QRect(0,0,200,100));
    /*std::this_thread::sleep_for(std::chrono::seconds(5));
    QGraphicsRectItem k(QRect(400,0,200,100));
    k.setPen(QColor(0,0,0,0)); k.setBrush(QImage(QString("inv.png")));
    this->main->addItem(&k);
    std::this_thread::sleep_for(std::chrono::seconds(15));*/
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
    QGraphicsScene::addRect(0,0,50,50);

}
