#ifndef DEVICE_CONNECT_H
#define DEVICE_CONNECT_H

#include <QtNetwork>
#include <QObject>
#include <QHostAddress>



class Device_connect : public QObject
{
    Q_OBJECT

public:
    explicit Device_connect(QObject *parent = nullptr);
    void connectToDevice(QString ip , int port);
    void disconnect();
    bool isConnected();
    QAbstractSocket::SocketState state();
    void sendMessage(QString message);


signals:
    void connected();
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState);
    void errorOccurred(QAbstractSocket::SocketError);
    void dataReady(QByteArray data);


private slots:
    void socket_State(QAbstractSocket::SocketState state);
    void socket_readyRead();

private:

    QTcpSocket _socket; // TCP
    QString _ip; // localhost 127.0.0.1
    int _port; // free ports from 1024 to 49151
};

#endif // DEVICE_CONNECT_H
