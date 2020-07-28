#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <QGraphicsItem>
#include <QPainter>
#include <math.h>


class personaje: public QGraphicsItem
{
    double  angulo=0, posy, posx, vx=0, vy=0, vel=0, Ax=0, Ay=0, masa=70, radio , dist;
    double  G           = 1;                // constante de cavendish
    double  g           = 9.8;                // gravedad
    double  delta       = 0.2;

    int     salud       = 100;
    int     puntuacion  = 0;
    int     perdida     = 0;                         //para anunciar que perdio
    int     altura      = 30;
    int     ancho       = 10;
    int     imagen      = 0;                        //  para cambiar de imagen con los saltos
    int     tipo_powerup= 0;


public:
    personaje();

    //      POSICIONES
    int getPosx() const;
    void setPosx(int value);
    int getPosy() const;
    void setPosy(int value);

    //      MASA
    int getMasa() const;
    void setMasa(int value);
    void setVx(double value);

    //                  CALCULO Y ACTIALIZACION
    void iteracion();
    void calculo(double posx2, double posy2, double masa2);

    //          ACCIONES
    void salto();

    int getSalud() const;
    int getPerdida() const;
    int getPuntuacion() const;

    void setPuntuacion(int value);
    void setTipo_powerup(int value);            // para darle el power up al personaje
    void setSalud(int value);                   // para colocarla cuando se cargue una partida

    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
};

#endif // PERSONAJE_H
