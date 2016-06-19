#include "birdyellow.h"

birdyellow::birdyellow(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x,y,radius,timer,pixmap,world,scene)
{

}


void birdyellow::ability()
{
    if(countaccel==0)
    {
        g_body->SetLinearVelocity(b2Vec2(float(g_body->GetLinearVelocity().x)*5, float(g_body->GetLinearVelocity().y)*5));
        countaccel++;
    }
}
