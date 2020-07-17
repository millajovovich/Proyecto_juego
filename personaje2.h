#ifndef PERSONAJE2_H
#define PERSONAJE2_H


#include <QGraphicsItem>
#include <QPainter>
#include <math.h>


class personaje2: public QGraphicsItem
{
    double angulo=0, posy, posx, vx=0, vy, vel=0, Ax=0, Ay=0, masa=70, radio , dist;
    int     salud       = 100;
    int     puntuacion  = 0;
    int     perdida     = 0;                         //para anunciar que perdio
    double  G           = 1;
    double  g           = 9.8;
    double  delta       = 0.2;

    int     altura      = 30;
    int     ancho       = 10;

    int     imagen      = 0;

public:
    personaje2();

    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    // POSICIONES
    int getPosx() const;
    void setPosx(int value);
    int getPosy() const;
    void setPosy(int value);

    // MASA
    int getMasa() const;
    void setMasa(int value);
    void setVx(double value);

    //                  CALCULO Y ACTIALIZACION
    void iteracion();
    void calculo(/*double posx2, double posy2, double masa2*/);

    //          ACCIONES
    void salto();
    bool baja_altura();                 // para confirmar la altura apropiada

    int getSalud() const;
    int getPerdida() const;
    void setPuntuacion(int value);
    int getPuntuacion() const;
};


#endif // PERSONAJE2_H
