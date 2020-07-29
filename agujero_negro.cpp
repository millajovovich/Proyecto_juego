#include "agujero_negro.h"

bool agujero_negro::getDestrucion() const
{
    return destrucion;
}

agujero_negro::~agujero_negro()
{   }

agujero_negro::agujero_negro(): escala(0.04)
{
    posx = 850;
    posy = rand()%440+60;
    vx = -8;
    vy = 0;
    masa = 20000;
    radio = 10;
}

double agujero_negro::getPosx() const
{
    return posx;
}

double agujero_negro::getPosy() const
{
    return posy;
}

double agujero_negro::getMasa() const
{
    return masa;
}

void agujero_negro::iteracion()     //      PARA ACTUALIZAR LAS POSICIONES Y REINICIAR ACELERACIONES
{
    posx = posx + vx*0.1;
    posy = posy + vy*0.1;
    setPos( posx, posy);
    Ax=0;
    Ay=0;

    if ( posx <= 0 ){
        destrucion = true;
    }
}

QRectF agujero_negro::boundingRect() const
{
    return QRectF(-10,-10,20,20);
}

void agujero_negro::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    painter->drawEllipse(boundingRect());
}
