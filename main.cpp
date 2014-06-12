#include "mainwindow.h"
#include "initwindow.h"
#include <QApplication>
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow l;

    l.show();

    initWindow i;
    QObject::connect(&l, SIGNAL(login(QString,QString)), &i, SLOT(autenticarLogin(QString,QString)));
    QObject::connect(&l, SIGNAL(offline()), &i, SLOT(offline()));
    //i.show();

    MainWindow w;
    QObject::connect(&i, SIGNAL(clickEnBoard(Board*)), &w, SLOT(mostrar(Board*)));
    QObject::connect(&w, SIGNAL(guardarClick()), &i, SLOT(guardarCambios()));

    //w.show();

    return a.exec();
}
