#include "api_manager.h"
#include <QMessageBox>

const QString kBaseUrl = "http://api.icndb.com/";
const QString kanbanUrl = "http://kanbanize.com/index.php/api/kanbanize/get_projects_and_boards/format/json";
const QString kanbanUrlTasks = "http://kanbanize.com/index.php/api/kanbanize/get_all_tasks/boardid/2/format/json";
const QString kanbanUrlColumnas = "http://kanbanize.com/index.php/api/kanbanize/get_board_structure/boardid/2/format/json";
const QString kanbanUrlLogin = "http://kanbanize.com/index.php/api/kanbanize/login/email/msalguero_2%40hotmail.com/pass/estructuradedatos/format/json";
const QString test = "http://date.jsontest.com";

API_Manager::API_Manager()
{
    object = new QJsonObject();
    array = new QJsonArray();
    connect(&m_nam, SIGNAL(finished(QNetworkReply*)),
                         this, SLOT(parseNetworkResponse(QNetworkReply*)));
    connect(this, SIGNAL(apiReady(QByteArray)), this, SLOT(recieveAPI(QByteArray)));
}

Lista<Board*>* API_Manager::getFullStructure(Lista<Board *> **boards)
{
    (*boards)->Anula();

    QEventLoop pause;
    connect(&m_nam, SIGNAL(finished(QNetworkReply*)), &pause, SLOT(quit()));
    getBoards();
    pause.exec();

    QJsonArray ProjectArray = (*object)["projects"].toArray();
    if(ProjectArray.isEmpty())
        exit(0);
    QJsonObject project = ProjectArray[0].toObject();
    QJsonArray boardArray = project["boards"].toArray();
    for (int i = 0; i < boardArray.size(); ++i)
    {
            QJsonObject boardObject = boardArray[i].toObject();
            Board* b = new Board(boardObject["name"].toString());

            QEventLoop pause;
            connect(&m_nam, SIGNAL(finished(QNetworkReply*)), &pause, SLOT(quit()));
            getColumns(boardObject["id"].toString());
            pause.exec();
            QJsonObject *j = object;

            QEventLoop pause2;
            connect(&m_nam, SIGNAL(finished(QNetworkReply*)), &pause2, SLOT(quit()));
            getTasks(boardObject["id"].toString());
            pause2.exec();
            QJsonArray *a = array;

            b->readKanban(*j, *a);
            (*boards)->Agregar(b);
    }
    return *boards;
}

void API_Manager::getRequest( const QString &urlString )
{
    QUrl url ( urlString );
    QNetworkRequest req ( url );
    req.setHeader( QNetworkRequest::ContentTypeHeader, "apikey" );
    req.setRawHeader("apikey", apikey.toUtf8());

    QByteArray postData;
    m_nam.post(req, postData);
}

void API_Manager::parseNetworkResponse( QNetworkReply *finished )
{

    if ( finished->error() != QNetworkReply::NoError )
    {
        QMessageBox::about(NULL, "Lo sentimos", "Contraseña o usuario no valido");
        // A communication error has occurred
        emit networkError( finished->error() );
        return;
    }

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QByteArray data = finished->readAll();
    emit apiReady( data );
}

void API_Manager::login(QString email, QString pass)
{
    //email = "msalguero_2%40hotmail.com";
    //pass  = "estructuradedatos";
    email.replace("@", "%40");
    qDebug()<<email<<" "<<pass;
    const QString kanbanUrlLogin = "http://kanbanize.com/index.php/api/kanbanize/login/email/"+email+"/pass/"+pass+"/format/json";
    qDebug()<<kanbanUrlLogin;
    QEventLoop pause;
    connect(&m_nam, SIGNAL(finished(QNetworkReply*)), &pause, SLOT(quit()));
    getRequest(kanbanUrlLogin);
    pause.exec();


}

void API_Manager::recieveAPI(const QByteArray &apiAsJSON)
{
    QJsonDocument json( QJsonDocument::fromJson(apiAsJSON));

    QFile saveFile(QStringLiteral("save2.json"));
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return ;
    }
    saveFile.write(json.toJson());

    if(json.isArray())
    {
        QJsonArray *a = new QJsonArray(json.array());
        array = a;
    }else
    {
        QJsonObject *j = new QJsonObject(json.object());
        if(j->contains("apikey"))
            apikey = (*j)["apikey"].toString();
        object = (j);
    }
}

void API_Manager::getBoards()
{
    const QString kanbanUrl = "http://kanbanize.com/index.php/api/kanbanize/get_projects_and_boards/format/json";
    getRequest(kanbanUrl);
}

void API_Manager::getColumns(QString id)
{
    const QString kanbanUrlColumnas = "http://kanbanize.com/index.php/api/kanbanize/get_board_structure/boardid/"+id+"/format/json";
    getRequest(kanbanUrlColumnas);
}

void API_Manager::getTasks(QString columnId)
{
    const QString kanbanUrlTasks = "http://kanbanize.com/index.php/api/kanbanize/get_all_tasks/boardid/"+columnId+"/format/json";
    getRequest(kanbanUrlTasks);
}
