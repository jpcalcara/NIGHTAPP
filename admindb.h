#ifndef ADMINDB
#define ADMINDB


#include <QObject>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QStringList>
#include <QVector>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QVariant>



class AdminDB : public QObject  {
        Q_OBJECT

public:
        AdminDB();
        ~AdminDB();

        /**
         * @brief especifica la conexion con la DB
         */
        bool conectar(QString nombreBase);

        /**
         * @brief inserta los datos en la DB
         */
        bool insertLog(QString usuario,QString clave, QString nombre, QString apellido, QString cel, QString mail);

private:
        QSqlDatabase db;

public:
        /**
         * @brief realiza una consulta a la DB
         */
        QVector <QStringList> select(QString comando);

        QSqlDatabase getDb() const;

        void setDb(const QSqlDatabase &value);
};
#endif // ADMINDB

