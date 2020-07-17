#include "agujero_negro.h"

agujero_negro::~agujero_negro()
{   }

agujero_negro::agujero_negro(): escala(0.04)
{
    posx = 830;
    posy = 200;
    vx = -15;
    vy = 0;
    masa = 5000000;
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

void agujero_negro::aceleraciones(double posx2, double posy2, double masa2)//    SUMA LAS ACELERACIONES CON LOS DEMAS CUERPOS
{
    angulo= atan2((posy2-posy), (posx2-posx));
    dist = pow(posx2-posx,2) + pow(posy2-posy,2);
    Ax += (((G*masa2)/dist) * cos(angulo));
    Ay += (((G*masa2)/dist) * sin(angulo));

}

void agujero_negro::iteracion(double tiempo)     //      PARA ACTUALIZAR LAS POSICIONES Y REINICIAR ACELERACIONES
{
    vx = vx + Ax*tiempo;
    vy = vy + Ay*tiempo;
    posx = posx + vx*tiempo + (Ax*tiempo*tiempo)/2;
    posy = posy + vy*tiempo + (Ay*tiempo*tiempo)/2;
    setPos( posx*escala, posy*escala );
    Ax=0;
    Ay=0;
}

QRectF agujero_negro::boundingRect() const
{
    return QRectF(-1*escala*radio,-1*escala*radio,2*escala*radio,2*escala*radio);
}

void agujero_negro::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(boundingRect());
}
