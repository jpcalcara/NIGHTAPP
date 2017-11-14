#include "busquedanombre.h"

BusquedaNombre::BusquedaNombre(QWidget *parent) : QWidget(parent)
{
    ManagerBusqueda = new QNetworkAccessManager;

    connect(ManagerBusqueda,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_getBusquedaNombre(QNetworkReply*)));
}

void BusquedaNombre::getBusquedaNombre(QString lat, QString lon, QString tipo_1, QString nom_busqueda)
{
    ManagerBusqueda->get(QNetworkRequest(QUrl("https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=" + lat + "," + lon + "&rankby=distance&types=" + tipo_1 + "&keyword=" + nom_busqueda + "&key=AIzaSyCWkS32Vvd6wBepLJkNJfRxELfXQOw8NFg")));
}

void BusquedaNombre::slot_getBusquedaNombre(QNetworkReply *reply)
{
    QStringList listName,listLatLon,listPlaceId;

    replyJsonDocum = QJsonDocument::fromJson(reply->readAll());

    QJsonArray jsonArray = replyJsonDocum.object().value("results").toArray();

    for(int i=0;i<jsonArray.size();i++)
    {
        QJsonValue geo = jsonArray.at(i).toObject().take("geometry");

        QJsonObject loc = geo.toObject().take("location").toObject();

        listName.append(jsonArray.at(i).toObject().take("name").toString());
        listPlaceId.append(jsonArray.at(i).toObject().take("place_id").toString());
        listLatLon.append(QString::number(loc.take("lat").toDouble()));
        listLatLon.append(QString::number(loc.take("lng").toDouble()));
    }

    emit signal_listadoBusqueda(listName,listLatLon,listPlaceId);
}
