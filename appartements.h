#ifndef APPARTEMENTS_H
#define APPARTEMENTS_H
#include <QString>
#include<QSqlQuery>
#include <QSqlQueryModel>

class Appartements
{
public:
    Appartements();
    Appartements(int,int,int,QString,int);
    int getid_appartement();
    QString getdescription_A();
    int getnb_chambres();
    int getprix();
     int getid_immeuble();
    void setid_appartement(int);
    void setdescription_A(QString);
    void setnb_chambres(int);
    void setprix(int);
     void setid_immeuble(int);
    bool ajouter();
    bool modifier(int,int,int,QString,int);
    QSqlQueryModel*afficher();
    bool supprimer(int);
    QSqlQueryModel*triercroissant();
    QSqlQueryModel*trierdecroissant();


private:
   int id_appartement;
   int prix;
   int nb_chambres;
   QString description_A;

   int id_immeuble;

};

#endif // APPARTEMENTS_H
