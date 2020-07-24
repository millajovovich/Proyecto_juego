#ifndef ATAQUES_H
#define ATAQUES_H

#include <QGraphicsItem>
#include <QPainter>


class ataques: public QGraphicsItem
{
    bool    colision = false;
    double  posx_bala;
    double  posy_bala;
    double  tiempo  = 0.2;

    int     tipo    = 0;                   //      para saber de quien arroja el ataque
    int     puntos  = 0;                 //      para saber si colisiono con un enemigo

public:
    ataques( );
    ~ataques();
    ataques(double x, double y, int tip);                  //para crear la bala desde la posicion de personaje

    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    void movimiento();
    double getPosx_bala() const;

    bool getColision() const;

    int getPuntos() const;              //para obtener si desaparace por impacto de disparo
};

#endif // ATAQUES_H
