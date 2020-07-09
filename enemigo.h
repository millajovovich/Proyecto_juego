#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsItem>
#include <QPainter>
#include "stdio.h"


class enemigo : public QGraphicsItem
{
    double posx_enemigo;
    double posy_enemigo;
    double vx = -5;

public:
    enemigo();
    ~enemigo();

    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    void setVx(double value);

    void movimiento();

    double getPosx_enemigo() const;
    double getPosy_enemigo() const;
};

#endif // ENEMIGO_H
