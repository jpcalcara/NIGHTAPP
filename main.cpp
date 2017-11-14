#include "manager.h"

#include <QApplication>
#include <QNetworkProxyFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QNetworkProxyFactory::setUseSystemConfiguration(true);

    Manager::getInstancia()->Iniciar();

    return a.exec();
}
