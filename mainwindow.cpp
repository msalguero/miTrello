#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->editNombreLista->hide();
    ui->guardarListabtn->hide();
    layout = new QHBoxLayout;
    layout->setAlignment(Qt::AlignTop);

    QScrollArea *scroll = new QScrollArea;
    ui->frame->setParent(scroll);
    ui->frame->setLayout(layout);
    scroll->setWidget(ui->frame);
    scroll->setWidgetResizable(true);

    QLayout* outerLayout = new QVBoxLayout();
    outerLayout->addWidget(scroll);
    ui->frame2->setLayout(outerLayout);
    setWindowTitle(QObject::tr("MiTrello"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mostrar(Board* b)
{
    currentBoard  = b;

    ui->lblNombre->setText(b->text());

    b->lista->iteradorReset();

    while(!b->lista->iteradorEnd())
    {
        layout->addWidget(b->lista->valorIterador());
        b->lista->Siguiente();
    }
    show();
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Seguro",
                                                                tr("Estas seguro?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        while(!layout->isEmpty())
        {
            delete layout->itemAt(0)->widget();
        }
        event->accept();
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->editNombreLista->show();
    ui->guardarListabtn->show();
}

void MainWindow::on_guardarListabtn_clicked()
{
    QString n = ui->editNombreLista->text();
    if(!n.isEmpty())
        addList(n);
    ui->editNombreLista->clear();
    ui->guardarListabtn->hide();
    ui->editNombreLista->hide();
}

void MainWindow::addList(QString nombre)
{
    ListaTarjeta* l = new ListaTarjeta(nombre);
    l->updateList();
    currentBoard->lista->Agregar(l);
    layout->addWidget(l);
}

void MainWindow::on_pushButton_2_clicked()
{
    emit guardarClick();
}
