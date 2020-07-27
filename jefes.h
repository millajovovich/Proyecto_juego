#ifndef JEFES_H
#define JEFES_H

#include <QGraphicsItem>
#include <QPainter>

class jefes: public QGraphicsItem
{
    double posx;
    double posy;

    int ancho;
    int alto;
    int salud   = 1000;
    int nivel;

    bool destruccion = 0;                   // para confirmar la salud del boss
public:
    jefes();
    jefes (int pos_x , int pos_y, int lvl_ );
    void movimiento();

    bool getDestruccion() const;

    int getPosx() const;
    int getPosy() const;

private:
    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
};

#endif // JEFES_H
