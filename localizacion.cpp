#include "localizacion.h"

Localizacion::Localizacion(QWidget *parent) : QWidget(parent)
{
    QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(this);

    if (source) {
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),this, SLOT(positionUpdated(QGeoPositionInfo)));

        source->startUpdates();
    }

    manager = new QNetworkAccessManager;

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_solicitudFinalizada(QNetworkReply *)));
}

void Localizacion::slot_solicitudFinalizada(QNetworkReply *reply)
{
    QByteArray ba = reply->readAll();

    int indiceComienzo = ba.indexOf("formatted_address");
    int indiceFin1 = ba.indexOf("X");
    int indiceFin2 = ba.indexOf("Córdoba");
    int inx1, inx2;

    if(indiceFin1<indiceFin2)
    {
        inx1 = (indiceFin1 - 20) - indiceComienzo;
    }
    else
    {
        inx1 =(indiceFin2 - 20) - indiceComienzo;
    }

    inx2 =indiceComienzo + 18;
    QString direccion = ba.mid(inx2,inx1);

    emit signal_domicilioObtenido(direccion);
}

void Localizacion::positionUpdated(const QGeoPositionInfo &info)
{
    alt=info.coordinate().latitude();
    lon=info.coordinate().longitude();
}

void Localizacion::pedirDomicilio(double ll, double lg)
{
    QString a = QString::number(ll);
    QString b = QString::number(lg);

    manager->get(QNetworkRequest(QUrl("https://maps.googleapis.com/maps/api/geocode/xml?latlng=" + a + "," + b+ "&key=AIzaSyAiMFncByo2gYEkkUepKtVFsXLOZIu6TIw")));


}

QStringList Localizacion::getLatLongGPS()
{
      QStringList cord;
      QString a = QString::number(alt);
      QString b = QString::number(lon);
      cord << a << b;
      return cord;
}

void Localizacion::getDomicilioActual()
{
    QString a = getLatLongGPS().at(0);
    QString b = getLatLongGPS().at(1);
    pedirDomicilio(a.toDouble(),b.toDouble());
}
