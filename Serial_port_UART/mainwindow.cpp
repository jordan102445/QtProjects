#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_port(this)

{
    ui->setupUi(this);

    ui->checkBox->setEnabled(false);

    connect(&m_port , &QSerialPort::readyRead, this, &MainWindow::onReadyRead);
    QList<QSerialPortInfo> ports = m_serialPortInfo.availablePorts();

    connect(&timer, &QTimer::timeout, this, &MainWindow::resetLedColor);
    timer.setSingleShot(false);

    // ui->ledGreen->setStyleSheet("background-color: #00FF00; border: 1px solid #c0c0c0;");
    ui->ledRed->setStyleSheet("background-color: #FF0000; border: 1px solid #c0c0c0;");




    for (const QSerialPortInfo &portInfo : ports) {
        ui->comboBox->addItem(portInfo.portName());

        qDebug() << "\n"
                 << "Port:" << portInfo.portName() << "\n"
                 << "Port:" << portInfo.standardBaudRates() << "\n"
                 << "Location:" << portInfo.systemLocation() << "\n"
                 << "Description:" << portInfo.description() << "\n"
                 << "Manufacturer:" << portInfo.manufacturer() << "\n"
                 << "Serial number:" << portInfo.serialNumber() << "\n"
                 << "Vendor Identifier:"
                 << (portInfo.hasVendorIdentifier()
                         ? QByteArray::number(portInfo.vendorIdentifier(), 16)
                         : QByteArray()) << "\n"
                 << "Product Identifier:"
                 << (portInfo.hasProductIdentifier()
                         ? QByteArray::number(portInfo.productIdentifier(), 16)
                         : QByteArray());
    }

    foreach (const qint32 baudRate, QSerialPortInfo::standardBaudRates()) {
        ui->Baud_rate->addItem(QString::number(baudRate));
    }

    ui->Parity->addItem("No Parity");
    ui->Parity->addItem("Even Parity");
    ui->Parity->addItem("Odd Parity");

    ui->Stop_bits->addItem("1 Bit");
    ui->Stop_bits->addItem("1,5 Bits");
    ui->Stop_bits->addItem("2 Bits");

     ui->Data->addItem("5");
     ui->Data->addItem("6");
     ui->Data->addItem("7");
     ui->Data->addItem("8");

    ui->Flow_control->addItem("No Flow Control");
    ui->Flow_control->addItem("Hardware Flow Control");
    ui->Flow_control->addItem("Software Flow Control");







}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetLedColor() {
    ui->ledGreen->setStyleSheet("background-color: #FFFFFF;");
}

void MainWindow::onReadyRead() {
    m_receivedData.append(m_port.readAll());
    //QString receivedText = QString::fromUtf8(m_receivedData);





    if (!m_receivedData.isEmpty()) {
        // Data is received
        ui->Output->setText(m_receivedData.toHex());
        ui->ledGreen->setStyleSheet("background-color: #00FF00;");

        if (timer.isActive()) {
            timer.stop();
        }
        timer.start(2000);
    } else {
        // No data received
        ui->Output->setText("No data received");
        ui->ledGreen->setStyleSheet("background-color: #FFFFFF;");
   }
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    // if (ui->checkBox->checkState() == Qt::Checked)
    //     m_port.write(" 1 ");
    // else
    //     m_port.write(" 0 ");
}


QByteArray MainWindow::createMessage(const qint64& command)
{
    QByteArray message;
    if(m_port.stopBits() == QSerialPort::OneStop)
    {
        // Start bit
        qint8 startBit = 0;
        message.append(startBit);
        // Start bit
        message.append(command);
        // Stop bit
        qint8 stopBit = 1;
        message.append(stopBit);
        // Stop bit

    }
    else if(m_port.stopBits() == QSerialPort::TwoStop)
    {
        // Start bit
        qint8 startBit = 0;
        message.append(startBit);
        // Start bit
        message.append(command);
        // Stop bit
        qint8 stopBit = 1;
        qint8 stopBitTwo = 1;
        message.append(stopBit);
        message.append(stopBitTwo);
        // Stop bit

    }
    return message;
}
void MainWindow::printBinary(const QByteArray& data)
{
    for (char byte : data) {
        for (int i = 7; i >= 0; --i) {
            qDebug() << ((byte >> i) & 1);
        }
    }
}

QByteArray MainWindow::createDataFrame(int value)
{
    // Example: Creating a DataFrame with an integer value
    QByteArray dataFrame;
    dataFrame.append('<');  // Start of the frame
    dataFrame.append(QString::number(value).toUtf8());  // Convert integer to QByteArray
    dataFrame.append('>');  // End of the frame
    return dataFrame;
}

void MainWindow::on_dial_valueChanged(int value)
{
    int startBitInt = 0xAA;
    char startBit = (char) startBitInt;
    m_port.write(&startBit,0x01);
    char byteToSendDial1 = (char)value;
    char byteToSendDial2 = (char)ui->dial_2->value();
    m_port.write(&byteToSendDial1,0x01);
    m_port.write(&byteToSendDial2,0x01);
    int stopBitInt = 0xBB;
    char stopBit = (char)stopBitInt;
    m_port.write(&stopBit,0x01);

    if(m_port.isWritable())
    {
        qDebug("The bytes are  sendend FROM DIAL 1");
    }
    else
    {
        qDebug("The bytes are not sendend FROM DIAL 1");
    }

    ui->DialText->setText(QString::number(value));

}

