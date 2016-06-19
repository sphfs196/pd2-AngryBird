#include "birdgreen.h"

birdgreen::birdgreen(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x,y,radius,timer,pixmap,world,scene)
{
    r1=radius;
}
void birdgreen::ability()
{
    QPixmap change(":/image/ice.png");
    change = change.scaled(960/32*6,540/18*6);
    g_pixmap.setPixmap(change);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);

    g_size = QSizeF(r1*2*3,r1*2*3);
    bodyshape.m_radius = r1*3;
    fixturedef.shape = &bodyshape;

    g_body->CreateFixture(&fixturedef);

}
