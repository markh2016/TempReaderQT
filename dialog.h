#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
void readSerial();

private:
    Ui::Dialog *ui;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id =  6790 ; //9025;
    static const quint16 arduino_uno_product_id = 29987 ; //1;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray serialdata ;
    QString serialbuffer ;
    bool counter = false ;
};

#endif // DIALOG_H
