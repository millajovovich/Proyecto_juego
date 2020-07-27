#ifndef AMBIENTE_H
#define AMBIENTE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>


class ambiente: public QGraphicsItem
{
public:
    ambiente(int _tipo);

    bool getDestrucion() const;

public slots:
    void movimiento();

private:
    double x;
    double y;
    double vx = 2;
    double t  = 0.2;

    int tipo;

    bool destruccion = false;

    //QTimer *timer_amb  = new QTimer(this);

    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
};

#endif // AMBIENTE_H
