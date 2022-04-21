#include "immeuble.h"
#include "qcustomplot.h"

#include <QtDebug>

immeuble::immeuble()
{

}
immeuble::immeuble(int id_immeuble, int nb_etages, QString adresse, QString description)
{
    this->id_immeuble=id_immeuble;
    this->nb_etages=nb_etages;
    this->adresse=adresse;
    this->description=description;
}
bool immeuble::ajouter(){
    QSqlQuery query;
    QString res = QString::number(id_immeuble);
    query.prepare("insert into IMMEUBLES values (:id_immeuble, :nb_etages, :adresse, :description)");
    query.bindValue(":id_immeuble",res);
    query.bindValue(":nb_etages", nb_etages);
    query.bindValue(":adresse", adresse);
    query.bindValue(":description", description);

    return query.exec();
}
QSqlQueryModel * immeuble::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from IMMEUBLES");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant Immeuble"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nombre Des Etages"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Description"));

    return model;
}
bool immeuble::supprimer(int id_immeuble){
    QSqlQuery query;
    QString res = QString::number(id_immeuble);
    query.prepare("delete from IMMEUBLES where id_immeuble = :id_immeuble");
    query.bindValue(":id_immeuble", res);
    return query.exec();
}
bool immeuble::modifier(int id_immeuble){
    QSqlQuery query;
    QString res = QString::number(id_immeuble);
    query.prepare("UPDATE IMMEUBLES SET nb_etages = :nb_etages ,adresse = :adresse, description = :description WHERE id_immeuble = :id_immeuble");
    query.bindValue(":id_immeuble",res);
    query.bindValue(":nb_etages", nb_etages);
    query.bindValue(":adresse", adresse);
    query.bindValue(":description", description);
    return query.exec();
}


QSqlQueryModel * immeuble::trier(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from IMMEUBLES order by id_immeuble");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant Immeuble"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nombre Des Etages"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Description"));

    return model;
}
QSqlQueryModel* immeuble::chercher(QString field){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from IMMEUBLES where (adresse) LIKE '%"+field+"%' ");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant Immeuble"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nombre Des Etages"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Description"));

    return model;
}




