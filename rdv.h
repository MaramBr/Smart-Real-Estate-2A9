#ifndef RDV_H
#define RDV_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class rdv
{
//private:
    QString TYPE ;
    QDate DATE_RDV ;
    int NUM_RDV;
    QString EMAIL;
public:
    rdv();
    rdv(int, QDate,QString,QString);

    //Getters
    int getNumRdv(){
        return NUM_RDV;
    }
    QDate getDate(){
        return DATE_RDV;
    }
    QString getTYPE(){
        return TYPE;
    }
    QString getEMAIL(){
        return EMAIL;
    }
    //Setters
    void setNumRdv(int n){
        NUM_RDV=n;
    }
    void setDate(QDate n){
        DATE_RDV=n;
    }
    void setTYPE(QString n){
        TYPE=n;
    } void setEmail(QString n){
       EMAIL=n;
    }

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* Rechercherdv(QString);
    //QSqlQueryModel * rechercher(QString);
    QSqlQueryModel * tricroi();
     QSqlQueryModel * tridecroi();
};



#endif // RDV_H
