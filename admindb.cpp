#include "admindb.h"



AdminDB::AdminDB()
{
   db=QSqlDatabase::addDatabase("QSQLITE");

}

AdminDB::~AdminDB()
{

}

bool AdminDB::conectar(QString nombreBase)
{
    db.setDatabaseName(nombreBase);
    if(db.open())
        return true;
    else
        return false;
}

QSqlDatabase AdminDB::getDb() const
{
    return db;
}

void AdminDB::setDb(const QSqlDatabase &value)
{
    db = value;
}

QVector<QStringList> AdminDB::select(QString comando)
{
    QVector<QStringList> registros;

    QSqlQuery query = db.exec( comando );

    while ( query.next() )  {
        QStringList campos;
        QSqlRecord record=query.record();

        for (int i=0 ; i<=6 ; i++)  {
            campos.append(query.value(i).toString());
        }


        registros.append( campos );
    }

    return registros;
}

bool AdminDB::insertLog(QString usuario, QString clave, QString nombre, QString apellido, QString cel, QString mail)
{
   // QByteArray resultado = QCryptographicHash::hash(clave.toAscii(),QCryptographicHash::Md5);
    QSqlQuery query(db);
    return query.exec("INSERT INTO usuario(usuario, clave, nombre, apellido, cel, mail) VALUES ('" + usuario + "', '" + clave + "', '" + nombre + "', '" + apellido + "', '" + cel + "', '" + mail +"')");
}

