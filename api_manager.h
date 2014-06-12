#ifndef API_MANAGER_H
#define API_MANAGER_H

#include <QObject>
#include <QDebug>
#include <QEventLoop>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include "board.h"
#include "listatarjeta.h"
#include "tarjeta.h"
#include "Lista.h"

class QDebug;

class API_Manager : public QObject
{
    Q_OBJECT
public:
    API_Manager();
    QJsonObject* object;
    QJsonArray* array;
    QString apikey;

    Lista<Board *> *getFullStructure(Lista<Board*> **boards);
    void login(QString email, QString pass);
    void getBoards();
    void getColumns(QString id);
    void getTasks(QString columnId);

private:
    void getRequest( const QString &url );

signals:
    void apiReady( const QByteArray &apiAsJSON );
    void networkError( QNetworkReply::NetworkError err );

public slots:
    void parseNetworkResponse( QNetworkReply *finished );
    void recieveAPI( const QByteArray &apiAsJSON );


private:
    QNetworkAccessManager m_nam;
};

#endif // API_MANAGER_H
