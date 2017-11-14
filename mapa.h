#ifndef MAPA_H
#define MAPA_H

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


class Mapa : public QWidget
{
    Q_OBJECT

public:
    explicit Mapa(QWidget *parent = 0);
    ~Mapa();

    void getMapa(QString latitud,QString longitud,QString valor, QStringList listUbicacion);

    QImage GetImagenMapa();

private:
    QImage im;
    QNetworkAccessManager *ManagerMapa;
    QImage imMapa;

signals:
    void signal_MandaMapa(QImage);

protected:
        void paintEvent(QPaintEvent *);

private slots:
        void slot_procesarRespuesta(QNetworkReply * reply);

};

#endif // MAPA_H
