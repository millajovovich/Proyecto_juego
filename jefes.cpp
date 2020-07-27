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

jefes::jefes(int pos_x, int pos_y, int lvl_ )
{
    posx  = pos_x;
    posy  = pos_y;
    nivel = lvl_;
    salud = salud*lvl_;             // para colocar salud dependiendo nivel

    setPos(posx, posy);
}

void jefes::movimiento()
{
    if ( posx > 700 && nivel == 1 ){
        posx -= 1;
    }
    else if ( posx > 680 ){
        posx -= 1;
    }

    setPos( posx, posy );

    QList<QGraphicsItem *> colliding_items = collidingItems();  // para la colision con disparo o con jugador
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if ( typeid(*(colliding_items[i])) == typeid(ataques)  ){
            salud -= 10;
        }
    }
    if ( salud <= 0 ){
        salud = 0;
        destruccion = true;
    }
}


QRectF jefes::boundingRect() const
{
    if ( nivel == 1 ){
        return QRectF(0,0,140,420);
    }
    else if ( nivel == 2 )
        return QRectF(0,0,150,420);
}

void jefes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    if ( nivel == 1 ){
        pixmap.load(":/imag/gato.png");
        painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
    }
    else if ( nivel == 2 || nivel == 3){
        pixmap.load(":/imag/boss2.png");
        painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
    }
}
