#include "sitesroute.h"

SitesRoute::SitesRoute(QWidget *parent) : QWidget(parent)
{
    ManagerRuta = new QNetworkAccessManager;
    ManagerMapaRuta = new QNetworkAccessManager;

    connect(ManagerRuta,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_getRuta(QNetworkReply*)));
    connect(ManagerMapaRuta,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_getMapaRuta(QNetworkReply*)));
}

void SitesRoute::getRuta(QString Olat, QString Olon, QString Dlat, QString Dlon)
{
    ManagerRuta->get(QNetworkRequest(QUrl("https://maps.googleapis.com/maps/api/directions/json?origin=" + Olat + "," + Olon + "&destination= " + Dlat + "," + Dlon + "&key=AIzaSyC5B1slkQH2LvD3kB3Ifsin47Tex52cri0")));
}

void SitesRoute::getMapaRuta(QStringList listCoord, QString valor)
{

    QString partBase ="https://maps.googleapis.com/maps/api/staticmap?";

    QString partMedia = "&size=6220x541&zoom=" + valor + "&path=";

    int latDes=listCoord.size()-2;
    int lonDes=listCoord.size()-1;

    QString partFinal = "&markers=color:red|label:O|" + listCoord.at(0) + "," + listCoord.at(1) + "&markers=color:blue|label:D|" +listCoord.at(latDes)+ "," + listCoord.at(lonDes)+ "";

    for(int i=0;i<listCoord.size();i++)
    {
        partMedia = partMedia + listCoord.at(i) + "," + listCoord.at(i+1) + "|";
        i++;
    }


    partMedia.chop(1);

    partBase += partMedia;

    partBase += partFinal;

    ManagerMapaRuta->get(QNetworkRequest(QUrl(partBase)));
}

void SitesRoute::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0,0,imMapaRuta);
}

void SitesRoute::slot_getRuta(QNetworkReply *reply)
{
    QStringList list;


    replyJsonDocum = QJsonDocument::fromJson(reply->readAll());

    QJsonArray jsonArray = replyJsonDocum.object().value("routes").toArray();


    for(int i=0; i<jsonArray.size();i++)
    {
        QJsonArray jsonArrayLegs = jsonArray.at(i).toObject().value("legs").toArray();

        list.append(jsonArrayLegs.at(i).toObject().take("distance").toObject().value("text").toString());
        list.append(jsonArrayLegs.at(i).toObject().take("duration").toObject().value("text").toString());

        for(int j=0;j<jsonArrayLegs.size();j++)
        {
            QJsonArray jsonArraySteps = jsonArrayLegs.at(j).toObject().value("steps").toArray();

            for(int n=0;n<jsonArraySteps.size();n++)
            {
                QJsonObject jsonArrayStartEnd = jsonArraySteps.at(n).toObject().value("start_location").toObject();
                list.append(QString::number(jsonArrayStartEnd.value("lat").toDouble()));
                list.append(QString::number(jsonArrayStartEnd.value("lng").toDouble()));

                jsonArrayStartEnd = jsonArraySteps.at(n).toObject().value("end_location").toObject();
                list.append(QString::number(jsonArrayStartEnd.value("lat").toDouble()));
                list.append(QString::number(jsonArrayStartEnd.value("lng").toDouble()));
            }
        }
    }

    emit signal_listadoRuta(list);

}

void SitesRoute::slot_getMapaRuta(QNetworkReply *reply)
{
    imMapaRuta = QImage::fromData(reply->readAll());

    emit signal_MandaMapaRuta(imMapaRuta);
    //this->repaint();
}
