#include "5_Logick.h"

#include <QApplication>
#include <QGraphicsView>
#include <QRect>
#include <QThread>
#include <chrono>
#include <thread>
#include <random>
#include <ctime>


int main(int argc, char *argv[])
{
    //srand(0xFF2B00FF);
    srand(time(NULL));
    QApplication a(argc, argv);
    MainScene o(0,0,600,400);
    QGraphicsView scene(&o);
    scene.show();
	
    o.constants.width=600;
    o.constants.height=400;
    o.constants.FPS=50;
	
	
    _Load* load = new _Load(&o);
    QThread* loadThread = new QThread;
    load->moveToThread(loadThread);
        a.connect(loadThread,SIGNAL(started()),load,SLOT(Load()));
        a.connect(load,SIGNAL(AddItem(QGraphicsItem*)),&o,SLOT(AddItem(QGraphicsItem*)));
        a.connect(load,SIGNAL(stopped()),&o,SLOT(Draw()));
    loadThread->start();
    
	
	
    Menu* menu = new Menu(&o);
    _Logick* logick = new _Logick(&o, menu);
    QThread* logickThread = new QThread;
    o.Log=logickThread;
    logick->moveToThread(logickThread);
        a.connect(logickThread,SIGNAL(started()),logick,SLOT(Draw()));
        a.connect(logick,SIGNAL(MoveItem(QGraphicsItem*, int, int)),&o,SLOT(MoveItem(QGraphicsItem*, int, int)));
        a.connect(menu,SIGNAL(MoveItem(QGraphicsItem*, int, int)),&o,SLOT(MoveItem(QGraphicsItem*, int, int)));
        a.connect(logick,SIGNAL(AddItem(QGraphicsItem*)),&o,SLOT(AddItem(QGraphicsItem*)));
        a.connect(logick,SIGNAL(SetLine(qreal,qreal,qreal,qreal)),&o,SLOT(SetLine(qreal,qreal,qreal,qreal)));
        a.connect(menu,SIGNAL(SetPlainText(QGraphicsTextItem*,QString)),&o,SLOT(SetPlainText(QGraphicsTextItem*,QString)));
        a.connect(logick,SIGNAL(startGame(int,QVector<int>*, int)),&o,SLOT(startGame(int,QVector<int>*, int)));
        a.connect(logick,SIGNAL(NextStep()),&o,SLOT(NextStep()));
        a.connect(logick,SIGNAL(RemoveItem(QGraphicsItem*)),&o,SLOT(RemoveItem(QGraphicsItem*)));
    logickThread->start();

    menu->show();
    logick->statuses.named.inMenu=true;

    return a.exec();
}
