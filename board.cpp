#include "board.h"

Board::Board(QString texto) : QPushButton("")
{
    lista = new Lista<ListaTarjeta*>();
    this->texto = texto;

    QPixmap pix("C:/Users/manuel/Documents/QT/miTrello/boton.png");

    QPainter* painter = new QPainter(&pix);
    painter->setPen(Qt::white);
    painter->setFont(QFont("Arial", 12));
    painter->drawText(pix.rect(), Qt::AlignCenter, texto);
    QIcon icono(pix);
   // this->setIcon(icono);
    //this->setIconSize(pix.rect().size());
    this->setText(texto);

    setMaximumWidth(pix.rect().width()-10);
    setMaximumHeight(pix.rect().height()-10);

    lista->Agregar(new ListaTarjeta("To do"));
    lista->Agregar(new ListaTarjeta("Doing"));
    lista->Agregar(new ListaTarjeta("Done"));
    lista->Recupera(0)->updateList();
    lista->Recupera(1)->updateList();
    lista->Recupera(2)->updateList();
    connect(this, SIGNAL(clicked()), this, SLOT(mandarBoard()));

    this->setStyleSheet("background-color: #378dbd; border-radius: 3px; font: 87 10pt Arial Black; color: white;");
}

void Board::mandarBoard()
{
    emit click(this);
}

void Board::write(QJsonObject &json)
{
    QJsonArray listaTArray;

    lista->iteradorReset();
    json["texto"] = texto;

    while(!lista->iteradorEnd())
    {
        QJsonObject listaObject;
        lista->valorIterador()->write(listaObject);
        listaTArray.append(listaObject);
        lista->Siguiente();
    }

     json["board"] = listaTArray;
}

void Board::read(const QJsonObject &json)
{
    lista->Anula();

    texto = json["texto"].toString();
    this->setText(texto);

    QJsonArray listaArray = json["board"].toArray();
    for (int i = 0; i < listaArray.size(); ++i) {
        QJsonObject listaObject = listaArray[i].toObject();
        ListaTarjeta* l = new ListaTarjeta(listaObject["name"].toString());
        l->read(listaObject);
        lista->Agregar(l);
    }
}

void Board::readKanban(const QJsonObject &json, const QJsonArray &json2)
{
    lista->Anula();

    QJsonArray listaArray = json["columns"].toArray();
    for (int i = 0; i < listaArray.size(); ++i) {
        QJsonObject listaObject = listaArray[i].toObject();
        if(listaObject["position"].toString().isEmpty())
            continue;
        ListaTarjeta* l = new ListaTarjeta(listaObject["lcname"].toString());
        l->readKanban(json2, listaObject["lcname"].toString());
        lista->Agregar(l);
    }
}
