#ifndef LOCALIZACION_H
#define LOCALIZACION_H

#include <QObject>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QGeoPositionInfoSource>

class Localizacion : public QWidget
{
    Q_OBJECT
public: explicit Localizacion(QWidget *parent = 0);

    float getAltitud(){
        return alt;
    }

    float getLongitud(){
        return lon;
    }

    /**
     * @brief getLatLongGPS Devuelve la posicion que da el GPS
     * @return QStringList con 2 parametros latitud y longitud
     */
    QStringList getLatLongGPS();

    /**
     * @brief getDomicilioActual devuelve el domicilio de donde se encuentra el dispositivo.
     * @return
     */
    void getDomicilioActual();

    /**
    * @brief pedirDomicilio Metodo que puede usarse desde otra clase, por ejemplo, Ventana, para que localizacion solicite a Google
    * el domicilio correspondiente a la latitud y longitud.
    * @param latitud
    * @param longitud
    */
    void pedirDomicilio(double latitud, double longitud);

private:
       QNetworkAccessManager *manager;
       double alt;
       double lon;

signals:

    /**
     * @brief signal_domicilioObtenido es emitira desde el slot_solicitudFinalizada una vez  analizado el JSON, y
     * obtenido el domiciio.
     * @param domicilio
     */
     void signal_domicilioObtenido(QString domicilio); //

private slots:

     /**
      * @brief slot_solicitudFinalizada se conocta desde la signal finished(QNetworkReply*), la cual obtiene la respuesta
      * de Google en JSON, y es analizada para obtener el domicilio
      */
     void slot_solicitudFinalizada(QNetworkReply *);

     /**
      * @brief positionUpdated informa la posicion actual donde se encuentra el user.
      */
     void positionUpdated(const QGeoPositionInfo &info);

};

#endif // LOCALIZACION_H
