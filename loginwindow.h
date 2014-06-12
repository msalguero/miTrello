#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private:
    Ui::LoginWindow *ui;

signals:
    void login(QString email, QString pass);
    void offline();
private slots:
    void on_login_clicked();
    void on_offline_clicked();
};

#endif // LOGINWINDOW_H
