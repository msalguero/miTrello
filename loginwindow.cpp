#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    QPixmap *pix = new QPixmap("C:/Users/manuel/Documents/QT/miTrello/top.png");

    ui->label->setPixmap(*pix);
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_login_clicked()
{
    QString email = ui->lineEditUsername->text();
    QString pass = ui->lineEditPassword->text();

    if(email.isEmpty() || pass.isEmpty())
    {
         QMessageBox::about(this, "Lo sentimos", "Debe llenar los campos requeridos");
         return ;
    }

    emit login(email, pass);
    ui->lineEditPassword->clear();
    ui->lineEditUsername->clear();
    this->hide();
}

void LoginWindow::on_offline_clicked()
{
    emit offline();
    this->hide();
}
