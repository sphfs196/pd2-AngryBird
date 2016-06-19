#ifndef PIG_H
#define PIG_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>

#define pig_DENSITY 10.0f
#define pig_FRICTION 0.2f
#define pig_RESTITUTION 0.5f

class Pig : public GameItem
{
public:
    Pig(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    b2BodyDef bodydef;

    void setLinearVelocity(b2Vec2 velocity);
};

#endif // PIG_H
