#include "initwindow.h"
#include "ui_initwindow.h"

initWindow::initWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initWindow)
{

    //this->setStyleSheet("background-color: teal;");

    ui->setupUi(this);
    setWindowTitle(QObject::tr("MiTrello"));
    ui->addBoardbtn->hide();
    ui->editBoardName->hide();

    boards = new Lista<Board*>();
    layout = new QHBoxLayout;
    boardPresionada = NULL;

   // QScrollArea *scroll = new QScrollArea;
    //ui->frame->setParent(scroll);
    //ui->frame->setLayout(layout);
    //scroll->setWidget(ui->frame);
    //scroll->setWidgetResizable(true);

    //QLayout* outerLayout = new QVBoxLayout();
    //outerLayout->addWidget(scroll);
    ui->frame2->setLayout(layout);

}

initWindow::~initWindow()
{
    delete ui;
}

void initWindow::enviarSignal(Board *b)
{
    emit clickEnBoard(b);
}

void initWindow::update()
{
    boards->iteradorReset();

    while(!boards->iteradorEnd())
    {
        layout->addWidget(boards->valorIterador());
        connect(boards->valorIterador(), SIGNAL(click(Board*)), this, SLOT(enviarSignal(Board*)));
        boards->Siguiente();
    }
}

void initWindow::on_pushButton_clicked()
{
    ui->addBoardbtn->show();
    ui->editBoardName->show();
}

void initWindow::on_addBoardbtn_clicked()
{
    QString n = ui->editBoardName->text();
    if(!n.isEmpty())
        addBoard(n);
    ui->editBoardName->clear();
    ui->addBoardbtn->hide();
    ui->editBoardName->hide();
}

void initWindow::addBoard(QString nombre)
{
    Board* b = new Board(nombre);
    boards->Agregar(b);
    layout->addWidget(b);
    connect(b, SIGNAL(click(Board*)), this, SLOT(enviarSignal(Board*)));
}

void initWindow::guardar()
{
    QFile saveFile(QStringLiteral("save.json"));


       if (!saveFile.open(QIODevice::WriteOnly)) {
           qWarning("Couldn't open save file.");
           return ;
       }

       QJsonObject estructura;
       write(estructura);
       if(estructura.empty())
           exit(0);
       QJsonDocument saveDoc(estructura);
       saveFile.write(saveDoc.toJson());

}

void initWindow::write(QJsonObject &json)
{


       QJsonArray boardArray;

       boards->iteradorReset();

       while(!boards->iteradorEnd())
       {
           QJsonObject boardObject;
           boards->valorIterador()->write(boardObject);
           boardArray.append(boardObject);
           boards->Siguiente();
       }

        json["trello"] = boardArray;
}

void initWindow::cargar()
{
    QFile loadFile(QStringLiteral("save.json"));

        if (!loadFile.open(QIODevice::ReadOnly)) {
            qWarning("Couldn't open save file.");
            return ;
        }

        QByteArray datos = loadFile.readAll();

        QJsonDocument loadDoc(QJsonDocument::fromJson(datos));

        read(loadDoc.object());
}

void initWindow::readKanban(const QJsonObject &json)
{
    boards->Anula();
     QJsonArray ProjectArray = json["projects"].toArray();
     QJsonObject project = ProjectArray[0].toObject();
     QJsonArray boardArray = project["boards"].toArray();
     for (int i = 0; i < boardArray.size(); ++i)
     {
             QJsonObject boardObject = boardArray[i].toObject();
             Board* b = new Board(boardObject["name"].toString());
             b->read(boardObject);
             boards->Agregar(b);
     }
}

void initWindow::read(const QJsonObject &json)
{
    boards->Anula();
    QJsonArray boardArray = json["trello"].toArray();
    for (int i = 0; i < boardArray.size(); ++i)
    {
            QJsonObject boardObject = boardArray[i].toObject();
            Board* b = new Board(boardObject["texto"].toString());
            b->read(boardObject);
            boards->Agregar(b);
    }
}

void initWindow::guardarCambios()
{
    guardar();
}

void initWindow::cargarKanban(QString email, QString pass)
{
    API_Manager api;
    api.login(email, pass);
    boards = api.getFullStructure(&(boards));
}

void initWindow::autenticarLogin(QString email, QString pass)
{
    cargarKanban(email, pass);

    update();
    this->show();
}

void initWindow::offline()
{
    cargar();

    update();
    this->show();
}
