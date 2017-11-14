#include "mapa.h"


Mapa::Mapa(QWidget *parent) :
    QWidget(parent)
{

    ManagerMapa = new QNetworkAccessManager;

    connect(ManagerMapa, SIGNAL(finished(QNetworkReply *)), this, SLOT(slot_procesarRespuesta(QNetworkReply *)));

}

Mapa::~Mapa()
{

}

void Mapa::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, imMapa.scaled(this->width(), this->height()));
}

void Mapa::getMapa(QString latitud, QString longitud, QString valor, QStringList listUbicacion)
{
    QString base="http://maps.google.com/maps/api/staticmap?center=" + latitud + "," + longitud + "&zoom=" + valor + "&size=400x350&maptype=roadmap";


    QString media="&markers=color:blue|label:A|" + latitud + "," + longitud + "&markers=color:green|label:B|";


    QString final="&sensor=false&key=AIzaSyBCjEj35ftW_ZdpyvSgI2MNsaoVMmXKt9k";

    for(int i=0;i<listUbicacion.size();i++)
    {
        media = media + listUbicacion.at(i) + "," + listUbicacion.at(i+1) + "|";
        i++;
    }

    media.chop(1);
    base+=media;
    base+=final;

    ManagerMapa->get(QNetworkRequest(QUrl(base)));
}

QImage Mapa::GetImagenMapa()
{
    return imMapa;
}

void Mapa::slot_procesarRespuesta(QNetworkReply * reply)
{
    imMapa = QImage::fromData(reply->readAll());

//    emit signal_MandaMapa(imMapa);
    this->repaint();
}
