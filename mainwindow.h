#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "listatarjeta.h"
#include "board.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QCloseEvent>
#include <QScrollArea>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);
    void addList(QString nombre);
signals:
    void guardarClick();
public slots:
    void mostrar(Board* b);

private slots:
    void on_pushButton_clicked();

    void on_guardarListabtn_clicked();

    void on_pushButton_2_clicked();

private:
    Board* currentBoard;
    QHBoxLayout *layout;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