void MainWindow::on_dial_2_valueChanged(int value)
{

    int startBitInt = 0xAA;
    char startBit = (char) startBitInt;
    m_port.write(&startBit,0x01);
    char byteToSendDial = (char)value;
    char byteToSendDial1 = (char)ui->dial->value();
    m_port.write(&byteToSendDial1,0x01);
    m_port.write(&byteToSendDial,0x01);
    int stopBitInt = 0xBB;
    char stopBit = (char)stopBitInt;
    m_port.write(&stopBit,0x01);

    if(m_port.isWritable())
    {
        qDebug("The bytes are  sendend FROM DIAL 2");
    }
    else
    {
        qDebug("The bytes are not sendend FROM DIAL 2");
    }

    ui->DialText_2->setText(QString::number(value));

    // // QByteArray sendData = QByteArray::number(value);
    // // m_port.write(sendData);
    // // QByteArray sendData;
    // // sendData.append(value);
    // // m_port.write(sendData);

}

void MainWindow::on_Disconnect_clicked()
{
    if(m_port.isOpen())
    {
        m_port.close();
        ui->ledstatus->setText("Disconnected");
        ui->checkBox->setEnabled(false);
        ui->checkBox->setCheckState(Qt::Unchecked);
        ui->comboBox->setCurrentText(" ");
    }

}

void MainWindow::on_Connect_clicked()
{
    auto portName = ui->comboBox->currentText();
        // QByteArray sendData = baudRate.toUtf8();
    // m_port.write(sendData);
    // m_port.write("\r\n");



    m_port.setPortName(portName);

    QString stringbaudRate = ui->Baud_rate->currentText();
    int intbaudRate = stringbaudRate.toInt();
    m_port.setBaudRate(intbaudRate);



    //QByteArray checkBaudRate = QByteArray::number(intbaudRate);
    //m_port.write(checkBaudRate);

    qDebug() << "Current baudrate" << m_port.baudRate();

   QString dataBitss = ui->Data->currentText();
    if(dataBitss == "5 Bits") {
         m_port.setDataBits(QSerialPort::DataBits::Data5);
     }
     else if((dataBitss == "6 Bits")) {
         m_port.setDataBits(QSerialPort::DataBits::Data6);
     }
     else if(dataBitss == "7 Bits") {
         m_port.setDataBits(QSerialPort::DataBits::Data7);
     }
     else if(dataBitss == "8 Bits"){
         m_port.setDataBits(QSerialPort::DataBits::Data8);
     }

    m_port.setDataBits(QSerialPort::DataBits::Data8);
    qDebug() << "Current Data Bits:" << m_port.dataBits();

    QString stopBits = ui->Stop_bits->currentText();
    if(stopBits == "1 Bit") {
        m_port.setStopBits(QSerialPort::StopBits::OneStop);
    }
    else if(stopBits == "1,5 Bits") {
        m_port.setStopBits(QSerialPort::StopBits::OneAndHalfStop);
    }
    else if(stopBits == "2 Bits") {
        m_port.setStopBits(QSerialPort::StopBits::TwoStop);
    }

    qDebug() << "Current STOP bits:" << m_port.stopBits();

    QString parity = ui->Parity->currentText();
    if(parity == "No Parity"){
        m_port.setParity(QSerialPort::Parity::NoParity);
    }
    else if(parity == "Even Parity"){
        m_port.setParity(QSerialPort::Parity::EvenParity);
    }
    else if(parity == "Odd Parity"){
        m_port.setParity(QSerialPort::Parity::OddParity);
    }

    qDebug() << "Current parity" << m_port.parity();

    QString flowControl = ui->Flow_control->currentText();
    if(flowControl == "No Flow Control") {
        m_port.setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    }
    else if(flowControl == "Hardware Flow Control") {
        m_port.setFlowControl(QSerialPort::FlowControl::HardwareControl);
    }
    else if(flowControl == "Software Flow Control") {
        m_port.setFlowControl(QSerialPort::FlowControl::SoftwareControl);
    }

    qDebug() << "Current flow control" << m_port.flowControl();

    m_port.open(QIODevice::ReadWrite);
    if (!portName.isEmpty())
    {

        if(m_port.isOpen())
        {
            ui->ledstatus->setText("Connected");
            ui->checkBox->setEnabled(true);
            ui->checkBox->setCheckState(Qt::Checked);

                 // int startBitInt = 0xAA;
                 // char startBit = (char) startBitInt;
                 // m_port.write(&startBit,0x01);
                 // char byteToSendDial1 = (char)ui->dial->value();
                 // char byteToSendDial2 = (char)ui->dial_2->value();
                 // m_port.write(&byteToSendDial1,0x01);
                 // m_port.write(&byteToSendDial2,0x01);
                 // int stopBitInt = 0xBB;
                 // char stopBit = (char)stopBitInt;
                 // m_port.write(&stopBit,0x01);

        }
        else
        {
            ui->ledstatus->setText("Not Connected");

        }

    }



}
void MainWindow::on_SendData_clicked()
{
    if(m_port.isOpen())
    {
        QString data = ui->Input->text();
    }
}

void MainWindow::on_OutputData_clicked()
{
    //readDataFromSerialPort();
    ui->Output->setText(QString(m_receivedData));
    m_receivedData.clear();

    if(ui->Output->text() != "0")
    {
        ui->ledGreen->setStyleSheet("background-color: #00FF00; border: 1px solid #c0c0c0;");
    }

}




