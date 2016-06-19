#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>

#define obs_DENSITY 10.0f
#define obs_FRICTION 0.5f
#define obs_RESTITUTION 0.5f

class obstacle : public GameItem
{
public:
    obstacle(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    b2BodyDef bodydef;
    b2PolygonShape bodyshape;

    void setLinearVelocity(b2Vec2 velocity);


};

#endif // OBSTACLE_H
