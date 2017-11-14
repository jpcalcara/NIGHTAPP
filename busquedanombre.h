#ifndef BUSQUEDANOMBRE_H
#define BUSQUEDANOMBRE_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QUrl>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QList>
#include <QSslSocket>

class BusquedaNombre : public QWidget
{
    Q_OBJECT
public:
    explicit BusquedaNombre(QWidget *parent = 0);
    void getBusquedaNombre(QString lat, QString lon,QString tipo_1,QString nom_busqueda);

signals:

private slots:
     void slot_getBusquedaNombre(QNetworkReply *reply);

private:
    QNetworkAccessManager *ManagerBusqueda;
    QJsonDocument replyJsonDocum;

signals:
    void signal_listadoBusqueda(QStringList,QStringList,QStringList);
};

#endif // BUSQUEDANOMBRE_H
