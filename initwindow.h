#ifndef INITWINDOW_H
#define INITWINDOW_H

#include <QDialog>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QSignalMapper>
#include <QFile>
#include <QJsonDocument>
#include "board.h"
#include "Lista.h"
#include "api_manager.h"

namespace Ui {
class initWindow;
}

class initWindow : public QDialog
{
    Q_OBJECT

public:
    Lista<Board*> *boards;
    Board* boardPresionada;
    explicit initWindow(QWidget *parent = 0);
    ~initWindow();

    void update();
    void addBoard(QString nombre);
    void guardar();
    void cargar();
    void cargarKanban(QString email, QString pass);
    void write(QJsonObject &json);
    void read(const QJsonObject &json);
    void readKanban(const QJsonObject &json);
signals:
    void clickEnBoard(Board* b);

public slots:
    void autenticarLogin(QString email, QString pass);
    void offline();
private slots:
    void enviarSignal(Board* b);

    void on_pushButton_clicked();

    void on_addBoardbtn_clicked();

    void guardarCambios();

private:
    QHBoxLayout *layout;
    QSignalMapper *signalMapper;
    Ui::initWindow *ui;
};

#endif // INITWINDOW_H
