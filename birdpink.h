#ifndef BIRDPINK_H
#define BIRDPINK_H

#include <bird.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>

class birdpink : public Bird
{
public:
    birdpink(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    void ability();

    //int countaccel=0;

};

#endif // BIRDPINK_H
