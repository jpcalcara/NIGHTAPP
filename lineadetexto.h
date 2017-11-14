#ifndef LINEADETEXTO_H
#define LINEADETEXTO_H

#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <QTreeWidget>
#include <QStringList>
#include <QTimer>
#include <QVector>
#include <QHeaderView>
#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QFile>
#include <QTextStream>

class LineaDeTexto : public QLineEdit
{   Q_OBJECT

public:
    LineaDeTexto(QWidget * parent = 0);
    LineaDeTexto(QString texto, QWidget *parent=0);

    LineaDeTexto(const LineaDeTexto & linea);
    LineaDeTexto& operator = (const LineaDeTexto & linea);

    LineaDeTexto operator +(const LineaDeTexto linea);

    void setDiccionario(QString archivo);

private:
    QTreeWidget *popup;
    QTimer *timer;
    QStringList *lista;
    void CrearPopup();
    bool eventFilter(QObject *obj, QEvent *e);
    void completarPopup(QVector<QStringList> vector);



private slots:
    void slot_sugerencias();
    void slot_completerLineEdit();
    void slot_agregaPalabra();
};


#endif // LINEADETEXTO_H
