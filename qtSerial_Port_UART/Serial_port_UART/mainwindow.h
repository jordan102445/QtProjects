#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QSerialPortInfo>



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

    void on_checkBox_stateChanged(int arg1);

    void on_dial_valueChanged(int value);

   // void readDataFromSerialPort();


    void on_Disconnect_clicked();

    void on_Connect_clicked();

    void on_SendData_clicked();

    void on_OutputData_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort m_port;
    QSerialPortInfo m_serialPortInfo;
    void onReadyRead();
    QByteArray m_receivedData;
    void onBaudRateChanged(int index);
    void onParityChanged(int index);
    void onStopBitsChanged(int index);
    void onDataBitsChanged(int index);
    void onFlowControlChanged(int index);
    void getParityFromString(QString);
};
#endif // MAINWINDOW_H
