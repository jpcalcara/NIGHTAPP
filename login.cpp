#include "login.h"
#include "ui_login.h"
#include "admindb.h"
#include <QDebug>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    im_fondo.load(":/root/Recursos/images/startsiluetablue.jpg");

    if(im_fondo.isNull())
    {
         qDebug()<<"Esta vacia";
    }


    ui->le_pass->setEchoMode(QLineEdit::Password);

    connect(ui->pb_initSesion,SIGNAL(pressed()),this,SLOT(slot_validarUsuario()));
    connect(ui->pb_register,SIGNAL(pressed()),this,SLOT(slot_Formulario()));

    usuario =new Usuario();
    jarray=new QJsonArray();
    jdoc=new QJsonDocument();

    manager = new QNetworkAccessManager;
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(slot_procesarRespuesta(QNetworkReply *)));
}

Login::~Login()
{
    delete ui;
}

Usuario Login::getUsuario()
{
    return *usuario;
}

void Login::resizeEvent(QResizeEvent *e)
{
    ui->tb_logo->resize(this->width(),this->height()/10);
    ui->tb_logo->move(0,ui->tb_logo->height());

    ui->le_user->resize(this->width(),this->height()/12);
    ui->le_user->move(0,this->height()/3);

    ui->le_pass->resize(this->width(),this->height()/12);
    ui->le_pass->move(0,this->height()/3 + ui->le_pass->height());

    ui->pb_initSesion->resize(this->width(),this->height()/10);
    ui->pb_initSesion->move(0,this->height()/2 + ui->pb_initSesion->height());



    ui->pb_register->resize(this->width()/3,this->height()/10);
    ui->pb_register->move(this->width()/3,this->height()-ui->pb_register->height());

    ui->l_questionR->resize(this->width(),this->height()/20);
    ui->l_questionR->move(0,this->height() - ui->pb_register->height() - ui->l_questionR->height());

}


void Login::slot_validarUsuario(){

    manager->get(QNetworkRequest(QUrl("https://juan-pablo7.000webhostapp.com/login.php?key=0713&tabla=usuarios")));
}


void Login::slot_procesarRespuesta(QNetworkReply *reply){

    QByteArray data =reply->readAll();

    if(data.contains(ui->le_user->text().toUtf8()) && data.contains(ui->le_pass->text().toUtf8()))
    {
        this->close();

        emit signal_ShowVentana(true);
    }

    else {
        QMessageBox::critical(this,"ERROR", "Usuario o contraseña incorrectos");
    }


}

void Login::slot_Formulario(){

    this->close();

    emit signal_ShowFormulario(true);
}


void Login::slot_verPass(bool a){

    if(a==false){

      ui->le_pass->setEchoMode(QLineEdit::Normal);
    }
}

void Login::slot_noverPass(bool a){

    if(a==false){

        ui->le_pass->setEchoMode(QLineEdit::Password);
    }
}

void Login::slot_infoAutores(){

    QMessageBox::information(this,"NIGHTAPP", "Desarrollado por -NICOLAS HEINZ--J.PABLO CALCARA-");
}

void Login::paintEvent(QPaintEvent *){

    QPainter painter(this);

    QImage imLogin = im_fondo.scaled(this->width(),this->height());

    painter.drawImage(0,0,imLogin);
}

