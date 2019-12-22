#include "4_Scene.h"
#include <cmath>

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
