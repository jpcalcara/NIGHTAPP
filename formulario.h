#ifndef FORMULARIO_H
#define FORMULARIO_H

#include <QWidget>
#include <QImage>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QResizeEvent>

#include "admindb.h"


namespace Ui {
class Formulario;
}

class Formulario : public QWidget
{
    Q_OBJECT

public:
    explicit Formulario(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    ~Formulario();

signals:
    void signal_ShowLogin(bool);

private:
    Ui::Formulario *ui;
    AdminDB *admin;
    QImage im_fondoform;
    QNetworkAccessManager *manager;

protected:
    void resizeEvent(QResizeEvent *e);

private slots:

    /**
     * @brief slot_verPass muestra el string correspondiente al password ingresado por el user
     */
    void slot_verPass(bool a);

    /**
     * @brief slot_noverPass encripta el string correspondiente al password ingresado por el user
     */
    void slot_noverPass(bool a);

    void slot_registerOnline();

    void slot_Reply(QNetworkReply *reply);
};

#endif // FORMULARIO_H
