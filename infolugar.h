#ifndef INFOLUGAR_H
#define INFOLUGAR_H

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

class InfoLugar : public QWidget
{
    Q_OBJECT
public:
    explicit InfoLugar(QWidget *parent = 0);
    void getInfoLugar(QString lugar);

signals:

private slots:
    void slot_getInfoLugar(QNetworkReply *reply);

private:
    QNetworkAccessManager *ManagerInfo;
    QJsonDocument replyJsonDocum;

signals:
    void signal_listadoInfo(QStringList);
};

#endif // INFOLUGAR_H
