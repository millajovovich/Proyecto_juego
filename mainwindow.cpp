#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Scene= new QGraphicsScene;
    timer= new QTimer;

    ui->graphicsView->setScene(Scene);
    Scene->setSceneRect(0,0,670,300);
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

    for( int i=0; i<balas.size();i++ ){
        balas.at(i)->movimiento();
    }

    if ( cuerpo->baja_altura() == true )
        cuerpo->setPosy(1);
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
    }

}


