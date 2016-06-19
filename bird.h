#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class Bird : public GameItem
{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    b2BodyDef bodydef;
    b2CircleShape bodyshape;
    b2FixtureDef fixturedef;

    void setLinearVelocity(b2Vec2 velocity);

    virtual void ability();

};

#endif // BIRD_H
