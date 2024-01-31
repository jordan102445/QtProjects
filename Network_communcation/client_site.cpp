#include "client_site.h"

Device_connect::Device_connect(QObject *parent)
    : QObject(parent)
{

    connect(&_socket,&QTcpSocket::connected,this,&Device_connect::connected);
    connect(&_socket,&QTcpSocket::disconnected,this,&Device_connect::disconnected);
    connect(&_socket,&QTcpSocket::stateChanged,this,&Device_connect::stateChanged);
    connect(&_socket,&QTcpSocket::errorOccurred,this,&Device_connect::errorOccurred);
    connect(&_socket,&QTcpSocket::readyRead,this,&Device_connect::socket_readyRead); // SIGNAL(readyRead) SLOT(socket_readyRead) ->
     // -> A signal is emitted when a particular event occurs, and a slot is a function that can handle the signal

}

void Device_connect::connectToDevice(QString ip, int port)
{
    _ip = ip;
    _port = port;
    _socket.connectToHost(_ip,_port);

}

void Device_connect::disconnect()
{
    _socket.close();
}

void Device_connect::socket_State(QAbstractSocket::SocketState state)
{
    if(state == QAbstractSocket::UnconnectedState)
    {
        return _socket.close();
    }

    emit stateChanged(state);
}

QAbstractSocket::SocketState Device_connect::state()
{
    return _socket.state();
}

bool Device_connect::isConnected()
{
    return _socket.state() == QAbstractSocket::ConnectedState;
}

void Device_connect::sendMessage(QString message)
{
    _socket.write(message.toUtf8());
}

void Device_connect::socket_readyRead()
{
    auto data = _socket.readAll();
    emit dataReady(data); // creates a mannually signal to emit,handle the slot in mainwindow.cpp -> Device_connect::dataReady
}



