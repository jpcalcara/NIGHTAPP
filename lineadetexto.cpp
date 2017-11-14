#include "lineadetexto.h"
#include <QIODevice>
#include <QDebug>

LineaDeTexto::LineaDeTexto(QWidget *parent) : QLineEdit( parent )
{
    lista = new QStringList;

    //this->setDiccionario("n");

    this->CrearPopup();
}

LineaDeTexto::LineaDeTexto(QString texto, QWidget *parent) : QLineEdit( texto, parent )
{

}

LineaDeTexto::LineaDeTexto(const LineaDeTexto &linea) : QLineEdit()  {
    this->setText(linea.text());
}

LineaDeTexto& LineaDeTexto::operator = (const LineaDeTexto & linea)  {
    this->setText(linea.text());
    return *this;
}

LineaDeTexto LineaDeTexto::operator +(const LineaDeTexto linea)  {
    LineaDeTexto l;
    l.setText(this->text() + " " + linea.text());
    return l;
}

void LineaDeTexto::CrearPopup()
{
    popup = new QTreeWidget;
    popup->setColumnCount(1);
    popup->setRootIsDecorated(false);  // Elimina el lugar del ícono de la izquierda.
    popup->header()->hide();  // Oculta la cabecera
    popup->installEventFilter(this);

    connect(popup, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(slot_completerLineEdit()));

    popup->setWindowFlags(Qt::Popup);  // Para que la ventana sea estilo popup
    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(1000);

    // Cada 200 mseg busca coincidencias
    connect(timer, SIGNAL(timeout()), SLOT(slot_sugerencias()));
    //connect(ui->leBuscar, SIGNAL(textEdited(QString)), timer, SLOT(start()));
    connect(this, SIGNAL(textEdited(QString)), timer, SLOT(start()));
}

bool LineaDeTexto::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == popup)  {
                   if (e->type() == QEvent::MouseButtonPress) {
                           popup->hide();
                           //ui->leBuscar->setFocus();
                           this->setFocus();
                           return true;
                   }

                   if (e->type() == QEvent::KeyPress) {
                           bool reconocido = false;
                           int key = static_cast<QKeyEvent*>(e)->key();
                           switch (key) {
                           case Qt::Key_Enter:
                           case Qt::Key_Tab:
                           case Qt::Key_Return:
                                   this->slot_completerLineEdit();
                                   reconocido = true;
                                   break;
                           case Qt::Key_Escape:
                                   //ui->leBuscar->setFocus();
                                   this->setFocus();
                                   // Si se presiona escape entonces limpiamos.
                                   //ui->leBuscar->clear();
                                   this->clear();
                                   popup->hide();
                                   reconocido = true;

                           case Qt::Key_Up:
                           case Qt::Key_Down:
                           case Qt::Key_Home:
                           case Qt::Key_End:
                           case Qt::Key_PageUp:
                           case Qt::Key_PageDown:
                                   break;

                           default:
                                   // Hace que permanezca el cursor en el QLineEdit y poder seguir escribiendo
                                   //ui->leBuscar->event(e);
                                   this->event(e);
                                   popup->hide();
                                   break;
                           }
                           return reconocido;
                   }
           }
           return false;
}

void LineaDeTexto::completarPopup(QVector<QStringList> vector)
{
    popup->clear();

    for (int i = 0; i < vector.size(); ++i) {
            QTreeWidgetItem * item;
            item = new QTreeWidgetItem(popup);
            item->setText(0, vector.at(i).at(0));
            item->setText(1, vector.at(i).at(1));
            item->setTextAlignment(1, Qt::AlignRight);  // Para alinear contra la derecha
    }

    popup->setCurrentItem(popup->topLevelItem(0));  // Queda seleccionado el primer elemento

    // Este número 20 es la cantidad de líneas que tiene la lista desplegable
    int h = popup->sizeHintForRow(0) * qMin(20, vector.size()) + 3;

    // El ancho del popup es igual al ancho del QLineEdit
    //popup->resize(ui->leBuscar->width(), h);
    popup->resize(this->width(), h);

    // Lo posiciona justo abajo del QLineEdit
    //popup->move(ui->leBuscar->mapToGlobal(QPoint(0, ui->leBuscar->height())));
    popup->move(this->mapToGlobal(QPoint(0, this->height())));

    popup->setFocus();
    popup->show();
}

void LineaDeTexto::setDiccionario(QString archivo)
{

    QFile file(":/root/Recursos/palabras/" + archivo + ".txt");

    //QFile file("F:/Ultima mejora/NightApp/" + archivo + ".txt");


    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"No abre archivo";
        return;
    }


    QTextStream in(&file);

    lista = new QStringList;

    while (!in.atEnd()) {


        lista->append(in.readLine());

    }

}

void LineaDeTexto::slot_sugerencias()
{
    QVector<QStringList> vectorCoincidencias;  // Almacenará las sugerencias

    QString cadena = this->text();

    // Este for se encarga de encontrar las coincidencias. Se sugieren hasta 5.
    for (int i=0, contador=0 ; i<lista->size() && contador<5 ; i++)  {

            QString string = lista->at(i);

            if (string.contains(cadena))  {
                    QStringList sugerencia;
                    sugerencia << string<< "Campo";
                    vectorCoincidencias.push_back(sugerencia);
                    contador++;
            }


    }

    if(!lista->contains(cadena)){

        connect(this,SIGNAL(returnPressed()),this,SLOT(slot_agregaPalabra()));

    }

    // Completa el popup con las sugerencias
    this->completarPopup(vectorCoincidencias);
}

void LineaDeTexto::slot_completerLineEdit()
{
    timer->stop();
    popup->hide();
    this->setFocus();

    QTreeWidgetItem *item = popup->currentItem();

    if (item)  {

           // Seteamos el QLineEdit con el texto del nombre del producto elegido.
        this->setText(item->text(0));
    }
}

void LineaDeTexto::slot_agregaPalabra()
{
    if(!lista->contains(this->text()))
    {
        lista->append(this->text());

        //QFile file("F:/Ultima mejora/NightApp/palabras.txt");

        QFile file(":/root/Recursos/palabras/palabras.txt");

        if (!file.open(QIODevice::ReadWrite | QIODevice::Append))
        {
            qDebug()<<"No abre archivo para añadir";
            return;
        }


        QTextStream in(&file);

        in<<"\n"<<this->text();

    }


}
