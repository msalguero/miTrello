#include "listatarjeta.h"
#include <QDebug>
ListaTarjeta::ListaTarjeta(QString name, QWidget* parent): QFrame(parent)
{
    size = 1;
    posicion = 1;
    this->dragEntro = false;

    setSize(50);

    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    layout = new QVBoxLayout();
    tarjetas = new Lista<Tarjeta*>();
    this->name = name;

    btnCrear = new QPushButton("Agregar");
    btnCrear->setStyleSheet("border: none; color: rgb(137, 137, 137); text-align:left;");
    dialog = new Dialog;
    layout->setSpacing(10);
    layout->setSizeConstraint(QLayout::SetNoConstraint);

    connect(btnCrear, SIGNAL(clicked()), dialog, SLOT(exec()));
    connect(dialog, SIGNAL(tarjetaCreada(Tarjeta*)), this, SLOT(enTarjetaCreada(Tarjeta*)));

    this->setAcceptDrops(true);
    this->setStyleSheet("background-color: #d0d0d0; border-radius: 3px;");

}

void ListaTarjeta::updateList()
{
    QLabel * label = new QLabel(name);
    label->setStyleSheet("font: 87 10pt Arial Black;");
    label->setMaximumHeight(35);
    layout->addWidget(label);
    tarjetas->iteradorReset();

    while(!tarjetas->iteradorEnd())
    {
        layout->addWidget(tarjetas->valorIterador());

        tarjetas->valorIterador()->setParent(this);
        connect(tarjetas->valorIterador(), SIGNAL(iniciarDrag(Tarjeta*)), this, SLOT(enTarjetaArrastrada(Tarjeta*)));
        tarjetas->Siguiente();
        size++;

        setSize(this->height()+40);
    }
    layout->addWidget(btnCrear);
    setLayout(layout);
}

void ListaTarjeta::enTarjetaCreada(Tarjeta* tarjeta)
{
    tarjetas->Agregar(tarjeta);
    setSize(this->height()+40);
    size++;
    layout->insertWidget( layout->count()-1, tarjeta);
    connect(tarjeta, SIGNAL(iniciarDrag(Tarjeta*)), this, SLOT(enTarjetaArrastrada(Tarjeta*)));
}

void ListaTarjeta::enTarjetaArrastrada(Tarjeta* tarjeta)
{
    disconnect(tarjeta, SIGNAL(iniciarDrag(Tarjeta*)), this, SLOT(enTarjetaArrastrada(Tarjeta*)));
    tarjetas->Localiza_Suprime(tarjeta);
    dragEntro = false;
}

void ListaTarjeta::dragEnterEvent(QDragEnterEvent *event)
{
    if(layout->indexOf((Tarjeta*)event->source()) != -1 && !dragEntro)
    {
        dragEntro = true;
        event->acceptProposedAction();
        return;
    }

    setSize(this->height()+40);
    event->acceptProposedAction();
}

void ListaTarjeta::dragLeaveEvent(QDragLeaveEvent *event)
{
    setSize(this->height()-40);

}

void ListaTarjeta::dropEvent(QDropEvent *event)
{
    Tarjeta* t = (Tarjeta*)event->source();
    dragEntro = false;

    int pos = posicion;

    insertarTarjeta(pos, t);
    event->acceptProposedAction();
}

void ListaTarjeta::insertarTarjeta(int pos, Tarjeta *tarjeta)
{

    Tarjeta* t2 = new Tarjeta(tarjeta->texto, tarjeta->prioridad, tarjeta->descripcion);

    tarjetas->Insertar(t2, pos-1);
    layout->insertWidget( pos, tarjeta);

    connect(tarjeta, SIGNAL(iniciarDrag(Tarjeta*)), this, SLOT(enTarjetaArrastrada(Tarjeta*)));
}

void ListaTarjeta::dragMoveEvent(QDragMoveEvent *event)
{

    tarjetas->iteradorReset();
    int p = 1;

    for (int i = 0; i < layout->count();i++)
    {
        QWidgetItem *myItem = dynamic_cast <QWidgetItem*>(layout->itemAt(i));

        if (event->answerRect().intersects(myItem->widget()->geometry()))
            break;

        p++;
    }

    qDebug() <<p;
    posicion = p;
    event->acceptProposedAction();
}

void ListaTarjeta::write(QJsonObject &json)
{
    QJsonArray tarjetaArray;

    tarjetas->iteradorReset();
    json["name"] = name;

    while(!tarjetas->iteradorEnd())
    {
        QJsonObject tarjetaObject;
        tarjetas->valorIterador()->write(tarjetaObject);
        tarjetaArray.append(tarjetaObject);
        tarjetas->Siguiente();
    }

     json["listaTarjetas"] = tarjetaArray;
}

void ListaTarjeta::read(const QJsonObject &json)
{
    tarjetas->Anula();

    name = json["name"].toString();

    QJsonArray tarjetaArray = json["listaTarjetas"].toArray();
    for (int i = 0; i < tarjetaArray.size(); ++i) {
        QJsonObject tarjetaObject = tarjetaArray[i].toObject();
        Tarjeta* t = new Tarjeta(tarjetaObject["texto"].toString());
        t->read(tarjetaObject);
        tarjetas->Agregar(t);
    }

    updateList();
}

void ListaTarjeta::readKanban(const QJsonArray &json, QString n)
{
    tarjetas->Anula();
    //name = json["columnname"].toString();
    name = n;
    for (int i = 0; i < json.size(); ++i) {
        QJsonObject tarjetaObject = json[i].toObject();
        if(n != tarjetaObject["columnname"].toString())
            continue;
        Tarjeta* t = new Tarjeta(tarjetaObject["title"].toString());
        //t->read(tarjetaObject);
        tarjetas->Agregar(t);
    }


    updateList();
}

void ListaTarjeta::setSize(int h)
{
    setMaximumHeight(h);
    setMinimumHeight(h);
}
