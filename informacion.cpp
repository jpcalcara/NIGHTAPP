#include "informacion.h"
#include "ui_informacion.h"
#include <QMouseEvent>
#include <QDebug>

Informacion::Informacion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Informacion)
{
    ui->setupUi(this);
}

Informacion::~Informacion()
{
    delete ui;
}

void Informacion::setTexto(QString texto)
{
    ui->te->setText( texto );
}

void Informacion::mousePressEvent(QMouseEvent *e)
{
    if(Qt::LeftButton || Qt::RightButton)
    {
        emit signal_clic();
    }

}
