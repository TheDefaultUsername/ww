#include "4_Scene.h"
#include <cmath>

QGraphicsItem* Weapon::detonate() {
    //if (isDet) return NULL;
    MainScene* scene = (MainScene*)(pointer->scene());
    if (isSpecific) {

    } else {
        //scene->launched=NULL;
        //velocityX=0;
        //velocityY=0;
        QVector<Worm*> vec;
        for (int i = 0; i<radius*2; i++)
            for (int j = 0; j<radius*2; j++) {
                QPointF pos(pointer->pos().x()+25-radius+i,pointer->pos().y()+25-radius+j);
                if (sqrt((-radius+i)*(-radius+i)+(-radius+j)*(-radius+j))<radius) {
                    if (pos.x()>=0&&pos.x()<scene->constants.width)
                    if (pos.y()>scene->currentLevel[((int)pos.x())]->pos().y()) emit MoveItem((QGraphicsPixmapItem*)scene->currentLevel[((int)pos.x())],0,1);
                    ///EMIT!!!!!!!!
                    //scene->addRect(pos.x(),pos.y(),1,1,QPen(Qt::transparent),QBrush(QColor(128,192,255,255)));
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
            ///EMIT!!!!!!!!!
        }
        //scene->addRect();
        return pointer;
    }
    return NULL;
}
