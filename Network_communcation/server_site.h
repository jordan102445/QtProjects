#ifndef SERVER_SITE_H
#define SERVER_SITE_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server_site :public QObject
{
    Q_OBJECT

public:
    explicit Server_site(int port,QObject *parent = nullptr);
    bool isStarted() const;
    void sendToAll(char startBit,char lenData,QString message,QByteArray crcData,char stopBit);
signals:
    void newClientConnected();
    void clientDisconnect();
    void dataReceived(QString message);

private slots:
    void on_client_connecting();
    void clientDisconnected();
    void clientDataReady();


private:
    QTcpServer *_server;
    QList<QTcpSocket *> _socketsList;
    bool _isStarted;

};

#endif // SERVER_SITE_H
