#include "birdpink.h"

birdpink::birdpink(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x,y,radius,timer,pixmap,world,scene)
{

}
void birdpink::ability()
{
    QPixmap change(":/image/005_1.png");
    change = change.scaled(960/32*2,540/18*2);
    g_pixmap.setPixmap(change);
/*
    if(countaccel==0)
    {
        g_body->SetLinearVelocity(b2Vec2(float(0.0), -abs(float(g_body->GetLinearVelocity().y)*10000)));
        countaccel++;
    }
    */
}
