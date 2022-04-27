#ifndef IMMEUBLE_H
#define IMMEUBLE_H
#include "qcustomplot.h"
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>


class immeuble
{
    //private:
        QString adresse, description;
        int id_immeuble,nb_etages;
public:
    immeuble();
    immeuble(int, int ,QString,QString);

    //Getters
    int getId(){
        return id_immeuble;
    }
    int getEtage(){
        return nb_etages;
    }
    QString getAdresse(){
        return adresse;
    }
    QString getDescription(){
        return description;
    }
    //Setters
    void setAdresse(QString n){
        adresse=n;
    }
    void setDescription(QString n){
        description=n;
    }
    void setId(int n){
        id_immeuble=n;
    }
    void setEtage(int n){
        nb_etages=n;
    }
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel* triercroissant();
    QSqlQueryModel* trierdecroissant();
    QSqlQueryModel* chercher(QString );
     void statimmeuble(QCustomPlot *customPlot);

};


#endif // IMMEUBLE_H
