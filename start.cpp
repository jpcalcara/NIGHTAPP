#include "start.h"
#include "ui_start.h"
#include <QMessageBox>
#include <QProcess>

Start::Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);

    im_fondoStart.load(":/root/Recursos/images/startsiluetablue.jpg");

    if(im_fondoStart.isNull())
    {
      qDebug()<<"Esta vacia";
    }

    counter = 0;
    intentos = 0;

    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(slot_updateProgressBar())); //timer para la barra de progreso

    timer->start(10);

    manager = new QNetworkAccessManager;
    manager->get(QNetworkRequest(QUrl("https://juan-pablo7.000webhostapp.com/TestConection.php")));
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(slot_procesarConexion(QNetworkReply*)));
}

Start::~Start()
{
    delete ui;
}

void Start::resizeEvent(QResizeEvent *e)
{
    ui->tbLogo->resize(this->width(),this->height()/5);
    ui->tbLogo->move(0,ui->tbLogo->height());

    ui->pbar->resize(this->width()/2,this->height()/20);
    ui->pbar->move(this->width()/4,this->height()/2+ui->pbar->height());
}

void Start::paintEvent(QPaintEvent *){

    QPainter painter(this);
    QImage imStart = im_fondoStart.scaled(this->width(),this->height());
    painter.drawImage(0,0,imStart);

}

void Start::slot_updateProgressBar(){

   /* if(counter <= 100){
       int state = QProcess::execute("ping", QStringList()<<"-n"<<"1"<<"www.google.com.ar");
       if(state==0){
          counter+=10;
          ui->pbar->setValue(counter);
          qDebug()<<"HAY CONEXION";
        }
        else{
            qDebug()<<"NO HAY CONEXION";
            QMessageBox::critical(this,"NO HAY CONEXION!", "Por favor verifica la conexion a internet");
            intentos++;
        }
    }
    else{
        if(counter >= 100){
            this->close();
            timer->stop();
            emit signal_ready(true);
        }
    }
    qDebug()<<intentos;
    if(intentos==3){
        this->close();
    }*/

   /* if(counter <= 100){
           counter++;
           ui->pbar->setValue(counter);
       }
       else{
           if(counter >= 100){
               this->close();
               timer->stop();
               emit signal_ready(true);
           }
    }*/
}

void Start::slot_procesarConexion(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    qDebug()<<data;
    /*    if(data!="" && counter <= 100){
           counter+=100;
           ui->pbar->setValue(counter);
        }
        else{
            QMessageBox::critical(this,"NO HAY CONEXION!", "Por favor verifica la conexion a internet");
            intentos++;
            if(counter >= 100){
              this->close();
              timer->stop();
              emit signal_ready(true);
            }
        }
    qDebug()<<intentos;
    if(intentos==3){
        this->close();
    }*/

    do{
        if(data!="" && counter <= 100){
           counter++;
           ui->pbar->setValue(counter);
        }
        else{
            QMessageBox::critical(this,"NO HAY CONEXION!", "Por favor verifica la conexion a internet");
            intentos++;
           // this->close();
           // if(intentos==3){
                this->close();
            //}
        }
        if(counter >= 100){
          this->close();
          timer->stop();
          emit signal_ready(true);
        }
        qDebug()<<intentos;
    }
    while(counter<100);

}
