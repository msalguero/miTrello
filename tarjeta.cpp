#include "tarjeta.h"


Tarjeta::Tarjeta(QString texto, int prioridad, QString descripcion)
{
    this->prioridad = prioridad;
    this->descripcion = descripcion;
    this->texto = texto;
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
    //setPixmap(*pix);

    this->setText(texto);
    this->setStyleSheet("background-color: #eef8f9; border-radius: 3px; font: 87 10pt Arial;");

    //offset = 0;
    setMaximumHeight(35);
    setMinimumHeight(35);



    setAttribute(Qt::WA_DeleteOnClose);
}

void Tarjeta::mousePressEvent(QMouseEvent *ev)
{
     QDrag *drag = new QDrag(this);
     QMimeData *mimeData = new QMimeData;

     mimeData->setText(texto);
     drag->setMimeData(mimeData);
     QPixmap pixmap = QPixmap::grabWidget(this);
     drag->setPixmap(pixmap);


   // Qt::DropAction dropAction = ;

    if(drag->exec(Qt::MoveAction) == Qt::MoveAction)
          emit iniciarDrag(this);
}

void Tarjeta::write(QJsonObject &json)
{
    json["texto"] = texto;
}

void Tarjeta::read(const QJsonObject &json)
{
    texto = json["texto"].toString();

}
