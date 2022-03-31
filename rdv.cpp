#include "rdv.h"


rdv::rdv()
{

}

rdv::rdv(int NUM_RDV, QDate DATE_RDV ,QString TYPE,QString EMAIL){
    this->NUM_RDV=NUM_RDV;
    this->DATE_RDV=DATE_RDV;
    this->TYPE=TYPE;
     this->EMAIL=EMAIL;
}
bool rdv::ajouter(){
    QSqlQuery query;
    QString res = QString::number(NUM_RDV);
    query.prepare("insert into rdv values (:NUM_RDV, :DATE_RDV , :TYPE,:EMAIL)");
    query.bindValue(":NUM_RDV",res);
    query.bindValue(":DATE_RDV", DATE_RDV);
    query.bindValue(":TYPE",TYPE);
    query.bindValue(":EMAIL",EMAIL);


    return query.exec();
}
QSqlQueryModel * rdv::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from RDV");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("NUM_RDV"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("DATE_RDV"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("EMAIL"));

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
    query.bindValue(":EMAIL",EMAIL);


    return query.exec();
}
/*
 QSqlQueryModel* rdv:: rechercher(QString TYPE){
   QSqlQueryModel* model = new QSqlQueryModel();
   QString search = "%"+TYPE+"%";
    model->setQuery("SELECT * FROM RDV WHERE num like '"+search+"'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("TYPE"));
    return model ;
}

*/


QSqlQueryModel* rdv::Rechercherdv(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM RDV WHERE NUM_RDV LIKE '"+recherche+"%'");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_RDV"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_RDV"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));

return model;
}
QSqlQueryModel * rdv::tricroi()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from RDV order by NUM_RDV "  );
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_RDV"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_RDV"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    return model;

}
QSqlQueryModel * rdv::tridecroi()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from RDV order by NUM_RDV desc "  );
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_RDV"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_RDV"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    return model;

}

