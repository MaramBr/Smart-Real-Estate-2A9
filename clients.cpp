#include "clients.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include <QObject>
#include <QString>
Clients::Clients()
{
CIN="";
nom="";
prenom="";
num_tel="";
type="";
}

Clients::Clients(QString CIN,QString nom,QString prenom,QString num_tel,QString type,QDate date_ajout)
{
 this->CIN=CIN;
 this->nom=nom;
 this->prenom=prenom;
 this->num_tel=num_tel;
 this->type=type;
 this->date_ajout=date_ajout;
}
QString Clients:: getcin()
{
    return CIN;
}
QString Clients:: getnom()
{
    return nom;
}
QString Clients:: getprenom()
{
    return prenom;
}
QString Clients:: getnum()
{
    return num_tel;
}
QString Clients:: gettype()
{
    return type;
}
QDate Clients:: getdate()
{
    return date_ajout;
}
void Clients:: setcin(QString CIN)
{
     this->CIN=CIN;
}
void Clients:: setnom(QString nom)
{
     this->nom=nom;
}
void Clients:: setprenom(QString prenom)
{
     this->prenom=prenom;
}
void Clients:: setnum(QString num_tel)
{
     this->num_tel=num_tel;
}
void Clients:: settype(QString type)
{
     this->type=type;
}
void Clients:: setdate(QDate date_ajout)
{
     this->date_ajout=date_ajout;
}
bool Clients:: ajouter()
{

        QSqlQuery query;

        query.prepare("INSERT INTO CLIENTS (CIN,nom,prenom,num_tel,type,date_ajout) "
                      "VALUES (:CIN,:nom,:prenom,:num_tel,:type,:date_ajout)");

        query.bindValue(":CIN",CIN);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":num_tel",num_tel);
        query.bindValue(":type",type);
        query.bindValue(":date_ajout",date_ajout);

        return query.exec();
}
bool Clients::modifier(QString CIN, QString nom, QString prenom, QString num_tel, QString type, QDate date_ajout)
{

    QSqlQuery query;
       query.prepare("update clients set CIN=:CIN,nom=:nom,prenom=:prenom,num_tel=:num_tel,type=:type,date_ajout=:date_ajout where CIN=:CIN");

       query.bindValue(":CIN",CIN);
       query.bindValue(":nom",nom);
       query.bindValue(":prenom",prenom);
       query.bindValue(":num_tel",num_tel);
       query.bindValue(":type",type);
       query.bindValue(":date_ajout",date_ajout);

       return query.exec();

}
bool Clients::supprimer(QString CIN)
{
    QSqlQuery query;

    query.prepare(" DELETE from clients where CIN=:CIN");
    query.bindValue(":CIN",CIN);

    return query.exec();
}

QSqlQueryModel*Clients::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select * from clients");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("num_tel"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_ajout"));
return model;
}

