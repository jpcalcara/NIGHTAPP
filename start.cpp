#include "start.h"
#include "ui_start.h"

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

    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(slot_updateProgressBar()));

    timer->start(10);
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

    if(counter <= 100){
        counter++;
        ui->pbar->setValue(counter);
    }
    else{
        if(counter >= 100){
            this->close();

            timer->stop();

            emit signal_ready(true);
        }

    }
}
