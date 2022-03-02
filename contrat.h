#ifndef CONTRAT_H
#define CONTRAT_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>
#include <QTableView>

class Contrat
{
public:
    Contrat();
    Contrat(int,QDate,int,QString,QString,int);
    int getnum();
    QDate getdate_s();
    int getmontant();
    QString gettype();
    QString getmode();
    int getcin();
    void setnum(int);
    void setdate(QDate);
    void setmontant(int);
    void settype(QString);
    void setmode(QString);
    void setcin(int);
    bool ajouter();
    bool modifier (int,QDate,int,QString,QString,int);
    QSqlQueryModel* afficher();
    bool supprimer(int);

private:
    int numc;
    QDate  date_signification;
    int montant;
    QString  typec,mode_paiement;
    int cin;

};

#endif // CONTRAT_H
