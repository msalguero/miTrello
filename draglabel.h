#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>
#include <QPicture>
#include <QPainter>
#include <QString>

class dragLabel: public QLabel
{
public:
    dragLabel(QString texto, int prioridad = 0);
};

#endif // DRAGLABEL_H
