#ifndef MQTTPUBLISHER_H
#define MQTTPUBLISHER_H

#include "qobjectdefs.h"
#include <QObject>
#include <QMqttClient>

class publisher : public QObject
{
    Q_OBJECT

public:
    explicit publisher(QObject *parent = nullptr);
    ~publisher();

    void connectToBroker(const QString &brokerAddress, quint16 port);
    void publishMessage(const QString &topic, const QString &message,const quint16 qos,const bool retain);
    void subscribeTopic(const QMqttTopicFilter &topic , const quint16 qos);

public slots:
    void onConnected();
    void onDisconnected();

signals:
    void onPublishFinished(const QMqttPublishProperties &properties, const QByteArray &payload);
    void connectedStateChangedConnected(QMqttClient::ClientState state);
    void connectedStateChangedDisconnected(QMqttClient::ClientState state);
    void recivedData(const QByteArray &payload);


private:
    QMqttClient *mqttClient;
};

#endif // MQTTPUBLISHER_H
