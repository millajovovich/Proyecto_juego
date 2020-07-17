#include "stdio.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

#include <QGraphicsItem>


//arreglar lo de los disparos entre enemigos
// mirar set opaciti


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));

    ui->graphicsView->setScene(Scene);
    Scene->setSceneRect(0,0,810,520);
    Scene->addRect(Scene->sceneRect());

    //              RELOJES
    connect(timer,          SIGNAL(timeout()),  this,SLOT(Mover()));
    connect(tiempo_enemigos,SIGNAL(timeout()),  this,SLOT(add_enemigo()));
    connect(tiempo_ata_jefe,SIGNAL(timeout()),  this,SLOT(ataque_boss()));
    connect(tiempo_nubes,   SIGNAL(timeout()),  this,SLOT(add_nube()));

    // ocultar los botones para que no aparezcan todos cuando empiece la app
    ui->gameover->hide();
    ui->lcdNumber->hide();
    ui->nombre_1->hide();
    ui->nombre_2->hide();
    ui->progressBar_1->hide();
    ui->progressBar_2->hide();
    ui->continuar->hide();
    ui->salir_menu->hide();
    ui->progressBar_1->isVisible();

    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/imag/intro.jpg")));

}


MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

//  FUNCION PARA ACTUALIZAR POSICIONES
void MainWindow::Mover()
{
    //  MOVIMIENTO DE PERSONAJE 1
    cuerpo->iteracion();
    cuerpo->calculo();

    //  MOVIMIENTO DE PERSONAJE 2
    if ( multijugador == true ) {
        cuerpo2->iteracion();
        cuerpo2->calculo();
    }

    //  PARA CONFIRMAR BAJA ALTURA Y LADOS P1
    if ( cuerpo->baja_altura() == true )
        cuerpo->salto();

    //  PARA CONFIRMAR BAJA ALTURA Y LADOS P2
    if ( cuerpo2->baja_altura() == true )
        cuerpo2->salto();

    //  MOVIMIENTO Y SALUD DE jefe
    if ( verificador == 1 ){
        boss->movimiento();
        boss->show();
        if ( boss->getDestruccion() == 1 ){
            Scene->removeItem(boss);
            verificador = 0;
            marcador +=1000;
            tiempo_ata_jefe->stop();
            //tiempo_enemigos->start(6000/nivel + 1000);      //  para subir la dificultad tra
        }
    }

    //  PARA ANUNCIAR GAMEOVER
    if ( cuerpo->getPerdida() == 1 || cuerpo2->getPerdida() == 1 )
        juego_terminado();

    //      MOVIMIENTO DE LAS BALAS DE PERSONAJES
    for( int i=0; i<balas.size();i++ ){
        if ( balas.at(i)->getPuntos() == 1 )                // para confirmar si murio por impacto
            marcador += 20;

        if ( balas.at(i)->getColision() == true ){          // para confirma si salio de escena o impacto con algo
            Scene->removeItem(balas.at(i));                 // para remover de la escena
            balas.removeOne(balas.at(i));                  //para eliminar de la lista
        }
        else
            balas.at(i)->movimiento();
    }

    //      MOVIMIENTO DE LAS BALAS DE ENEMIGOS
    for( int i=0; i<balas_ene.size();i++ ){
        if ( balas_ene.at(i)->getPuntos() == 1 )                // para confirmar si murio por impacto
            marcador += 20;

        if ( balas_ene.at(i)->getColision() == true ){          // para confirma si salio de escena o impacto con algo
            Scene->removeItem(balas_ene.at(i));                 // para remover de la escena
            balas_ene.removeOne(balas_ene.at(i));                  //para eliminar de la lista
        }
        else
            balas_ene.at(i)->movimiento();
    }

    //      MOVIMIENTO DE LOS ENEMIGOS
    for( int i=0; i<enemy.size();i++ ){
        if ( int(-enemy.at(i)->getPosy_enemigo()) == int (cuerpo->getPosy()) ){

            //          CREACION DE LAS BALAS ENEMIGAS EN POSICION DEL PERSONAJE
            balas_ene.append(new ataques_enemigos( enemy.at(i)->getPosx_enemigo(), enemy.at(i)->getPosy_enemigo(), 0));
            Scene->addItem( balas_ene.back() );
        }

        //      VERIFICADOR DE DESTRUCCION DE ENEMIGO
        if ( enemy.at(i)->getColision() == true ){
            Scene->removeItem(enemy.at(i));                 // para remover de la escena
            enemy.removeOne(enemy.at(i));                   //para eliminar de la lista

            //      CUENTA PARA APARICION DE LOS JEFES
            cuenta_enemigos += 1;                             // para llevar la cuenta de en cuanto aparece el boss
            if (cuenta_enemigos%5 == 0 && verificador == 0){  // condicional para llamar al boss, verif = 0 para no spawnear otro boss
                add_boss();
            }
        }

        else
            enemy.at(i)->movimiento();
    }

    //      MOVIMIENTO DE NUBES
    for ( int i=0; i<nube.size();i++ ){
        nube.at(i)->movimiento();

        if ( nube.at(i)->getColision() == true ){
            Scene->removeItem( nube.at(i) );
            nube.removeOne( nube.at(i) );
        }
    }

    ui->progressBar_1->setValue(cuerpo->getSalud());
    ui->progressBar_2->setValue(cuerpo2->getSalud());
    ui->lcdNumber->display(marcador);
}


