#include "ventana.h"
#include "ui_ventana.h"

#include <QPainter>

Ventana::Ventana(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ventana),
    teInfo( new QTextEdit( this ) )
{
    ui->setupUi(this);

    im_fondoven.load(":/root/Recursos/images/startsiluetablue.jpg");

    if(im_fondoven.isNull()){
        qDebug()<<"Esta vacia";
    }

    ui->datos_Lugar->hide();

    timer = new QTimer;

    timer->setInterval(500);

    ui->le_search->setDiccionario("palabras");

    ui->TimeAndDistance->hide();

    connect(ui->pb_update,SIGNAL(pressed()),this,SLOT(slot_ActualizaPos()));
    connect(ui->cb_categories,SIGNAL(activated(int)),this,SLOT(slot_comboBox(int)));
    connect(ui->lw_listplaces,SIGNAL(activated(QModelIndex)),this,SLOT(slot_ActivaListado(QModelIndex)));
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_time()));

    teInfo->setWindowFlags( Qt::Window );


    popup = new QTreeWidget;

    popup->setColumnCount(1);
    popup->setRootIsDecorated(false);  // Elimina el lugar del ícono de la izquierda.
    popup->header()->hide();  // Oculta la cabecera
    popup->installEventFilter(this);

    //connect(popup, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT());

    connect(ui->pb_ver,SIGNAL(pressed()),this,SLOT(hola2()));

    popup->setWindowFlags(Qt::Popup);// Para que la ventana sea estilo popup


    connect(timer2,SIGNAL(timeout()),this,SLOT(slot_time2()));



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

void Ventana::SetInfoLugar(QStringList info)
{
    /*ui->lw_listcharac->clear();

    ui->lw_listcharac->addItems(info);

    ui->lw_listcharac->setVisible(true);*/

    popup->clear();

    QTreeWidgetItem * item;

    for (int i = 0; i < info.size(); ++i) {

            item = new QTreeWidgetItem(popup);
            item->setText(0,info.at(i));
            item->setTextAlignment(1, Qt::AlignRight);
            tam= item->text(0).size();
    }



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
    ui->datos_Lugar->hide();



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


    //ui->datos_Lugar->show();

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

void Ventana::hola2()
{

    /*teInfo->resize( this->width()/2, this->height()/3 );
    teInfo->move( this->width() - teInfo->width(), this->height() - teInfo->height() );
    teInfo->show();*/



        popup->resize(this->width()/2,ui->pb_ver->height());

        popup->move(ui->pb_ver->mapToGlobal(QPoint(-(this->width()/2),ui->pb_ver->height())));

        popup->show();
        timer2->start();

}

void Ventana::slot_time2()
{
    popup->close();
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

   ui->pb_update->resize(this->width()/3,this->height()/12);
    ui->pb_update->move(this->width()/3,this->height()- ui->pb_update->height());

    ui->cb_categories->resize(this->width()/3,this->height()/10);
    ui->cb_categories->move(this->width()-ui->cb_categories->width(),0);

    ui->le_search->resize(this->width()-ui->cb_categories->width(),this->height()/10);
    ui->le_search->move(0,0);

    ui->lw_listplaces->resize(this->width(),this->height()/5);
    ui->lw_listplaces->move(0,this->height()-ui->pb_update->height()-ui->lw_listplaces->height());

    //ui->datos_Lugar->resize(this->width(),this->height()/5);
    //ui->datos_Lugar->move(0,this->height()-ui->pb_update->height()-ui->lw_listplaces->height());

    ui->datos_Lugar->move(0,this->height()-ui->pb_update->height()-ui->lw_listplaces->height()-ui->datos_Lugar->height());

    ui->TimeAndDistance->resize(this->width()/3,this->height()/18);
    ui->TimeAndDistance->move(this->width()/10,this->height()-ui->pb_update->height()-ui->lw_listplaces->height()-ui->datos_Lugar->height()-ui->TimeAndDistance->height());
}

void Ventana::resizeEvent(QResizeEvent *e)
{
    dimensionarWidget();
}
