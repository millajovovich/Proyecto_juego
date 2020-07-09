#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer= new QTimer;

    ui->graphicsView->setScene(Scene);
    Scene->setSceneRect(0,0,800,450);
    Scene->addRect(Scene->sceneRect());

    cuerpo = new personaje();
    Scene->addItem(cuerpo);

    connect(timer,SIGNAL(timeout()),this,SLOT(Mover()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}


void MainWindow::on_pushButton_clicked()
{
    timer->start(15);
}

void MainWindow::Mover()
{
    cuerpo->iteracion();
    cuerpo->calculo();

    //movimiento de las balas
    for( int i=0; i<balas.size();i++ ){
        if ( balas.at(i)->getPosx_bala() > 700 ){
            Scene->removeItem(balas.at(i));                 // para remover de la escena
            balas.removeOne(balas.at(i)) ;                  //para eliminar de la lista
        }
        else
            balas.at(i)->movimiento();
    }

    for( int i=0; i<enemy.size();i++ ){
        if ( enemy.at(i)->getPosx_enemigo() < 50 ){
            Scene->removeItem(enemy.at(i));                 // para remover de la escena
            enemy.removeOne(enemy.at(i));                  //para eliminar de la lista
        }
        else
            enemy.at(i)->movimiento();
    }


    if ( cuerpo->baja_altura() == true )
        cuerpo->salto();
}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if( evento->key()==Qt::Key_W ){
        cuerpo->salto();
    }
    if( evento->key()==Qt::Key_D ){
        cuerpo->setVx(5);
    }
    if( evento->key()==Qt::Key_A ){
        cuerpo->setVx(-5);
    }
    if( evento->key()==Qt::Key_S ){
        balas.append(new ataques(cuerpo->getPosx(), -cuerpo->getPosy()));
        Scene->addItem(balas.back());

        enemy.append( new enemigo() );
        Scene->addItem(enemy.back());
    }

}


