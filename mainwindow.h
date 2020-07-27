#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QKeyEvent>

#include "personaje.h"
#include "personaje2.h"
#include "ataques.h"

#include "enemigo.h"
#include "ataques_enemigos.h"
#include "jefes.h"

#include "nubes.h"
#include "agujero_negro.h"
#include "ambiente.h"

#include <QTimer>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool activacion         = true;         //  para confirmar, por ahora no esta en uso
    bool multijugador       = 0;
    bool ataque_jefe        = 0;
    bool completado         = 0;
    bool juego_on           = 0;            // para que se activen teclas para la partida

    int marcador            = 0;
    int verificador         = 0;            //  este es para saber si entra en escena un boss y no spawnear enemigos basicos
    int verificador_hole    = 0;
    int cuenta_enemigos     = 1;            //  empieza en uno para que no aparezca jefe empezando
    int pantalla            = 0;
    int nivel               = 1;            //  representa el nivel actual y para la dificultad


private slots:
    void add_enemigo();                 //      para añadir enemigo
    void add_boss();                    //      para añadir jefe
    void add_nube();
    void add_ambiente();                //  para generar el ambiente de movimiento
    void add_agujero();
    void ataque_boss();

    void Mover();                       //      para actualizar las posiciones
    void juego_terminado();             //      para anunciar game over
    void juego_completado();

    //       BOTONES
    void on_solo_jugador_clicked();
    void on_multijugador_clicked();
    void on_continuar_clicked();        //  continuar estando en pausa
    void on_salir_menu_clicked();       //  para salir al menu principal

    void on_seguir_clicked();           //  para pasar del registro a elegir modo de juego

private:
    Ui::MainWindow *ui;
    QGraphicsScene *Scene = new QGraphicsScene;
    QGraphicsView  *view;

    //              TIEMPOS DE MOVIMIENTOS
    QTimer *timer           = new QTimer;
    QTimer *tiempo_enemigos = new QTimer;
    QTimer *tiempo_ata_jefe = new QTimer;               // timepo entre los  ataques de jefes
    QTimer *tiempo_nubes    = new QTimer;               // tiempo de aparicion de las nubes
    QTimer *tiempo_amb      = new QTimer;
    QTimer *tiempo_agujero  = new QTimer;               // tiempo de aparicion de las nubes

    personaje       *cuerpo;
    personaje2      *cuerpo2;
    ataques         *bala;
    jefes           *boss;
    nubes           *power_up;
    agujero_negro   *hole;
    ambiente        *entorno;

    //              LISTAS PARA LOS MOVIMIENTOS Y CONFIMARCIONES DE COLISION
    QList <ataques*>             balas;
    QList <ataques_enemigos*>    balas_ene;
    QList <enemigo*>             enemy;
    QList <nubes*>               nube;
    QList <agujero_negro*>       negro;
    QList <ambiente*>            entor;


    void keyPressEvent(QKeyEvent *evento);
};
#endif // MAINWINDOW_H
