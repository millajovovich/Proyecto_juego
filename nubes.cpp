#include "nubes.h"
#include "personaje.h"
#include "stdio.h"

nubes::nubes()
{
    posx  = 820;
    posy  = (rand()%420+70);
    radio = 60;
    setPos( posx, posy );
}

bool nubes::getColision_perso() const
{
    return colision_perso;
}

bool nubes::getColision() const
{
    return colision;
}

int nubes::getTipo() const
{
    return tipo;
}

void nubes::movimiento()
{
    posx -= 10*0.2;

    QList<QGraphicsItem *> colliding_items = collidingItems();  // para la colision con disparo
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(personaje) ){
            colision = true;
            colision_perso = true;
        }
    }

    if ( posx <= 10 ){
        colision = true;
    }

    setPos( posx, posy );
}

QRectF nubes::boundingRect() const
{
    return QRectF(-radio/2,-radio/2,radio,radio);
}

void nubes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/imag/nube.gif");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}
