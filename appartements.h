#ifndef APPARTEMENTS_H
#define APPARTEMENTS_H
#include <QString>
#include<QSqlQuery>
#include <QSqlQueryModel>

class Appartements
{
public:
    Appartements();
    Appartements( QString,int,int,QString,int);
     QString getid_appartement();
    QString getdescription_A();
    int getnb_chambres();
    int getprix();
     int getid_immeuble();
    void setid_appartement(QString);
    void setdescription_A(QString);
    void setnb_chambres(int);
    void setprix(int);
     void setid_immeuble(int);
    bool ajouter();
    bool modifier( QString,int,int,QString,int);
    QSqlQueryModel*afficher();
    bool supprimer( QString);
    QSqlQueryModel*triercroissant();
    QSqlQueryModel*trierdecroissant();
     QSqlQueryModel*rechercher( QString);


private:
   QString id_appartement;
   int prix;
   int nb_chambres;
   QString description_A;

   int id_immeuble;

};

#endif // APPARTEMENTS_H
