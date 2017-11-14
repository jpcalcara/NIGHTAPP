#include "usuario.h"

Usuario::Usuario()
{
    adminDB = new AdminDB;
    adminDB->conectar(":/root/Recursos/database/usuarios.sqlite");
}

//Getters
int Usuario::getId()
{
    return id;
}

QString Usuario::getName()
{
    return name;
}

QString Usuario::getSurname()
{
    return surname;
}

QString Usuario::getTelephone()
{
    return telephone;
}

QString Usuario::getMail()
{
    return mail;
}

QString Usuario::getUser()
{
    return user;
}

QString Usuario::getPass()
{
    return pass;

}


//Setters
void Usuario::setId(int ide)
{
    id=ide;
}

void Usuario::setName(QString nm)
{
    name=nm;
}

void Usuario::setSurname(QString sn)
{
    surname=sn;
}

void Usuario::setTelephone(QString tl)
{
    telephone=tl;
}

void Usuario::setMail(QString em)
{
    mail=em;
}

void Usuario::setUser(QString us)
{
    user=us;
}

void Usuario::setPass(QString ps)
{
    pass=ps;
}
