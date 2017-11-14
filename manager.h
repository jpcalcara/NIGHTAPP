#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QStringList>
#include <QDebug>
#include <QVector>

#include "login.h"
#include "ventana.h"
#include "formulario.h"
#include "start.h"


#include "localizacion.h"
#include "mapa.h"
#include "lineadetexto.h"
#include "busquedanombre.h"
#include "infolugar.h"
#include "sites.h"
#include "sitesroute.h"


class Mapa;
class Sites;
class SitesRoute;
class InfoLugar;
class BusquedaNombre;
class Localizacion;

class Manager : public QObject
{
    Q_OBJECT

public:
    void Iniciar();
    static Manager *getInstancia();
    ~Manager();

private slots:
    void slot_ShowLogin(bool estado);
    void slot_ShowFormulario(bool estado);
    void slot_ShowVentana(bool estado);

    void slot_IniciaInfo(QModelIndex index);
    void slot_IniciaBusquedaPalabra(QString palabra);
    void slot_ZoomMapa(int estado, QString zoom);

    void slot_RealizaBusqueda();
    void slot_RecibListado(QStringList listName,QStringList listLatLon,QStringList listPlaceId);
    void slot_RecibInfo(QStringList info);
    void slot_RecibIndexCombo(int index);
    void slot_RecibRuta(QStringList listRuta);
    void slot_RecibMapa(QImage im);

signals:
    void signal_MandaIm(QImage);

private:
    Login *login;
    Ventana *ventana;
    Formulario *formulario;
    Start *start;
    static Manager *instancia;

    QImage MapaPrueba;
    QImage MapaRutaPrueba;


    //Se lo pone como privado al constructor para que nadie pueda acceder
    explicit Manager(QObject *parent = 0);

    Mapa *map;
    Localizacion *loc;
    Sites *sites;
    SitesRoute *siteroute;
    InfoLugar *infolugar;
    BusquedaNombre *BNombre;



    QStringList listIdLugares,listLatLonLugares;
    int tipo;

};

#endif // MANAGER_H
