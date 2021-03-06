#include "personaje2.h"
#include "enemigo.h"
#include "mainwindow.h"

int personaje2::getMasa() const
{
    return masa;
}

void personaje2::setMasa(int value)
{
    masa = value;
}

void personaje2::setVx(double value)
{
    vx = value;
}

int personaje2::getSalud() const
{
    return salud;
}

int personaje2::getPerdida() const
{
    return perdida;
}

void personaje2::setPuntuacion(int value)
{
    puntuacion += value;
}

int personaje2::getPuntuacion() const
{
    return puntuacion;
}

personaje2::personaje2()
{
    posx=400;
    posy=-300;
    vel=0;
    setPos(posx,-posy);
}

int personaje2::getPosx() const
{
    return posx;
}

void personaje2::setPosx(int value)
{
    posx = value;
}

int personaje2::getPosy() const
{
    return posy;
}

void personaje2::setPosy(int value)
{
    posy += value;
    setPos(posx,-posy);
}

void personaje2::salto()
{
    vy=40;
    angulo=90;
}

void personaje2::calculo( double posx2, double posy2, double masa2 )
{
    angulo= atan2((posy2-posy), (posx2-posx));
    dist = pow(posx2-posx,2) + pow(posy2-posy,2);
    Ax += (((G*masa2)/dist) * cos(angulo));
    Ay += (((G*masa2)/dist) * sin(angulo));
}

void personaje2::iteracion()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();  // para la colision con disparo
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(enemigo) || typeid(*(colliding_items[i])) == typeid(ataques_enemigos)){
            salud -= 10;
        }
        if (typeid(*(colliding_items[i])) == typeid(agujero_negro))
            salud = 0;

    }

    vx = vx + Ax*delta;
    vy = vy +( Ay - g )*delta;
    vel = sqrt(vy*vy+vx*vx);
    angulo = atan2(vy,vx);

    posx += vx*delta + 0.5* Ax * delta * delta;
    posy += vy*delta + 0.5*( Ay - g ) * delta * delta;
    Ax = 0;
    Ay = 0;

    if ( salud <= 0 )                   //      REPRESENTA EL GAME OVER EN MAINMENU
        perdida = 1;

    if ( posy > -100 ){
        vy = 0;
        posy = -100;
    }
    else if (posx < 10  ||  posx > 810 ){
        vx = -vx;
    }
    else if ( posy < -500 ){
        vy = 70;
        posy = -500;
        salud -= 20;
    }
    setPos( posx,-posy );
}

QRectF personaje2::boundingRect() const
{
    return QRectF(-20,-35,35,70);
}

void personaje2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    QPixmap pixmap;
    pixmap.load(":/imag/personaje0.png");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}
