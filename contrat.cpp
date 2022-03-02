#include "contrat.h"
#include <QString>
#include <QSqlQuery>
#include <QDate>
#include <QObject>
Contrat::Contrat()
{
numc=0;
montant=0;
typec="";
mode_paiement="";
cin=0;


}
Contrat::Contrat(int numc, QDate date_signification , int montant , QString typec , QString mode_paiement ,int cin)
{
    this->numc=numc;
    this->date_signification=date_signification;
    this->montant=montant;
    this->typec=typec;
    this->mode_paiement=mode_paiement;
    this->cin=cin;
}
int Contrat::getnum(){return numc;}
QDate Contrat::getdate_s(){return date_signification;}
int Contrat::getmontant(){return montant;}
QString Contrat::gettype(){return typec;}
QString Contrat::getmode(){return mode_paiement;}
int Contrat::getcin(){return cin;}
void Contrat::setnum(int numc){this->numc=numc;}
void Contrat::setdate(QDate date_signification){this->date_signification=date_signification;}
void Contrat::setmontant(int montant){this->montant=montant;}
void Contrat::settype(QString typec){this->typec=typec;}
void Contrat ::setmode(QString mode_paiement){this->mode_paiement=mode_paiement;}
void Contrat::setcin(int cin) {this->cin=cin;}
bool Contrat::ajouter()
{

    QString numc_string=QString::number(numc);
    QString montant_string=QString::number(montant);
    QString cin_string=QString::number(cin);
    QSqlQuery query;

    query.prepare("INSERT INTO CONTRATS (numc,date_signification,montant,typec,mode_paiement,cin) "
                  "VALUES (:numc,:date_signification,:montant,:typec,:mode_paiement,:cin)");
    query.bindValue(":numc",numc_string);
    query.bindValue(":date_signification",date_signification);
    query.bindValue(":montant",montant_string);
    query.bindValue(":typec",typec);
    query.bindValue(":mode_paiement",mode_paiement);
    query.bindValue(":cin",cin_string);

    return query.exec();

}
bool Contrat::modifier(int numc,QDate date_signification,int montant,QString typec,QString mode_paiement,int cin)
{
    QString numcf=QString::number(numc);
    QString montant_string=QString::number(montant);
    QString cin_string=QString::number(cin);
    QSqlQuery query;
   query.prepare("update contrats set numc=:numc,date_signification=:date_signification,montant=:montant,typec=:typec,mode_paiement=:mode_paiement,cin=:cin where numc=:numc");
   query.bindValue(":numc",numcf);
   query.bindValue(":date_signification",date_signification);
   query.bindValue(":montant",montant_string);
   query.bindValue(":typec",typec);
   query.bindValue(":mode_paiement",mode_paiement);
   query.bindValue(":cin",cin_string);
   return query.exec();

}
bool Contrat::supprimer(int numc)
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

