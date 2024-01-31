#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtEndian>
#include <QMessageBox>

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
    void on_SentButton_clicked();
    void on_ReciveButton_clicked();
    void on_Connect_clicked();
    void on_Disconnect_clicked();
    void on_Check_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort port;
    void onRead();
    QByteArray port_read;
    QSerialPortInfo infoPort;
    unsigned int xcrc32(QVector<quint8> data, unsigned int init);
    quint32 CheckCrc;
    quint32 receivedCrc;
    quint32 sentCrc;
    static const unsigned int crc32_table[];
    quint32 calculateCRC(QVector<quint8> &data);
};
#endif // MAINWINDOW_H
