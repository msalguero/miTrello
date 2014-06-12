#ifndef LISTATARJETA_H
#define LISTATARJETA_H

#include <QFrame>
#include "tarjeta.h"
#include "Lista.h"
#include "dialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QJsonArray>
#include <QJsonObject>


class Dialog;

class ListaTarjeta : public QFrame
{
    Q_OBJECT
    Dialog* dialog;
public:
    Lista<Tarjeta*> *tarjetas;
    QString name;
    QPushButton* btnCrear;
    int posicion;
    int size;
    bool dragEntro;

    ListaTarjeta(QString name, QWidget *parent = 0);
    void updateList();
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void insertarTarjeta(int pos, Tarjeta* tarjeta);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void write(QJsonObject &json);
    void read(const QJsonObject &json);
    void readKanban(const QJsonArray &json, QString n);

signals:
    void crearTarjeta();
private slots:
    void enTarjetaCreada(Tarjeta* tarjeta);
    void enTarjetaArrastrada(Tarjeta* tarjeta);

private:
     QVBoxLayout* layout;

     void setSize(int h);
};

#endif // LISTATARJETA_H
