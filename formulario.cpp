#include "formulario.h"
#include "ui_formulario.h"


Formulario::Formulario(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formulario)
{
    ui->setupUi(this);

    im_fondoform.load(":/root/Recursos/images/startsiluetablue.jpg");

    if(im_fondoform.isNull())
    {
         qDebug()<<"Esta vacia";
    }

    this->setWindowTitle("NIGHTAPP");

    admin = new AdminDB();

    manager = new QNetworkAccessManager;


    ui->le_pass->setEchoMode(QLineEdit::Password);

    connect(ui->pb_register,SIGNAL(clicked()),this,SLOT(slot_registerOnline()));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_Reply(QNetworkReply*)));

}

Formulario::~Formulario()
{
    delete ui;
}

void Formulario::resizeEvent(QResizeEvent *e)
{
    ui->tb_title->resize(this->width(),this->height()/10);
    ui->tb_title->move(0,ui->tb_title->height());

    ui->le_name->resize(this->width(),this->height()/15);
    ui->le_name->move(0,ui->le_name->height() + ui->tb_title->height() + this->height()/10);

    ui->le_surname->resize(this->width(),this->height()/15);
    ui->le_surname->move(0,ui->le_surname->height() + ui->le_name->height() + ui->tb_title->height() + this->height()/10);

    ui->le_telephone->resize(this->width(),this->height()/15);
    ui->le_telephone->move(0,ui->le_surname->height() + ui->le_name->height() + ui->tb_title->height() + this->height()/10 + ui->le_telephone->height());

    ui->le_mail->resize(this->width(),this->height()/15);
    ui->le_mail->move(0,ui->le_surname->height() + ui->le_name->height() + ui->tb_title->height() + this->height()/10 + ui->le_telephone->height() + ui->le_mail->height());

    ui->le_user->resize(this->width(),this->height()/15);
    ui->le_user->move(0,ui->le_surname->height() + ui->le_name->height() + ui->tb_title->height() + this->height()/10 + ui->le_telephone->height() + ui->le_mail->height() +ui->le_user->height());

    ui->le_pass->resize(this->width(),this->height()/15);
    ui->le_pass->move(0,ui->le_surname->height() + ui->le_name->height() + ui->tb_title->height() + this->height()/10 + ui->le_telephone->height() + ui->le_mail->height() +ui->le_user->height() + ui->le_pass->height());

    ui->pb_register->resize(this->width()/3,this->height()/10);
    ui->pb_register->move(this->width()/3,this->height() - ui->pb_register->height());
}

void Formulario::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QImage imform = im_fondoform.scaled(this->width(),this->height());
    painter.drawImage(0,0,imform);
}

void Formulario::slot_verPass(bool a){

    if(a==false){

      ui->le_pass->setEchoMode(QLineEdit::Normal);

    }
}

void Formulario::slot_noverPass(bool a){

    if(a==false){

        ui->le_pass->setEchoMode(QLineEdit::Password);

    }
}


void Formulario::slot_registerOnline()
{

    if(!ui->le_user->text().isEmpty() && !ui->le_mail->text().isEmpty() && !ui->le_pass->text().isEmpty()){

        manager->get(QNetworkRequest(QUrl("https://juan-pablo7.000webhostapp.com/registro.php?name=" + ui->le_name->text() + ""
                                          "&surname=" + ui->le_surname->text() + ""
                                          "&tel= "+ ui->le_telephone->text() +""
                                          "&mail=" + ui->le_mail->text() +""
                                          "&user=" +ui->le_user->text() + ""
                                          "&pass=" + ui->le_pass->text()+""
                                          "&key=0713&tabla=usuarios")));
    }

    else
    {
      QMessageBox::information(this,"NIGHTAPP", "Algunos de los campos esta incompletos!!");

    }

}

void Formulario::slot_Reply(QNetworkReply *reply)
{

    if(reply->readAll() == "Registro exitoso")
    {
        QMessageBox::information(this,"NIGHTAPP", "Registro Completo!");

        this->close();

        emit signal_ShowLogin(true);
    }
    else {
        QMessageBox::information(this,"NIGHTAPP", "ERROR!");
    }

}

