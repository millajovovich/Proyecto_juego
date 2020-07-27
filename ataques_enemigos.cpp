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

int ataques_enemigos::getTipo() const
{
    return tipo;
}

ataques_enemigos::ataques_enemigos(double x, double y, double vx0, double vy0, int tip)
{
    tipo        = tip;
    posx_bala   = x;
    posy_bala   = y;
    vx          = vx0;
    vy          = vy0;
    if ( tip == 1 ){     // para formar ataque aleatorios del boss
        posx_bala = 820;
        posy_bala = rand()%350+100;
    }

    setPos(posx_bala, posy_bala);
}

void ataques_enemigos::movimiento()
{
    if ( posx_bala < 0 || posy_bala < -500){
        colision = true;
    }

    if ( tipo == 0 ){
        posx_bala -= 25*t;                  // movimiento de la bala
    }

    else if ( tipo == 1 ){
        posx_bala -= 25*t;                  // movimiento del ataque
    }

    else if ( tipo == 2 ){
        posy_bala += vy*t;
        posx_bala += vx*t;
    }

    setPos( posx_bala, posy_bala);

    QList<QGraphicsItem *> colliding_items = collidingItems();  // para la colision con disparo
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if ( typeid(*(colliding_items[i])) == typeid(personaje) || typeid(*(colliding_items[i])) == typeid(personaje2) ){
            colision = true;
            puntos = 1;
        }
    }
}

QRectF ataques_enemigos::boundingRect() const
{
    if (tipo == 0){
        return QRectF(-5,-5,10,10);
    }
    else if ( tipo == 1 ){
        return QRectF(0,-50,825,100);
    }
    else if ( tipo == 2 ){
        return QRectF(-15, -15, 60, 30);
    }
}

void ataques_enemigos::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->setBrush(Qt::black);
    //QPixmap *pixmap;
    //painter->drawPixmap(0, 0, *pixmap, 0, 50, 1000, 100);

    if (tipo == 0){
        painter->setBrush(Qt::black);
        painter->drawEllipse(boundingRect());
    }

    else if ( tipo == 1 ){
        QPixmap pixmap;
        pixmap.load(":/imag/ata_boss1.png");
        painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
    }

    else if ( tipo == 2 ){
        QPixmap pixmap;
        pixmap.load(":/imag/ata_boss2.png");
        painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
    }
}
