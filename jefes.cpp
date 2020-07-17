#include "jefes.h"
#include "ataques.h"

bool jefes::getDestruccion() const
{
    return destruccion;
}

int jefes::getPosx() const
{
    return posx;
}

int jefes::getPosy() const
{
    return posy;
}

jefes::jefes()
{

}

jefes::jefes(int pos_x, int pos_y)
{
    posx = pos_x;
    posy = pos_y;
    setPos(posx, posy);
}

void jefes::movimiento()
{
    posx += 0.01;
    QList<QGraphicsItem *> colliding_items = collidingItems();  // para la colision con disparo o con jugador
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if ( typeid(*(colliding_items[i])) == typeid(ataques)  ){
            salud -= 10;
        }
    }
    if ( salud <= 0 ){
        destruccion = true;
    }
}


QRectF jefes::boundingRect() const
{
    return QRectF(0,0,100,400);
}

void jefes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/imag/gato.png");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}
