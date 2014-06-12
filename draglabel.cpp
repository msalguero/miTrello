#include "draglabel.h"

dragLabel::dragLabel(QString texto, int prioridad)
{
    QPixmap *pix;

    if(prioridad == 1)
        pix = new QPixmap("C:/Users/manuel/Documents/QT/miTrello/tarjeta2.png");
    else if(prioridad == 2)
        pix = new QPixmap("C:/Users/manuel/Documents/QT/miTrello/tarjeta1.png");
    else
        pix = new QPixmap("C:/Users/manuel/Documents/QT/miTrello/tarjeta3.png");

    QPainter* painter = new QPainter(pix);
    painter->setPen(Qt::black);
    painter->setFont(QFont("Arial", 12));
    painter->drawText(pix->rect(), Qt::AlignCenter, texto);
    setPixmap(*pix);

}
