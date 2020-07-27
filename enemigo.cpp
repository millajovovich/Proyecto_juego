#include "enemigo.h"
#include "ataques.h"
#include "mainwindow.h"
#include "personaje.h"

bool enemigo::getColision() const
{
    return colision;
}

enemigo::enemigo()
{
    //srand (time(NULL));
    posx_enemigo = 820;
    posy_enemigo = rand()%390+100;
    setPos( posx_enemigo , posy_enemigo );
    tipo_enemigo = rand()%1;
}

enemigo::~enemigo()
{   }

double enemigo::getPosx_enemigo() const
{
    return posx_enemigo;
}

double enemigo::getPosy_enemigo() const
{
    return posy_enemigo;
}

void enemigo::setVx(double value)
{
    vx = value;
}

void enemigo::movimiento()
{
    if ( tipo_enemigo == 0 ){
        posx_enemigo += -10*0.1;
        posy_enemigo += vy * 0.1;

        if ( posy_enemigo <= 80 || posy_enemigo >= 500 )        // para hacer el efecto de rebote
            vy = -vy;

    }
    setPos( posx_enemigo , posy_enemigo );

    if ( posx_enemigo < 20 || salud <= 0){
        colision = true;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();  // para la colision con disparo o con jugador
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if ( typeid(*(colliding_items[i])) == typeid(personaje) || typeid(*(colliding_items[i])) == typeid(personaje2)){
            colision = true;
        }
        else if ( typeid(*(colliding_items[i])) == typeid(ataques) ){
            salud -= 20;
        }
    }
}

QRectF enemigo::boundingRect() const
{
    return QRectF(-15,-15,30,30);
}

void enemigo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/imag/alien.png");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}
