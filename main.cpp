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


int main(int argc, char *argv[])
{
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
    _Draw* draw = new _Draw(&o);
    QThread* b = new QThread;
    draw->moveToThread(b);
    a.connect(b,SIGNAL(started()),draw,SLOT(Draw()));
    b->start();
    a.connect(draw,SIGNAL(stopped()),&o,SLOT(Draw()));

    /*while(true) {
        if(KeysPressed.Up()) h.setRect(h.rect().x(),h.rect().y()-50,50,50);
        if(KeysPressed.Down()) h.setRect(h.rect().x(),h.rect().y()+50,50,50);
        if(KeysPressed.Right()) h.setRect(h.rect().x()+50,h.rect().y(),50,50);
        if(KeysPressed.Left()) h.setRect(h.rect().x()-50,h.rect().y(),50,50);

    }*/



    return a.exec();
}
