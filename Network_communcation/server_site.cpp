#include "server_site.h"
#include "qtcpserver.h"

Server_site::Server_site(int port,QObject *parent)
    : QObject(parent)

{
    _server = new QTcpServer(this);
    connect(_server, &QTcpServer::newConnection, this, &Server_site::on_client_connecting);
    _isStarted = _server->listen(QHostAddress::Any, port);
    if(!_isStarted){
        qDebug() << "Server could not start";
    } else{
        qDebug() << "Server started...";
    }
}


void Server_site::on_client_connecting()
{
    qDebug() << "a client connected to server";
    auto socket = _server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &Server_site::clientDataReady);
    connect(socket, &QTcpSocket::disconnected, this, &Server_site::clientDisconnected);
    _socketsList.append(socket);
    char bit = 0xAA;
    emit newClientConnected();
}

void Server_site::clientDisconnected()
{
    emit clientDisconnect();
}

bool Server_site::isStarted() const
{
    return _isStarted;
}


void Server_site::clientDataReady()
{
    auto socket = qobject_cast<QTcpSocket *>(sender());
    auto data = QString(socket->readAll());
    emit dataReceived(data);
    foreach (auto s , _socketsList) {
        if(s != socket)
        {
            s->write(data.toUtf8());
        }

    }
}

void Server_site::sendToAll(char startBit,char lenData,QString message,QByteArray crcData,char stopBit)
{
    foreach(auto socket , _socketsList)
    {
        socket->write(&startBit,0x01);
        socket->write(&lenData,0x01);
        socket->write(message.toUtf8());
        socket->write(crcData);
        socket->write(&stopBit);
    }
}

