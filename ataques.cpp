#include "ataques.h"
#include "mainwindow.h"

ataques::ataques( )
{   }

ataques::ataques(double x, double y, int tip)
{
    tipo = tip;
    posx_bala = x;
    posy_bala = y;
    setPos(posx_bala, posy_bala);
}

ataques::~ataques()
{   }

bool ataques::getColision() const
{
    return colision;
}

int ataques::getPuntos() const
{
    return puntos;
}

double ataques::getPosx_bala() const
{
    return posx_bala;
}

void ataques::movimiento()
{
    if ( posx_bala > 820 ){
        colision = true;
    }

    if ( tipo == 0 ){
        posx_bala += 20 * tiempo;                  // movimiento de la bala
        setPos(posx_bala, posy_bala);
    }

    else if ( tipo == 1 ){
        posx_bala -= 20 * tiempo;                  // movimiento de la bala
        setPos(posx_bala, posy_bala);
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();  // para la colision con disparo
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(enemigo) || typeid(*(colliding_items[i])) == typeid(jefes) ){
            colision = true;
            puntos = 1;
        }
    }
}

QRectF ataques::boundingRect() const
{
    return QRectF(-5,-5,20,10);
}

void ataques::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/imag/balas.png");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}

