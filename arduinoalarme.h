#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QSqlQueryModel>

class Arduinoalarme
{
public:     //méthodes de la classe Arduino
    Arduinoalarme();
    int connect_arduinoA(); // permet de connecter le PC à Arduino
    int close_arduinoA(); // permet de femer la connexion
    int write_to_arduinoA( QByteArray ); // envoyer des données vers arduino
    QByteArray read_from_arduinoA();  //recevoir des données de la carte Arduino
    QSerialPort* getserialA();   // accesseur
    QString getarduino_port_nameA();
    QSqlQueryModel * afficherAlarmeA();
private:
QSerialPort * serialA; //Cet objet rassemble des informations (vitesse, bits de données, etc.)
//et des fonctions (envoi, lecture de réception,…) sur ce qu’est une voie série pour Arduino.
static const quint16 arduino_uno_vendor_id=9025;//**
static const quint16 arduino_uno_producy_id=67;//**
QString arduino_port_nameA;
bool arduino_is_availableA;
QByteArray data1;  // contenant les données lues à partir d'Arduino
};

#endif // ARDUINO_H
