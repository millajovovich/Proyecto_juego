#include "personaje.h"
#include "enemigo.h"
#include "mainwindow.h"

personaje::personaje()
{
    posx=400;
    posy=-200;
    vel=0;
    setPos(posx,-posy);
}

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

int personaje::getSalud() const
{
    return salud;
}

int personaje::getPerdida() const
{
    return perdida;
}

void personaje::setPuntuacion(int value)
{
    puntuacion += value;
}

int personaje::getPuntuacion() const
{
    return puntuacion;
}

void personaje::setTipo_powerup(int value)
{
    tipo_powerup = value;

    if ( value == 0 ){
        if ( 100-salud < 50){           // para que no sobre pase el limite de salud
            salud = 100;
        }
        else
            salud += 50;
    }
    tipo_powerup = 0;
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

void personaje::calculo(double posx2, double posy2, double masa2)
{
    angulo= atan2((posy2-posy), (posx2-posx));
    dist = pow(posx2-posx,2) + pow(posy2-posy,2);
    Ax += (((G*masa2)/dist) * cos(angulo));
    Ay += (((G*masa2)/dist) * sin(angulo));
}

void personaje::iteracion()
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

    if ( posy > -100 )
        vy = 0;

    vx = vx + Ax*delta;
    vy = vy +( Ay - g )*delta;
    vel = sqrt(vy*vy+vx*vx);
    angulo = atan2(vy,vx);

    posx += vx*delta + 0.5* Ax * delta * delta;
    posy += vy*delta + 0.5*( Ay - g ) * delta * delta;
    Ax = 0;
    Ay = 0;
    setPos( posx,-posy );

    if ( salud <= 0 )                   //          REPRESENTA EL GAME OVER EN MAINMENU
        perdida = 1;
}

void personaje::salto()
{
    vy = 40;
    imagen = !imagen;
}

bool personaje::baja_altura()
{
    if ( posy < -500 )
        return true;
    else if (posx < 10  ||  posx > 810 )
        vx = -vx;
    else
        return false;
}

QRectF personaje::boundingRect() const
{
    return QRectF(-20,-35,35,70);
}

void personaje::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    QPixmap pixmap, pixmap1;
    pixmap.load(":/imag/personaje1.png");
    pixmap1.load(":/imag/personaje2.png");
    if (imagen == 0)
        painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
    else
        painter->drawPixmap(boundingRect(),pixmap1,pixmap.rect());
}




