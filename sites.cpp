#include "sites.h"

Sites::Sites(QWidget *parent) : QWidget(parent)
{
    ManagerSites = new QNetworkAccessManager;

    connect(ManagerSites,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_getSites(QNetworkReply*)));
}

void Sites::slot_getSites(QNetworkReply *reply)
{

    QStringList listName,listLatLon,listPlaceId;

    replyJsonDocum = QJsonDocument::fromJson(reply->readAll());

    QJsonArray replyJsonArray = replyJsonDocum.object().value("results").toArray();

    for(int i=0;i<replyJsonArray.size();i++)
    {
        QJsonValue geo = replyJsonArray.at(i).toObject().take("geometry");

        QJsonObject loc = geo.toObject().take("location").toObject();

        listName.append(replyJsonArray.at(i).toObject().take("name").toString());
        listPlaceId.append(replyJsonArray.at(i).toObject().take("place_id").toString());
        listLatLon.append(QString::number(loc.take("lat").toDouble()));
        listLatLon.append(QString::number(loc.take("lng").toDouble()));
    }



    emit signal_listadoLugares(listName,listLatLon,listPlaceId);

}


void Sites::getSites(QString punt_lat, QString punt_long, QString tipo)
{
    ManagerSites->get(QNetworkRequest(QUrl("https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=" + punt_lat + "," + punt_long + "&radius=500&types=" + tipo + "&key=AIzaSyCWkS32Vvd6wBepLJkNJfRxELfXQOw8NFg")));
}
