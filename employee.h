#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QSqlQueryModel>
#include<QSqlQuery>
#include<qcustomplot.h>


class employee
{
public:
    employee();     //constructeur par defaut
    employee(int,QString,QString,int,QString,QString,QString,int,int); //constructeur parametrer

    int getid();   //affecter des nouvelles valeurs
    QString getnom();
    QString getprenom();
    int gettel();
    QString getmdp();
    QString getadr();
    QString gettype();
    int getprime();
    int getsalaire();

    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void settel(int);
    void setmdp(QString);
    void setadr(QString);
    void settype(QString);
    void setprime(int);
    void setsalaire(int);
    bool ajouter(); //pas de parametre car elle a acces aux toutes les parametres
    bool modifier(int,QString,QString,int,QString,QString,QString,int,int);
    QSqlQueryModel * afficher(); //un modele des infos
    bool supprimer(int);
    QSqlQueryModel*triercroissant();
    QSqlQueryModel*trierdecroissant();
      QSqlQueryModel *rechercher(QString);
      void stat(QCustomPlot *customPlot);
     // bool oublieMDP(QString );




    private:
    int id_employe;   //presenter les attributs
    QString nom_e;
    QString prenom_e;
    int num_tel_e;
    QString mdp;
    QString adresse_e;
    QString type_e;
    int salaire;
    int prime;
};

#endif // EMPLOYEE_H
