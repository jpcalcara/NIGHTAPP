#ifndef START_H
#define START_H

#include <QWidget>
#include <QImage>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QProgressBar>
#include <QTime>
#include <QTimer>
#include <QResizeEvent>

namespace Ui {
class Start;
}

class Start : public QWidget
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    ~Start();

private:
    Ui::Start *ui;
    QImage im_fondoStart;
    QTimer * timer;
    int counter;

signals:
    void signal_ready(bool);

protected:
    void resizeEvent(QResizeEvent *e);


private slots:

    /**
     * @brief slot_updateProgressBar  actualiza la barra de progreso al cargar la app
     */
    void slot_updateProgressBar();
};

#endif // START_H
