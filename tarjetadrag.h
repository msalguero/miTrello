#ifndef TARJETADRAG_H
#define TARJETADRAG_H

#include "tarjeta.h"

class TarjetaDrag : public Tarjeta
{
    Q_OBJECT
public:
    TarjetaDrag(Tarjeta* tarjeta);

    void mouseMoveEvent(QMouseEvent* ev);
};

#endif // TARJETADRAG_H
