#ifndef SITES_H
#define SITES_H

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

class Sites : public QWidget
{
    Q_OBJECT
public:
    explicit Sites(QWidget *parent = 0);
    void getSites(QString punt_lat, QString punt_long, QString tipo);

signals:

private slots:
    void slot_getSites(QNetworkReply *reply);

private:
    QNetworkAccessManager *ManagerSites;
    QJsonDocument replyJsonDocum;

signals:
    void signal_listadoLugares(QStringList,QStringList,QStringList);
};

#endif // SITES_H
