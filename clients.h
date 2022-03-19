#ifndef CLIENTS_H
#define CLIENTS_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
class Clients
{
public:
    Clients();
    Clients(QString,QString,QString,QString,QString,QDate);
    QString getcin();
    QString getnom();
    QString getprenom();
    QString getnum();
    QString gettype();
    QDate getdate();
    void setcin(QString);
    void setnom(QString);
    void setprenom(QString);
    void setnum(QString);
    void settype(QString);
    void setdate(QDate);
    bool ajouter();
    bool modifier(QString,QString,QString,QString,QString,QDate);
    QSqlQueryModel*afficher();
    bool supprimer(QString);
    QSqlQueryModel*triercroissant();
    QSqlQueryModel*trierdecroissant();
    QSqlQueryModel*recherche(QString);
    bool excel();

private:
    QString CIN;
    QString nom;
    QString prenom;
    QString num_tel;
    QString type;
    QDate date_ajout;
};

#endif // CLIENTS_H
