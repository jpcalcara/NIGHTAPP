#include "ventana.h"
#include "ui_ventana.h"

#include <QPainter>

Ventana::Ventana(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ventana)
{
    ui->setupUi(this);

    im_fondoven.load(":/root/Recursos/images/startsiluetablue.jpg");

    if(im_fondoven.isNull()){
        qDebug()<<"Esta vacia";
    }

    timer = new QTimer;

    timer->setInterval(500);

    ui->info->close();

    ui->le_search->setDiccionario("palabras");

    ui->TimeAndDistance->hide();

    connect(ui->pb_update,SIGNAL(pressed()),this,SLOT(slot_ActualizaPos()));
    connect(ui->cb_categories,SIGNAL(activated(int)),this,SLOT(slot_comboBox(int)));
    connect(ui->lw_listplaces,SIGNAL(activated(QModelIndex)),this,SLOT(slot_ActivaListado(QModelIndex)));
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_time()));
    connect(ui->info, SIGNAL(signal_clic()), ui->info, SLOT(close()));

}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QImage imVen = im_fondoven.scaled(this->width(),this->height());
    painter.drawImage(0,0,imVen);
    painter.drawImage(25,ui->le_search->height()+10,imMap);

}

void Ventana::SetListadoLugares(QStringList lugares)
{
    ui->lw_listplaces->clear();

    ui->lw_listplaces->addItems(lugares);

    ui->lw_listplaces->setVisible(true);

}

void Ventana::SetInfoLugar(QStringList info2)
{
    QString data;

    for(int i=0; i<info2.size(); i++)
    {
        data += info2.at(i) + " ";
    }

    ui->info->setTexto(data);
}

void Ventana::SetDistancia(QString distancia)
{

    ui->TimeAndDistance->clear();
    ui->TimeAndDistance->show();
    ui->TimeAndDistance->setText(distancia);
}

void Ventana::SetMapa(QImage im)
{
    imMap = im;

    this->repaint();
}


void Ventana::slot_comboBox(int i)
{
    emit signal_IndexCombo(i);
}

void Ventana::slot_ActualizaPos()
{
    zoom = 10;

    estado=1;

    ui->TimeAndDistance->hide();


    if(ui->le_search->text().isEmpty())
    {
        emit signal_IniciaBusqueda();
    }

    else {

        emit signal_IniciaBusquedaPalabra(ui->le_search->text());

    }

}

void Ventana::slot_ActivaListado(QModelIndex index)
{
    zoom = 10;

    estado=2;

    ui->info->show();

    emit signal_IniciaInfo(index);
}

void Ventana::slot_time()
{
   if(zoom>10)
    {
        timer->stop();

        zoom--;

        emit signal_Estado(estado,QString::number(zoom));
   }
}


void Ventana::mouseDoubleClickEvent(QMouseEvent *e)
{
    timer->stop();

    if(zoom<20)
    {
        zoom++;

        emit signal_Estado(estado,QString::number(zoom));
    }

}

void Ventana::mousePressEvent(QMouseEvent *e)
{
    timer->start();
}

void Ventana::dimensionarWidget()  {

    ui->pb_update->resize(this->width()/3,this->height()/5);
    ui->pb_update->move(this->width()/3,this->height()- ui->pb_update->height());

    ui->cb_categories->resize(this->width()/7,this->height()/7);
    ui->cb_categories->move(this->width()- ui->cb_categories->width(),0);

    ui->le_search->resize(this->width()-ui->cb_categories->width(),this->height()/7);
    ui->le_search->move(0,0);


    //ui->textEdit->resize(this->width()/3,this->height()/3);
    //ui->textEdit->move(this->width()/3,this->height() - ui->lw_listplaces->height() - ui->pb_update->height() - ui->textEdit->height());

    ui->lw_listplaces->resize(this->width(),this->height()/5);
    ui->lw_listplaces->move(0,this->height()-ui->pb_update->height()-ui->lw_listplaces->height());

    //ui->TimeAndDistance->resize(this->width()/3,this->height()/10);
    //ui->TimeAndDistance->move(0,this->height()-ui->pb_update->height()-ui->lw_listplaces->height()- ui->textEdit->height()-ui->TimeAndDistance->height());

}

void Ventana::resizeEvent(QResizeEvent *e)
{
    dimensionarWidget();
}
 
