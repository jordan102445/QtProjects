#include "publisher.h"

publisher::publisher(QObject *parent)
    : QObject(parent),
    mqttClient(new QMqttClient(this))
{
    connect(mqttClient, &QMqttClient::connected, this, &publisher::onConnected);
    connect(mqttClient, &QMqttClient::disconnected, this, &publisher::onDisconnected);
    //connect(mqttClient, &QMqttClient::messageReceived,this, &publisher::onPublishFinished);
}

publisher::~publisher()
{
    if (mqttClient->state() != QMqttClient::Disconnected)
        mqttClient->disconnect();

    delete mqttClient;
}

void publisher::connectToBroker(const QString &brokerAddress, quint16 port)
{
    mqttClient->setHostname(brokerAddress);
    mqttClient->setPort(port);
    mqttClient->connectToHost();
}

void publisher::publishMessage(const QString &topic, const QString &message,const quint16 qos,const bool retain)
{
    if (mqttClient->state() == QMqttClient::Connected)
    {
        QMqttTopicName mqttTopic(topic);
        QMqttPublishProperties properties;
        mqttClient->publish(mqttTopic, message.toUtf8(), qos,retain);
    }
}

void publisher::subscribeTopic(const QMqttTopicFilter &topic , const quint16 qos)
{
        mqttClient->subscribe(topic,qos);
}

void publisher::onConnected()
{
   emit connectedStateChangedConnected(QMqttClient::Connected);
}

void publisher::onDisconnected()
{

    emit connectedStateChangedDisconnected(QMqttClient::Disconnected);

}

// void publisher::onPublishFinished(const QMqttPublishProperties &properties, const QByteArray &payload)
// {
//     emit recivedData(payload);
// }
