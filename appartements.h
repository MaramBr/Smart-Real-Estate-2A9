#ifndef APPARTEMENTS_H
#define APPARTEMENTS_H
#include <QString>
#include<QSqlQuery>
#include <QSqlQueryModel>
#include <qcustomplot.h>

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
     QImage getimage();
    void setid_appartement(QString);
    void setdescription_A(QString);
    void setnb_chambres(int);
    void setprix(int);
     void setid_immeuble(int);
     void setimage(QImage);
    bool ajouter();
    bool modifier( QString,int,int,QString,int);
    QSqlQueryModel*afficher();
    bool supprimer( QString);
    QSqlQueryModel*triercroissant();
    QSqlQueryModel*trierdecroissant();
     QSqlQueryModel*rechercher( QString);
    bool pdf();
     void stat(QCustomPlot *customPlot);

private:
   QString id_appartement;
   int prix;
   int nb_chambres;
   QString description_A;

   int id_immeuble;
   QImage image;

};

#endif // APPARTEMENTS_H
