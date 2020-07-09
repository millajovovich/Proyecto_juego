#include "personaje.h"

int personaje::getMasa() const
{
    return masa;
}

void personaje::setMasa(int value)
{
    masa = value;
}

void personaje::setVx(double value)
{
    vx = value;
}

personaje::personaje()
{
    posx=400;
    posy=-100;
    vel=0;
    setPos(posx,-posy);
}

QRectF personaje::boundingRect() const
{
    return QRectF(-20,-35,35,70);
}

void personaje::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    QPixmap pixmap;
    pixmap.load(":/imag/personaje0.png");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
    //painter->setBrush(Qt::cyan);
    //painter->drawEllipse(boundingRect());
}

int personaje::getPosx() const
{
    return posx;
}

void personaje::setPosx(int value)
{
    posx = value;
}

int personaje::getPosy() const
{
    return posy;
}

void personaje::setPosy(int value)
{
    posy += value;
    setPos(posx,-posy);
}

void personaje::calculo(/*double posx2, double posy2, double masa2*/)
{
    /*angulo= atan2((posy2-posy), (posx2-posx));
    dist = pow(posx2-posx,2) + pow(posy2-posy,2);
    Ax += (((G*masa2)/dist) * cos(angulo));
    Ay += (((G*masa2)/dist) * sin(angulo));*/
    vy=vy-g*delta;
    vel=sqrt(vy*vy+vx*vx);
    angulo=atan2(vy,vx);

}

void personaje::salto()
{
    vy=40;
    angulo=90;
}

bool personaje::baja_altura()
{
    if ( posy < -420 )
        return true;
    else if (posx < 2  ||  posx > 750 )
        vx = -vx;
    else
        return false;
}

void personaje::iteracion()
{
    posx+=vx*delta;
    posy+=vy*delta-0.5*g*delta*delta;
    setPos(posx,-posy);
}




