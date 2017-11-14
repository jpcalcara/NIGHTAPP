#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <QMessageBox>

#include "admindb.h"
#include "usuario.h"

//para la DB online
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonArray>
#include <QJsonDocument>
#include <QResizeEvent>


namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    ~Login();
    Usuario *usuario;
    Usuario getUsuario();
    QNetworkAccessManager *manager;
    QJsonArray *jarray;
    QJsonDocument *jdoc;
    QJsonDocument replyJsonDocum;


signals:
    void signal_ShowVentana(bool);
    void signal_ShowFormulario(bool);
    void usuarioCorrecto(Usuario *us);
    void select(int i);

protected:
    void resizeEvent(QResizeEvent *e);


private:

    Ui::Login *ui;
    QImage im_fondo;

private slots:

     void slot_procesarRespuesta(QNetworkReply *reply);


    //Metodos para enviar datos y recibir de la base de datos
     void slot_validarUsuario();

    /**
     * @brief slot_validar valida los datos ingresados por el user contra la base de datos,
     */
    //void slot_validar();

    /**
     * @brief slot_Formulario inicializa un objeto de tipo formulario para la carga de datos
     */
    void slot_Formulario();

    /**
     * @brief slot_verPass muestra el string correspondiente al password ingresado por el user
     */
    void slot_verPass(bool a);

    /**
     * @brief slot_noverPass encripta el string correspondiente al password ingresado por el user
     */
    void slot_noverPass(bool a);

    void slot_infoAutores();
};

#endif // LOGIN_H
