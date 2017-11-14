#include "manager.h"

Manager* Manager::instancia = NULL;

Manager::Manager(QObject *parent) : QObject(parent),login(new Login), ventana(new Ventana) , formulario(new Formulario)
  , start(new Start)
{

    map = new Mapa;
    loc = new Localizacion;
    sites = new Sites;
    siteroute = new SitesRoute;
    infolugar = new InfoLugar;
    BNombre = new BusquedaNombre;

    connect(start,SIGNAL(signal_ready(bool)),this,SLOT(slot_ShowLogin(bool)));

    connect(login,SIGNAL(signal_ShowFormulario(bool)),this,SLOT(slot_ShowFormulario(bool)));

    connect(login,SIGNAL(signal_ShowVentana(bool)),this,SLOT(slot_ShowVentana(bool)));

    connect(formulario,SIGNAL(signal_ShowLogin(bool)),this,SLOT(slot_ShowLogin(bool)));


    connect(ventana,SIGNAL(signal_IniciaBusqueda()),this,SLOT(slot_RealizaBusqueda()));
    connect(ventana,SIGNAL(signal_IniciaInfo(QModelIndex)),this,SLOT(slot_IniciaInfo(QModelIndex)));
    connect(ventana,SIGNAL(signal_IndexCombo(int)),this,SLOT(slot_RecibIndexCombo(int)));
    connect(ventana,SIGNAL(signal_IniciaBusquedaPalabra(QString)),this,SLOT(slot_IniciaBusquedaPalabra(QString)));
    connect(ventana,SIGNAL(signal_Estado(int,QString)),this,SLOT(slot_ZoomMapa(int,QString)));

    ////


    connect(sites,SIGNAL(signal_listadoLugares(QStringList,QStringList,QStringList)),this,SLOT(slot_RecibListado(QStringList,QStringList,QStringList)));
    connect(infolugar,SIGNAL(signal_listadoInfo(QStringList)),this,SLOT(slot_RecibInfo(QStringList)));
    connect(BNombre,SIGNAL(signal_listadoBusqueda(QStringList,QStringList,QStringList)),this,SLOT(slot_RecibListado(QStringList,QStringList,QStringList)));
    connect(siteroute,SIGNAL(signal_listadoRuta(QStringList)),this,SLOT(slot_RecibRuta(QStringList)));
    connect(map,SIGNAL(signal_MandaMapa(QImage)),this,SLOT(slot_RecibMapa(QImage)));
    connect(siteroute,SIGNAL(signal_MandaMapaRuta(QImage)),this,SLOT(slot_RecibMapa(QImage)));
}

void Manager::Iniciar()
{
    start->show();
}

Manager *Manager::getInstancia()
{


    if(instancia == NULL )
    {
        instancia = new Manager();
    }

    return instancia;
}

Manager::~Manager()
{
    if(instancia != NULL )
    {
        delete instancia;
    }
}


void Manager::slot_ShowLogin(bool estado)
{
    if(estado)
    {
        login->show();
    }
}

void Manager::slot_ShowFormulario(bool estado)
{

    if(estado)
    {
        formulario->show();
    }
}

void Manager::slot_ShowVentana(bool estado)
{
    if(estado)
    {
        ventana->show();
    }
}

void Manager::slot_IniciaInfo(QModelIndex index)
{
    infolugar->getInfoLugar(listIdLugares.at(index.row()));
}

void Manager::slot_IniciaBusquedaPalabra(QString palabra)
{
    if(tipo == 1)
    {
        BNombre->getBusquedaNombre("-31.4197583","-64.1890037","bar",palabra);
    }
    if(tipo == 2)
    {
        BNombre->getBusquedaNombre("-31.4197583","-64.1890037","night_club",palabra);
    }
    if(tipo == 3)
    {
        BNombre->getBusquedaNombre("-31.4197583","-64.1890037","restaurant",palabra);
    }
    if(tipo == 4)
    {
        BNombre->getBusquedaNombre("-31.4197583","-64.1890037","casino",palabra);
    }
    if(tipo == 5)
    {
        BNombre->getBusquedaNombre("-31.4197583","-64.1890037","museum",palabra);
    }

    if(tipo == 6)
    {
        BNombre->getBusquedaNombre("-31.4197583","-64.1890037","movie_theater",palabra);
    }
}

void Manager::slot_ZoomMapa(int estado, QString zoom)
{
    if(estado == 1)
    {
        map->getMapa("-31.4197583","-64.1890037",zoom,listLatLonLugares);
    }

    if(estado == 2)
    {
        siteroute->getMapaRuta(listLatLonLugares,zoom);
    }
}

void Manager::slot_RealizaBusqueda()
{
    //"-31.4197583","-64.1890037"

    if(tipo == 1)
    {
        sites->getSites("-31.4197583","-64.1890037","bar");

    }
    if(tipo == 2)
    {
        sites->getSites("-31.4197583","-64.1890037","night_club");

    }
    if(tipo == 3)
    {
        sites->getSites("-31.4197583", "-64.1890037", "restaurant");

    }
    if(tipo == 4)
    {
        sites->getSites("-31.4197583", "-64.1890037", "casino");

    }
    if(tipo == 5)
    {
        sites->getSites("-31.4197583","-64.1890037","museum");

    }

    if(tipo == 6)
    {
        sites->getSites("-31.4197583","-64.1890037","movie_theater");

    }


}

void Manager::slot_RecibListado(QStringList listName, QStringList listLatLon, QStringList listPlaceId)
{
    listIdLugares.clear();
    listLatLonLugares.clear();

    listIdLugares = listPlaceId;

    listLatLonLugares = listLatLon;

    ventana->SetListadoLugares(listName);

    map->getMapa("-31.4197583","-64.1890037","10",listLatLonLugares);


}

void Manager::slot_RecibInfo(QStringList info)
{

    siteroute->getRuta("-31.4197583","-64.1890037",info.at(6),info.at(7));

    info.removeAt(6);
    info.removeAt(6);

    ventana->SetInfoLugar(info);
}


void Manager::slot_RecibIndexCombo(int index)
{
    tipo=index;
}

void Manager::slot_RecibRuta(QStringList listRuta)
{
     QString Distancia;

     listLatLonLugares.clear();

     Distancia=listRuta.at(0);
     Distancia+=" - ";
     Distancia+=listRuta.at(1);

     ventana->SetDistancia(Distancia);

     listRuta.removeAt(0);
     listRuta.removeAt(0);

     listLatLonLugares = listRuta;

     siteroute->getMapaRuta(listLatLonLugares,"10");

}

void Manager::slot_RecibMapa(QImage im)
{
    MapaPrueba = im;

    ventana->SetMapa(MapaPrueba);
}

