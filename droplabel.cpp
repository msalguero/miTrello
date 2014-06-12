#include "droplabel.h"

DropLabel::DropLabel(int n)
{
    setAcceptDrops(true);
    posicion = n;
    pal = QWidget::palette().color(QWidget::backgroundRole());


}

//void DropLabel::dragEnterEvent(QDragEnterEvent *event)
//{
    //setGeometry(((Tarjeta*)event->source())->geometry());

   // QPalette Pal(palette());
    // set black background
   // Pal.setColor(QPalette::Background, Qt::blue);
   // setAutoFillBackground(true);
   // setPalette(Pal);

   // event->acceptProposedAction();
//}

void DropLabel::dragLeaveEvent(QDragLeaveEvent *event)
{
    //setGeometry(0,0,0,0);


    setPalette(pal);


}

//void DropLabel::dropEvent(QDropEvent *event)
//{
  //  setPalette(pal);
  //  emit dropFinalizado((Tarjeta*)event->source());
   // event->acceptProposedAction();
//}

void DropLabel::setActive()
{
    QPalette Pal(palette());

    Pal.setColor(QPalette::Background, Qt::blue);
    setAutoFillBackground(true);
    setPalette(Pal);
}

void DropLabel::setDeactive()
{
    setPalette(pal);
}
