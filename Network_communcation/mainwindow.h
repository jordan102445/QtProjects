#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "client_site.h"
#include "server_site.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    //Client site
    void device_connected();
    void device_disconnected();
    void device_stateChanged(QAbstractSocket::SocketState);
    void device_errorOccurred(QAbstractSocket::SocketError);
    void on_ButConDis_clicked();
    void on_IpEdit_textChanged(const QString &arg1);
    void device_dataReady(QByteArray data);
     void on_SentClient_clicked();
    //Server site
    void newClientConnected();
    void clientDisconnected();
    void clientDataRecived(QString message);
    void on_ServerConnect_clicked();





    void on_SentServer_clicked();

private:
    Ui::MainWindow *ui;
    Device_connect _connectedDevice;
    Server_site * _server;
    void setDeviceController();
    static const unsigned int crc32_table[];
    unsigned int xcrc32(QVector<quint8> data, unsigned int init);
    quint32 calculateCRC(QVector<quint8> &data);
    quint32 sentCrc;
    quint32 calculatedCrc;
    QVector<quint8> quint8Vector;
    QDataStream stream;
    QByteArray messageByte;
    enum states{START, DATALENGTH, DATA, CRC_BYTE, END};
    QByteArray recivedDataCheck;
    QByteArray convertCRC;
    QString recivedData;
    QString convertedDataString;
    quint32 crcValue;

};
#endif // MAINWINDOW_H
