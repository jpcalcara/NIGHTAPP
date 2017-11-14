#include "infolugar.h"

InfoLugar::InfoLugar(QWidget *parent) : QWidget(parent)
{
    ManagerInfo = new QNetworkAccessManager;

    connect(ManagerInfo,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_getInfoLugar(QNetworkReply*)));
}

void InfoLugar::getInfoLugar(QString lugar)
{
    ManagerInfo->get(QNetworkRequest(QUrl("https://maps.googleapis.com/maps/api/place/details/json?placeid=" + lugar + "&key=AIzaSyA1QSFl8jq6hN54GEzIfA1AnInqrQWbUUA")));
}

void InfoLugar::slot_getInfoLugar(QNetworkReply *reply)
{
    QStringList list;

    replyJsonDocum = QJsonDocument::fromJson(reply->readAll());


    QJsonValue valor = replyJsonDocum.object().value("result").toObject();

    list.append(valor.toObject().value("name").toString());
    list.append(valor.toObject().value("vicinity").toString());
    list.append(valor.toObject().value("website").toString());
    list.append(valor.toObject().value("formatted_phone_number").toString());
    list.append(QString::number(valor.toObject().take("opening_hours").toObject().value("open_now").toBool()));
    list.append(QString::number(valor.toObject().value("rating").toDouble()));
    QJsonArray jsonArrayWeek =valor.toObject().take("opening_hours").toObject().value("weekday_text").toArray();

    list.append(QString::number(valor.toObject().take("geometry").toObject().take("location").toObject().value("lat").toDouble()));
    list.append(QString::number(valor.toObject().take("geometry").toObject().take("location").toObject().value("lng").toDouble()));

    for(int i=0;i<jsonArrayWeek.size();i++)
    {
        list.append(jsonArrayWeek.at(i).toString());
    }
   /* // REFERENCIAS DEL LUGAR

    QJsonArray ArrayReviews=valor.toObject().take("reviews").toArray();

    for(int n=0;n<ArrayReviews.size();n++)
    {
        list.append(ArrayReviews.at(n).toObject().value("-Referencia-").toString());
        list.append(ArrayReviews.at(n).toObject().value("author_name").toString());
        list.append(ArrayReviews.at(n).toObject().value("text").toString());
    }
    */
    if(list.at(4)=="0")
    {
        list.removeAt(4);
        list.insert(4,"Cerrado");
    }

    if (list.at(4)=="1")
    {
        list.removeAt(4);
        list.insert(4,"Abierto");
    }

    emit signal_listadoInfo(list);
}
