#ifndef BIRDGREEN_H
#define BIRDGREEN_H

#include <bird.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>

class birdgreen : public Bird
{
public:
    birdgreen(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    void ability();
    int r1;
};

#endif // BIRDGREEN_H
