#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QImage>
#include <QModelIndex>
#include <QStringList>
#include <QTimer>
#include <QVector>
#include <QHeaderView>
#include <QObject>
#include <QEvent>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include <QTreeWidget>

#include <QMouseEvent>
#include <QTextEdit>


namespace Ui {
class Ventana;
}

class Ventana : public QWidget
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = 0);
    ~Ventana();
    void paintEvent(QPaintEvent *);

    void SetListadoLugares(QStringList lugares);
    void SetInfoLugar(QStringList info);
    void SetDistancia(QString distancia);
    void SetMapa(QImage im);


signals:
    void signal_ShowLogin(bool);
    void signal_IndexCombo(int);
    void signal_IniciaBusquedaPalabra(QString);
    void signal_Estado(int,QString);

private:
    Ui::Ventana *ui;
    QImage im_fondoven;
    int estado;
    QImage imMap;
    int zoom = 10;
    QTimer *timer;
    QTimer *timer2;
    QTreeWidget *popup;

    QTextEdit *teInfo;
    int tam;


    void dimensionarWidget();
signals:
    void signal_IniciaBusqueda();
    void signal_IniciaInfo(QModelIndex );


private slots:
    void slot_comboBox(int i);
    void slot_ActualizaPos();
    void slot_ActivaListado(QModelIndex index);
    void slot_time();
    void hola2();
    void slot_time2();

protected:
    void mouseDoubleClickEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);


};

#endif // VENTANA_H
