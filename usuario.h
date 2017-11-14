#ifndef USUARIO_H
#define USUARIO_H

#include <QString>
#include <QVector>
#include <QtSql/QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>


#include "admindb.h"

class Usuario
{

public:
    Usuario();

    int id;
    QString name;
    QString surname;
    QString telephone;
    QString mail;
    QString user;
    QString pass;

    //creo una base de datos adminDB para consultar los datos del usuario
    AdminDB * adminDB;

    //Getters
     int getId();
     QString getName();
     QString getSurname();
     QString getTelephone();
     QString getMail();
     QString getUser();
     QString getPass();

    //Setters
    void setId(int ide);
    void setName(QString nm);
    void setSurname(QString sn);
    void setTelephone(QString tel);
    void setMail(QString em);
    void setUser(QString us);
    void setPass(QString ps);

};

#endif // USUARIO_H
