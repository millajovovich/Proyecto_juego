#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <QGraphicsItem>
#include <QPainter>
#include <math.h>


class personaje: public QGraphicsItem
{
    double angulo=0, posy, posx, vx=0, vy, vel=0, Ax=0, Ay=0, masa=70, radio , dist;
    double G = 1;
    double g = 9.8;
    double delta = 0.2;

    int altura = 30;
    int ancho  = 10;

    int imagen = 0;

public:
    personaje();

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

};

#endif // PERSONAJE_H
