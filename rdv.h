#ifndef RDV_H
#define RDV_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <qcustomplot.h>
#include <smtp.h>
#include <QFileDialog>
class rdv
{
//private:
    QString TYPE_R ;
    QString DATE_RDV ;
    int NUM_RDV;
    QString EMAIL;
public:
    rdv();
    rdv(int, QString,QString,QString);

    //Getters
    int getNumRdv(){
        return NUM_RDV;
    }
    QString getDate(){
        return DATE_RDV;
    }
    QString getTYPE(){
        return TYPE_R;
    }
    QString getEMAIL(){
        return EMAIL;
    }
    //Setters
    void setNumRdv(int n){
        NUM_RDV=n;
    }
    void setDate(QString n){
        DATE_RDV=n;
    }
    void setTYPE(QString n){
        TYPE_R=n;
    } void setEmail(QString n){
       EMAIL=n;
    }

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* Rechercherdv(QString);
    QSqlQueryModel* recherche_date(QString);
     //QSqlQueryModel * rechercher(QString);
    QSqlQueryModel * tricroi();
    QSqlQueryModel * tridecroi();
    void statrdv(QCustomPlot *customPlot);

};



#endif // RDV_H

