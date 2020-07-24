#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsItem>
#include <QPainter>
#include <QList>
#include "ataques.h"
#include "stdio.h"


class enemigo : public QGraphicsItem
{
    bool    colision        = false;

    double  posx_enemigo;
    double  posy_enemigo;
    double  vx              = -15;
    double  vy              = -15 * (rand()%3-1);
    double  t               = 0.1;

    int     tipo_enemigo    = 0;
    int     salud = 100;

public:
    enemigo();
    ~enemigo();

    QList<ataques*> enemy;

    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    void setVx(double value);

    void movimiento();

    double getPosx_enemigo() const;
    double getPosy_enemigo() const;

    bool getColision() const;
};

#endif // ENEMIGO_H
