#ifndef BIRDYELLOW_H
#define BIRDYELLOW_H

#include <bird.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>
/*
#define yellow_DENSITY 100.0f
#define yellow_FRICTION 0.2f
#define yellow_RESTITUTION 0.5f
*/
class birdyellow : public Bird
{
public:
    birdyellow(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    void ability();

private :
    int countaccel=0;
};

#endif // BIRDYELLOW_H
