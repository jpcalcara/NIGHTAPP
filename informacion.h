#ifndef INFORMACION_H
#define INFORMACION_H

#include <QWidget>

namespace Ui {
class Informacion;
}

class Informacion : public QWidget
{
    Q_OBJECT

public:
    explicit Informacion(QWidget *parent = 0);
    ~Informacion();

    void setTexto( QString texto );

protected:
    void mousePressEvent(QMouseEvent * e);

private:
    Ui::Informacion *ui;

signals:
    void signal_clic();
};

#endif // INFORMACION_H
