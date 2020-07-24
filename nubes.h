#ifndef NUBES_H
#define NUBES_H

#include <QGraphicsItem>
#include <QPainter>
#include <stdio.h>

class nubes : public QGraphicsItem
{
    int     tipo = rand()%1;            // para darte un poder a cada tipo de nube
    int     radio;

    double  posx;
    double  posy;

    bool    colision_perso  = false;
    bool    colision        = false;
    bool    imagen          = 0;
public:
    nubes();

    void movimiento();

    int getTipo() const;
    bool getColision() const;
    bool getColision_perso() const;

    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

};

#endif // NUBES_H
