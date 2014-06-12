#include "tarjetadrag.h"

TarjetaDrag::TarjetaDrag(Tarjeta* tarjeta): Tarjeta(tarjeta->texto, tarjeta->prioridad, tarjeta->descripcion)
{
    //QPoint p = this->mapFromGlobal(QCursor::pos());
    //offset = p;

}

void TarjetaDrag::mouseMoveEvent(QMouseEvent *ev)
{
   this->move(mapToParent(ev->pos() - offset));
}