void MainWindow::add_enemigo()
{
    if (verificador == 0 ){                         // verificador de boss
        enemy.append( new enemigo() );
        Scene->addItem(enemy.back());
    }
}

void MainWindow::add_boss()
{
    verificador = 1;
    boss = new jefes(720 , 70);
    Scene->addItem(boss);
    boss->setOpacity(0.5);
    tiempo_ata_jefe->start(6000);
}

void MainWindow::add_nube()
{
    nube.append( new nubes );
    Scene->addItem( nube.back() );
}

void MainWindow::ataque_boss()
{
    Scene->removeItem(boss);
    balas_ene.append(new ataques_enemigos(0, 0, 1));
    Scene->addItem(balas_ene.back());
    Scene->addItem(boss);
}


void MainWindow::juego_terminado()
{
    ui->gameover->  show();
    ui->salir_menu->show();

    timer->             stop();
    tiempo_enemigos->   stop();
    tiempo_nubes->      stop();
}


void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    //                                  MOVIMIENTO PERSONAJE 1
    if( evento->key()==Qt::Key_W ){
        cuerpo->salto();
    }
    if( evento->key()==Qt::Key_D ){
        cuerpo->setVx(5);
    }
    if( evento->key()==Qt::Key_A ){
        cuerpo->setVx(-5);
    }
    if( evento->key()==Qt::Key_E ){
        balas.append(new ataques(cuerpo->getPosx()+20, -cuerpo->getPosy(), 0));
        Scene->addItem(balas.back());
    }

    //                                  MOVIMIENTO PERSONAJE 2
    if ( multijugador == true ){
        if( evento->key()==Qt::Key_I ){
            cuerpo2->salto();
        }
        if( evento->key()==Qt::Key_L ){
            cuerpo2->setVx(5);
        }
        if( evento->key()==Qt::Key_J ){
            cuerpo2->setVx(-5);
        }
        if( evento->key()==Qt::Key_K ){
            balas.append(new ataques(cuerpo2->getPosx()+20, -cuerpo2->getPosy(), 0));
            Scene->addItem(balas.back());
        }
    }

    //                                  TECLAS DE EVENTOS
    if( evento->key()==Qt::Key_P ){
        timer->stop();
        tiempo_enemigos->stop();
        tiempo_nubes->stop();
        tiempo_ata_jefe->stop();

        ui->salir_menu->show();
        ui->continuar->show();
    }
}


//                                              BOTONES USADOS
void MainWindow::on_Empezar_clicked()
{
    cuerpo = new personaje();
    Scene->addItem(cuerpo);

    timer->start(15);
    tiempo_enemigos->start(3000);
    tiempo_nubes->start(20000);

    ui->lcdNumber->     show();
    ui->nombre_1->      show();
    ui->progressBar_1-> show();

    ui->Empezar->       hide();
    ui->multijugador->  hide();

    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/imag/fondo.png")));
}

void MainWindow::on_continuar_clicked()
{
    timer->start(15);
    tiempo_enemigos->start(2000);

    ui->continuar->hide();
    ui->salir_menu->hide();

}

void MainWindow::on_salir_menu_clicked()
{
    //              PARAR LOS RELOJES
    timer->stop();
    tiempo_enemigos->stop();

    //              PARA LIMPIAR LISTAS
    balas.clear();
    balas_ene.clear();
    enemy.clear();
    Scene->clear();

    //              MOSTRAR BOTONES NECESARIOS
    ui->Empezar->       show();
    ui->multijugador->  show();
    ui->lcdNumber->     hide();
    ui->nombre_1->      hide();
    ui->nombre_2->      hide();
    ui->progressBar_1-> hide();
    ui->progressBar_2-> hide();
    ui->continuar->     hide();
    ui->salir_menu->    hide();
    ui->gameover->      hide();

    multijugador = 0;
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/imag/intro.jpg")));
}

void MainWindow::on_multijugador_clicked()
{
    multijugador = 1;

    cuerpo = new personaje();
    Scene->addItem(cuerpo);

    cuerpo2 = new personaje2();
    Scene->addItem(cuerpo2);

    timer->start(15);
    tiempo_enemigos->start(1000);
    tiempo_nubes->start(8000);

    ui->lcdNumber->         show();
    ui->nombre_1->      show();
    ui->nombre_2->      show();
    ui->progressBar_1-> show();
    ui->progressBar_2-> show();

    ui->Empezar->hide();
    ui->multijugador->hide();

    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/imag/intro.jpg")));
}
