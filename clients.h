#ifndef CLIENTS_H
#define CLIENTS_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
class Clients
{
public:
    Clients();
    Clients(int,QString,QString,int,QString,QDate);
    int getcin();
    QString getnom();
    QString getprenom();
    int getnum();
    QString gettype();
    QDate getdate();
    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setnum(int);
    void settype(QString);
    void setdate(QDate);
    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(int);

private:
    int CIN;
    QString nom;
    QString prenom;
    int num_tel;
    QString type;
    QDate date_ajout;
};

#endif // CLIENTS_H
