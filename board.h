#ifndef BOARD_H
#define BOARD_H

#include <QPushButton>
#include <QJsonArray>
#include <QJsonObject>
#include "Lista.h"
#include "listatarjeta.h"

class Board : public QPushButton
{
    Q_OBJECT
public:
    Lista<ListaTarjeta*> *lista;
    QString texto;

    Board(QString texto);

    void write(QJsonObject &json);
    void read(const QJsonObject &json);
    void readKanban(const QJsonObject &json, const QJsonArray &json2);
signals:
    void click(Board* board);
private slots:
    void mandarBoard();
};

#endif // BOARD_H
