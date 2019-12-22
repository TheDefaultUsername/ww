#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QRect>
#include <QGraphicsItem>
#include <QThread>
#include <chrono>
#include <thread>
#include <QKeyEvent>
#include <random>
#include <ctime>

//MainWindow *t = NULL;

int main(int argc, char *argv[])
{
    //srand(0xFF2B00FF);
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow o(0,0,600,400);
    QGraphicsView scene(&o);
    scene.show();
#if 0
    o.setBackgroundBrush(QBrush(QColor(80,120,255,255)));
    QGraphicsRectItem k(QRect(400,0,200,100));
    o.addItem(&k); k.setPen(QColor(0,0,0,0)); k.setBrush(QImage(QString("inv.png")));
    k.hide();
    k.show();
    QGraphicsRectItem h(QRect(400,0,50,50)); h.setPen(QColor(0,0,0,0)); h.setBrush(QImage(QString("inv2.png")));
    o.addItem(&h);
#endif
    o.constants.width=600;
    o.constants.height=400;
    o.constants.FPS=50;
    _Draw* draw = new _Draw(&o);
    QThread* b = new QThread;
    draw->moveToThread(b);
    a.connect(b,SIGNAL(started()),draw,SLOT(Draw()));
    a.connect(draw,SIGNAL(AddItem(QGraphicsItem*)),&o,SLOT(AddItem(QGraphicsItem*)));
    b->start();
    a.connect(draw,SIGNAL(stopped()),&o,SLOT(Draw()));
    Menu* menu = new Menu(&o);
    _Logick* log = new _Logick(&o, menu);
    QThread* c = new QThread;
    log->moveToThread(c);
    a.connect(b,SIGNAL(started()),log,SLOT(Draw()));
    a.connect(log,SIGNAL(MoveItem(QGraphicsPixmapItem*, int, int)),&o,SLOT(MoveItem(QGraphicsPixmapItem*, int, int)));
    a.connect(log,SIGNAL(AddItem(QGraphicsItem*)),&o,SLOT(AddItem(QGraphicsItem*)));
    a.connect(log,SIGNAL(SetLine(qreal,qreal,qreal,qreal)),&o,SLOT(SetLine(qreal,qreal,qreal,qreal)));
    c->start();
    log->statuses.named.inInventory=true;
    //t=&o;


    /*while(true) {
        if(KeysPressed.Up()) h.setRect(h.rect().x(),h.rect().y()-50,50,50);
        if(KeysPressed.Down()) h.setRect(h.rect().x(),h.rect().y()+50,50,50);
        if(KeysPressed.Right()) h.setRect(h.rect().x()+50,h.rect().y(),50,50);
        if(KeysPressed.Left()) h.setRect(h.rect().x()-50,h.rect().y(),50,50);

    }*/



    return a.exec();
}

//void KeyPressEvent(QKeyEvent* event) {
//    t->keyPressEvent(event);
//}

//void KeyReleaseEvent(QKeyEvent* event) {
//    t->keyReleaseEvent(event);
//}
