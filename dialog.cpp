#include "dialog.h"
#include "ui_dialog.h"



Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lcdNumber->display("----");
    arduino_is_available = false;

    arduino_port_name = "";
    arduino = new QSerialPort;
    serialbuffer ="" ;



    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier()){
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }


    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }
    }

    if(arduino_is_available){
        // open and configure the serialport
        arduino->setPortName(arduino_port_name);

        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->open(QSerialPort::ReadOnly);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
    }else{
        // give error message if not available
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }
}

void Dialog::readSerial()
{


  serialdata = arduino->readAll();
  serialbuffer = QString::fromStdString(serialdata.toStdString());
      if(counter ==true ){
       ui->lcdNumber->display(serialbuffer);
      }
  counter = true ;

}

Dialog::~Dialog()
{

    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;

}

