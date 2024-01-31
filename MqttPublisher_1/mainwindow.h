#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMqtt>
#include <QMqttMessage>
#include <QMqttSubscription>
#include <QtEndian>

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
    void onPublishButtonClicked();
    void onMqttStateChanged(QMqttClient::ClientState state);
    void on_buttonConnect_clicked();
    void on_subButton_clicked();
    void onMessageReceived(const QMqttMessage &message);
    void onMqttSubcriberState(QMqttSubscription::SubscriptionState state);

private:
    Ui::MainWindow *ui;
    QMqttClient *mqttClient;
    QMqttSubscription *mqttSubcribe;
    static const unsigned int crc32_table[];
    unsigned int xcrc32(QVector<quint8> data, unsigned int init);
    quint32 calculateCRC(QVector<quint8> &data);
    quint32 calculatedCrc;
    quint32 checkCrcRecived;
    QVector<quint8> quint8Vector;
    QDataStream stream;
    QByteArray messageByte;
    enum states{START, DATALENGTH, DATA, CRC_BYTE, END};
};
#endif // MAINWINDOW_H
