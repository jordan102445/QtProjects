#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    publisherObject(new publisher(this))
{
    ui->setupUi(this);

    // Connect signals and slots
    connect(ui->buttonConnect, &QPushButton::clicked, this, &MainWindow::on_buttonConnect_clicked);
    connect(ui->buttonSubscribe,&QPushButton::clicked, this, &MainWindow::on_buttonSubscribe_clicked);
    connect(publisherObject, &publisher::connectedStateChangedConnected, this, &MainWindow::clientConnected);
    connect(publisherObject, &publisher::connectedStateChangedDisconnected, this, &MainWindow::clientDissconted);
    //connect(publisherObject, &publisher::recivedData,this,&MainWindow::publishMessageRecived);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonConnect_clicked()
{
    QString brokerAddress = ui->lineEditHost->text();
    quint16 port = ui->spinBoxPort->value();

    // Connect to MQTT broker
    publisherObject->connectToBroker(brokerAddress, port);
}

void MainWindow::clientConnected()
{
    qDebug() << "Client connected to the broker";
}

void MainWindow::clientDissconted()
{
    qDebug() << "Client disconnected from the broker";
}

void MainWindow::on_buttonSubscribe_clicked()
{
    // Get topic from UI
    QString topic = ui->lineEditTopic->text();
    quint16 Qos = ui->spinQoS->value();
    publisherObject->subscribeTopic(topic, Qos);


}

void MainWindow::on_buttonPublish_clicked()
{
    QString messageSent = ui->lineEditMessage->text();
    QString topic = ui->lineEditTopic->text();
    quint16 Qos = ui->spinQoS_2->value();
    bool retainCheck = ui->checkBoxRetain->checkState();

    publisherObject->publishMessage(topic,messageSent,Qos,retainCheck);

}

void MainWindow::publishMessageRecived(QByteArray data)
{
    ui->textEdit->setText(QString::fromUtf8(data));
}

