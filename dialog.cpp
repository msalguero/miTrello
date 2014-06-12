#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("Nueva Tarjeta"));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_2_clicked()
{
    this->reject();
}

void Dialog::on_pushButton_clicked()
{
    QString nombre, descripcion;
    int prioridad;

    nombre = ui->lineEdit->text();
    descripcion = ui->lineEdit2->text();
    if(ui->radioButton->isChecked())
        prioridad = 0;
    else if(ui->radioButton_2->isChecked())
        prioridad = 1;
    else
        prioridad = 2;

    if(nombre.isEmpty())
        QMessageBox::question( this, "Perdon",tr("Se necesita un titulo para la tarjeta\n"),
                               QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
    else
    {
        emit tarjetaCreada(new Tarjeta(nombre, prioridad, descripcion));
        this->accept();
    }

}
