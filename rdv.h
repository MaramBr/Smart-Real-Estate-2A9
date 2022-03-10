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
public:
    rdv();
    rdv(int, QDate,QString);

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

    //Setters
    void setNumRdv(int n){
        NUM_RDV=n;
    }
    void setDate(QDate n){
        DATE_RDV=n;
    }
    void setTYPE(QString n){
        TYPE=n;
    }

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel * tricroi();
     QSqlQueryModel * tridecroi();
};



#endif // RDV_H
