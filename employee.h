#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QSqlQueryModel>

class employee
{
public:
    employee();
    employee(int,QString,QString,int,QString,QString,QString,int,int);
    int getid();
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
bool ajouter();
bool modifier(int,QString,QString,int,QString,QString,QString,int,int);
QSqlQueryModel * afficher();
bool supprimer(int);
private:
int id_employe,num_tel_e,salaire,prime;
QString nom_e,prenom_e,mdp,adresse_e,type_e;
};

#endif // EMPLOYEE_H
