#ifndef AGUJERO_NEGRO_H
#define AGUJERO_NEGRO_H

#include <math.h>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>


class agujero_negro: public QGraphicsItem
{
    double angulo=0,posy ,posx , vx, vy, Ax=0, Ay=0, masa, radio , dist;
    double G = 1;     //6.67384*pow( 10 ,-11);
    double delta=0.1;
    int r=20;

public:
    ~agujero_negro();
    agujero_negro();

    double getPosx() const;
    double getPosy() const;
    double getMasa() const;

    void aceleraciones(double posx2, double posy2, double masa2);
    void iteracion(double dt);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

private:
    double escala;
};

#endif // AGUJERO_NEGRO_H
