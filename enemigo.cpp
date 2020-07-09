#include "enemigo.h"
#include "personaje.h"

enemigo::enemigo()
{
    //srand (time(NULL));
    posx_enemigo = 750;
    posy_enemigo = rand()%400;
    setPos( posx_enemigo , posy_enemigo );
}

enemigo::~enemigo()
{

}

double enemigo::getPosx_enemigo() const
{
    return posx_enemigo;
}

double enemigo::getPosy_enemigo() const
{
    return posy_enemigo;
}

void enemigo::setVx(double value)
{
    vx = value;
}

void enemigo::movimiento()
{
    posx_enemigo += vx*0.2;
    setPos( posx_enemigo , posy_enemigo );
}

QRectF enemigo::boundingRect() const
{
    return QRectF(-15,-15,30,30);
}

void enemigo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawRect(boundingRect());
}
