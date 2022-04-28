#include "arduinoalarme.h"

Arduinoalarme::Arduinoalarme()
{
    data1="";
    arduino_port_nameA="";
    arduino_is_availableA=false;
    serialA=new QSerialPort;
}

QString Arduinoalarme::getarduino_port_nameA()
{
    return arduino_port_nameA;
}

QSerialPort *Arduinoalarme::getserialA()
{
   return serialA;
}
int Arduinoalarme::connect_arduinoA()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                       == arduino_uno_producy_id) {
                   arduino_is_availableA = true;
                   arduino_port_nameA=serial_port_info.portName();
               } } }
        qDebug() << "arduino_port_name is :" << arduino_port_nameA;
        if(arduino_is_availableA){ // configuration de la communication ( débit...)
            serialA->setPortName(arduino_port_nameA);
            if(serialA->open(QSerialPort::ReadWrite)){
                serialA->setBaudRate(QSerialPort::Baud115200); // débit : 115200 bits/s
                serialA->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
                serialA->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
                serialA->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
                serialA->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}

int Arduinoalarme::close_arduinoA()

{

    if(serialA->isOpen()){
            serialA->close();
            return 0;
        }
    return 1;


}


 QByteArray Arduinoalarme::read_from_arduinoA()
{
    if(serialA->isReadable())
    {
         data1=serialA->readAll(); //récupérer les données reçues

         return data1;
    }
 }


int Arduinoalarme::write_to_arduinoA( QByteArray d)

{

    if(serialA->isWritable()){
        serialA->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }


}

QSqlQueryModel * Arduinoalarme::afficherAlarmeA()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from alarme");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Distance"));
    return model;
}

