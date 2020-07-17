#include "ataques_enemigos.h"
#include "mainwindow.h"

ataques_enemigos::ataques_enemigos()
{   }

bool ataques_enemigos::getColision() const
{
    return colision;
}

int ataques_enemigos::getPuntos() const
{
    return puntos;
}

double ataques_enemigos::getPosx_bala() const
{
    return posx_bala;
}

ataques_enemigos::ataques_enemigos(double x, double y, int tip)
{
    tipo = tip;
    posx_bala = x;
    posy_bala = y;
    if ( tip == 1 ){
        posx_bala = 820;
        posy_bala = rand()%400+100;
    }
    setPos(posx_bala, posy_bala);
}

QRectF ataques_enemigos::boundingRect() const
{
    if (tipo == 0)
        return QRectF(-5,-5,20,5);
    else if ( tipo == 1 )
        return QRectF(0,-50,800,100);
}

void ataques_enemigos::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    if (tipo == 0)
        painter->drawEllipse(boundingRect());
    else if ( tipo == 1 )
        painter->drawRect(boundingRect());
}

void ataques_enemigos::movimiento()
{
    if ( posx_bala < 0){
        colision = true;
    }

    if ( tipo == 0 ){
        posx_bala -= 20*0.2;                  // movimiento de la bala
        setPos(posx_bala, posy_bala);
    }

    else if ( tipo == 1 ){
        posx_bala -= 20*0.2;                  // movimiento de la bala
        setPos(posx_bala, posy_bala);
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();  // para la colision con disparo
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if ( typeid(*(colliding_items[i])) == typeid(personaje) || typeid(*(colliding_items[i])) == typeid(personaje2) ){
            colision = true;
            puntos = 1;
        }
    }
}
