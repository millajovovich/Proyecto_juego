#include "ambiente.h"
#include "mainwindow.h"

ambiente::ambiente(int _tipo)
{
    tipo = _tipo;

    if ( tipo == 0){
        x = 970;
        y = rand()%470 + 60;
        this->setOpacity(0.7);
    }

    else if ( tipo == 1 ){
        x = 410;
        y = 515;
    }

    setPos( x, y );
}

bool ambiente::getDestrucion() const
{
    return destruccion;
}

void ambiente::movimiento()
{
    if ( tipo == 0 ){
        x -= vx*t;
    }

    if ( x < -150 ){
        destruccion = true;
    }
    setPos( x, y );
}

QRectF ambiente::boundingRect() const
{
    if ( tipo == 0 ){
        return QRectF(-150, -60, 300, 120);
    }
    else if ( tipo == 1 ){
        return QRectF(-420, -20, 840, 40);
    }
}

void ambiente::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    if ( tipo == 0 ){
        pixmap.load(":/imag/ambi1.png");
        painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
    }
    else if ( tipo == 1 ){
        pixmap.load(":/imag/ambi2.png");
        painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
    }
    //QPixmap pixmap;
    //pixmap.load(":/imag/nube.gif");
    //painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}
