#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
   // connect(ui->writeButton,SIGNAL(clicked(bool)),this,SLOT(led()));
    ui->Log->setReadOnly(1);
    ui->Red_slider->setRange(0,255);
    ui->Blue_slider->setRange(0,255);
    ui->Green_slider->setRange(0,255);
    connect(ui->Red_slider,SIGNAL(valueChanged(int)),this,SLOT(updateRed(int)));
    connect(ui->Green_slider, SIGNAL(valueChanged(int)),this,SLOT(updateGreen(int)));
    connect(ui->Blue_slider, SIGNAL(valueChanged(int)),this, SLOT(updateBlue(int)));
    arduinoIsAvailable= false;
    arduino_Portname = "";
    arduino = new QSerialPort;
    ui->Log->append("Number of available serial ports: " + QString::number( QSerialPortInfo::availablePorts().length()));
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
      ui->Log->append("Port name: "+info.portName());
      ui->Log->append("Has vendor id: " +QString::number( info.hasVendorIdentifier()));
        if(info.hasVendorIdentifier()) ui->Log->append("Vendor ID: " + QString::number( info.vendorIdentifier()));
        ui->Log->append("Has product id: " + QString::number( info.hasProductIdentifier()));
        if(info.hasProductIdentifier()) ui->Log->append("Product ID: " + QString::number( info.productIdentifier()));

    }
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if(info.hasProductIdentifier() && info.hasVendorIdentifier())
        {
            if(info.vendorIdentifier() ==9025 && info.productIdentifier() ==67)
            {
                arduinoIsAvailable = true;
                arduino_Portname = info.portName();
                ui->Log->append("Arduino is available and connected to "+arduino_Portname+" port");
            }
        }
    }
    if(arduinoIsAvailable)
    {

       arduino->setPortName(arduino_Portname);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }
    else ui->Log->append("Arduino is not available. Please connect the Arduino and restart the program");


}

MainWindow::~MainWindow()
{
    if(arduino->isOpen()) arduino->close();
    delete ui;

}

void MainWindow::led()
{
    QString command ="a";
    qDebug()<<  arduino->write(command.toStdString().c_str());
}

void MainWindow::updateRed(int red)
{
    ui->Red_number->setText(QString::number(red));
    if(arduinoIsAvailable)
    {
        QString command("r"+QString::number(red));
        qDebug()<<command;
        arduino->write(command.toStdString().c_str());
    }
}

void MainWindow::updateGreen(int green)
{
    ui->Green_number->setText(QString::number(green));
    if(arduinoIsAvailable)
    {
        QString command("g"+QString::number(green));
        qDebug()<<command;
        arduino->write(command.toStdString().c_str());
    }
}

void MainWindow::updateBlue(int blue)
{
    ui->Blue_number->setText(QString::number(blue));
    if(arduinoIsAvailable)
    {
        QString command("b"+QString::number(blue));
        qDebug()<<command;
        arduino->write(command.toStdString().c_str());
    }
}


