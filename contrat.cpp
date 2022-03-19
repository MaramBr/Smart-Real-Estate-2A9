#include "contrat.h"
#include <QString>
#include <QSqlQuery>
#include <QDate>
#include <QObject>

#include<qiterator.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Contrat::Contrat()
{
numc="";
montant=0;
typec="";
mode_paiement="";
cin="";


}
Contrat::Contrat(QString numc, QDate date_signification , int montant , QString typec , QString mode_paiement ,QString cin)
{
    this->numc=numc;
    this->date_signification=date_signification;
    this->montant=montant;
    this->typec=typec;
    this->mode_paiement=mode_paiement;
    this->cin=cin;
}
QString Contrat::getnum(){return numc;}
QDate Contrat::getdate_s(){return date_signification;}
int Contrat::getmontant(){return montant;}
QString Contrat::gettype(){return typec;}
QString Contrat::getmode(){return mode_paiement;}
QString Contrat::getcin(){return cin;}
void Contrat::setnum(QString numc){this->numc=numc;}
void Contrat::setdate(QDate date_signification){this->date_signification=date_signification;}
void Contrat::setmontant(int montant){this->montant=montant;}
void Contrat::settype(QString typec){this->typec=typec;}
void Contrat ::setmode(QString mode_paiement){this->mode_paiement=mode_paiement;}
void Contrat::setcin(QString cin) {this->cin=cin;}
bool Contrat::ajouter()
{

    //QString numc_string=QString::number(numc);
    QString montant_string=QString::number(montant);

    QSqlQuery query;

    query.prepare("INSERT INTO CONTRATS (numc,date_signification,montant,typec,mode_paiement,cin) "
                  "VALUES (:numc,:date_signification,:montant,:typec,:mode_paiement,:cin)");
    query.bindValue(":numc",numc);
    query.bindValue(":date_signification",date_signification);
    query.bindValue(":montant",montant_string);
    query.bindValue(":typec",typec);
    query.bindValue(":mode_paiement",mode_paiement);
    query.bindValue(":cin",cin);

    return query.exec();

}
bool Contrat::modifier(QString numc,QDate date_signification,int montant,QString typec,QString mode_paiement,QString cin)
{
    //QString numcf=QString::number(numc);
    QString montant_string=QString::number(montant);
    QSqlQuery query;
   query.prepare("update contrats set numc=:numc,date_signification=:date_signification,montant=:montant,typec=:typec,mode_paiement=:mode_paiement,cin=:cin where numc=:numc");
   query.bindValue(":numc",numc);
   query.bindValue(":date_signification",date_signification);
   query.bindValue(":montant",montant_string);
   query.bindValue(":typec",typec);
   query.bindValue(":mode_paiement",mode_paiement);
   query.bindValue(":cin",cin);
   return query.exec();

}
bool Contrat::supprimer(QString numc)
{


    QSqlQuery query;

    query.prepare(" DELETE from contrats where numc=:numc");
    query.bindValue(":numc",numc);

    return query.exec();
}

QSqlQueryModel * Contrat::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select * from CONTRATS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("numc"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_signification"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mode_paiement"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("cin"));
return model;
}
QSqlQueryModel * Contrat::triercroissant()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select * from CONTRATS order by montant asc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("numc"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_signification"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mode_paiement"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("cin"));
return model;
}
QSqlQueryModel * Contrat::trierdecroissant()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select * from CONTRATS order by montant desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("numc"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_signification"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mode_paiement"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("cin"));
return model;
}
QSqlQueryModel * Contrat::recherche(QString numc)
{
    QSqlQueryModel * model= new QSqlQueryModel();
     QString res= numc;
     model->setQuery("select * from contrats where numc='"+res+"'");

    return model;
}

void Contrat::printQr(const QrCode &qr) {
    int border = 4;
    for (int y = -border; y < qr.getSize() + border; y++) {
        for (int x = -border; x < qr.getSize() + border; x++) {
            std::cout << (qr.getModule(x, y) ? "##" : "  ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void Contrat::generateQr()
{
    const char *text = "Soyez les bienvenus chez smartlab!";

    const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW;  // Error correction level

    // Make and print the QR Code symbol
    const QrCode qr = QrCode::encodeText(text, errCorLvl);
    printQr(qr);
    std::cout << toSvgString(qr, 200);
}

 std::string Contrat::toSvgString(const QrCode &qr, int border) {
    if (border < 0)
        throw std::domain_error("Border must be non-negative");
    if (border > INT_MAX / 2 || border * 2 > INT_MAX - qr.getSize())
        throw std::overflow_error("Border too large");

    std::ostringstream sb;
    sb << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    sb << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
    sb << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
    sb << (qr.getSize() + border * 2) << " " << (qr.getSize() + border * 2) << "\" stroke=\"none\">\n";
    sb << "\t<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/>\n";
    sb << "\t<path d=\"";
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            if (qr.getModule(x, y)) {
                if (x != 0 || y != 0)
                    sb << " ";
                sb << "M" << (x + border) << "," << (y + border) << "h1v1h-1z";
            }
        }
    }
    sb << "\" fill=\"#000000\"/>\n";
    sb << "</svg>\n";
    return sb.str();
}



