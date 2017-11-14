#ifndef SITESROUTE_H
#define SITESROUTE_H

#include <QWidget>
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
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
#include <QStringList>


class SitesRoute : public QWidget
{
    Q_OBJECT
public:
    explicit SitesRoute(QWidget *parent = 0);

    void getRuta(QString Olat, QString Olon, QString Dlat, QString Dlon);

    void getMapaRuta(QStringList listCoord,QString valor);

private:
    QNetworkAccessManager *ManagerRuta , *ManagerMapaRuta;
    QImage imMapaRuta;
    QJsonDocument replyJsonDocum;
    QStringList listaConRuta;

protected:
        void paintEvent(QPaintEvent *);

private slots:

        void slot_getRuta(QNetworkReply *reply);

        void slot_getMapaRuta(QNetworkReply *reply);


signals:
        void signal_listadoRuta(QStringList);

        void signal_MandaMapaRuta(QImage);


};

#endif // SITESROUTE_H
