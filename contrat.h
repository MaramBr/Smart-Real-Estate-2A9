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
    Contrat(QString,QDate,int,QString,QString,QString);
    QString getnum();
    QDate getdate_s();
    int getmontant();
    QString gettype();
    QString getmode();
    QString getcin();
    void setnum(QString);
    void setdate(QDate);
    void setmontant(int);
    void settype(QString);
    void setmode(QString);
    void setcin(QString);
    bool ajouter();
    bool modifier (QString,QDate,int,QString,QString,QString);
    QSqlQueryModel* afficher();
    bool supprimer(QString);
private:
    QString numc;
    QDate  date_signification;
    int montant;
    QString  typec,mode_paiement;
    QString cin;

};

#endif // CONTRAT_H
