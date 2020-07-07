#include "ataques.h"

ataques::ataques()
{

}

ataques::ataques(double x, double y)
{
    posx_bala = x;
    posy_bala = y;
    setPos(posx_bala, posy_bala);
}

QRectF ataques::boundingRect() const
{
    return QRectF(-5,-5,20,5);
}

void ataques::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawEllipse(boundingRect());
}

void ataques::movimiento()
{
    posx_bala+=10*0.2;                  // movimiento de la bala
    setPos(posx_bala, posy_bala);

    /*if (posx_bala > 600){
        scene()->removeItem(this);
    }*/
}
