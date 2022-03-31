#include "rdv.h"


rdv::rdv()
{

}

rdv::rdv(int NUM_RDV, QDate DATE_RDV ,QString TYPE){
    this->NUM_RDV=NUM_RDV;
    this->DATE_RDV=DATE_RDV;
    this->TYPE=TYPE;
}
bool rdv::ajouter(){
    QSqlQuery query;
    QString res = QString::number(NUM_RDV);
    query.prepare("insert into rdv values (:NUM_RDV, :DATE_RDV , :TYPE)");
    query.bindValue(":NUM_RDV",res);
    query.bindValue(":DATE_RDV", DATE_RDV);
    query.bindValue(":TYPE",TYPE);

    return query.exec();
}
QSqlQueryModel * rdv::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from RDV");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("NUM_RDV"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("DATE_RDV"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("type"));
    return model;
}
bool rdv::supprimer(int NUM_RDV){
    QSqlQuery query;
    QString res = QString::number(NUM_RDV);
    query.prepare("delete from RDV where NUM_RDV = :NUM_RDV");
    query.bindValue(":NUM_RDV", res);
    return query.exec();
}
bool rdv::modifier(){
    QSqlQuery query;
    QString res = QString::number(NUM_RDV);
    query.prepare("update RDV SET DATE_RDV = :DATE_RDV, TYPE=:TYPE where NUM_RDV = :NUM_RDV");
    query.bindValue(":NUM_RDV",res);
    query.bindValue(":DATE_RDV", DATE_RDV);
    query.bindValue(":TYPE",TYPE);

    return query.exec();
}
