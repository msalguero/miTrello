#ifndef TARJETA_H
#define TARJETA_H

#include <QLabel>
#include <QPicture>
#include <QPainter>
#include <QString>
#include <QMouseEvent>
#include <QEvent>
#include <QDrag>
#include <QMimeData>
#include <QVBoxLayout>
#include <QJsonArray>
#include <QJsonObject>

class Tarjeta : public QLabel
{
    Q_OBJECT
public:
    int static const PRIORIDAD_ALTA = 2;
    int static const PRIORIDAD_MEDIA = 1;
    int static const PRIORIDAD_BAJA = 0;

    Tarjeta(QString texto, int prioridad = 0, QString descripcion = NULL);
    int prioridad;
    QString descripcion;
    QString texto;
    QPoint offset;

    void mousePressEvent(QMouseEvent* ev);
    void write(QJsonObject &json);
    void read(const QJsonObject &json);
signals:
    void iniciarDrag(Tarjeta* tarjeta);

};

#endif // TARJETA_H
