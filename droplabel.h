#ifndef DROPLABEL_H
#define DROPLABEL_H

#include <QLabel>
#include <QPicture>
#include <QPainter>
#include <QString>
#include <QMouseEvent>
#include <QEvent>
#include <QDrag>
#include <QMimeData>
#include "tarjeta.h"

class Tarjeta;

class DropLabel : public QLabel
{
    Q_OBJECT
public:
    int posicion;
    QPalette pal;
    DropLabel(int n);

    //void dragEnterEvent(QDragEnterEvent *event);
    //void dropEvent(QDropEvent *event);
    void setActive();
    void setDeactive();
    void dragLeaveEvent(QDragLeaveEvent *event);
signals:
    void dropFinalizado(Tarjeta* tarjeta);
};

#endif // DROPLABEL_H
