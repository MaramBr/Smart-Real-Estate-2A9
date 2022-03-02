#include "employee.h"
#include<QString>
#include<QSqlQuery>
#include<QObject>

employee::employee()
{
id_employe=0;
nom_e="";
prenom_e="";
num_tel_e=0;
mdp="";
adresse_e="";
type_e="";
prime=0;
salaire=0;
}

employee::employee(int id_employe,QString nom_e,QString prenom_e,int num_tel_e,QString mdp,QString adresse_e,QString type_e,int prime,int salaire)
{
 this->id_employe=id_employe;
 this->nom_e=nom_e;
    this->prenom_e=prenom_e;
    this->num_tel_e=num_tel_e;
    this->mdp=mdp;
    this->adresse_e=adresse_e;
    this->type_e=type_e;
    this->prime=prime;
    this->salaire=salaire;
}

int employee::getid(){return id_employe; }
QString employee::getnom(){return  nom_e;}
QString employee::getprenom(){return  prenom_e;}
int employee::gettel(){return num_tel_e; }
QString employee::getmdp(){return  mdp;}
QString employee::getadr(){return  adresse_e;}
QString employee::gettype(){return  type_e;}
int employee::getprime(){return prime; }
int employee::getsalaire(){return salaire; }

void employee::setid(int id_employe){ this->id_employe=id_employe;}
void employee::setnom(QString nom_e){ this->nom_e=nom_e;}
void employee::setprenom(QString prenom_e){ this->prenom_e=prenom_e;}
void employee::settel(int num_tel_e){ this->num_tel_e=num_tel_e;}
void employee::setmdp(QString mdp){ this->mdp=mdp;}
void employee::setadr(QString adresse_e){ this->adresse_e=adresse_e;}
void employee::settype(QString type_e){ this->type_e=type_e;}
void employee::setprime(int prime){ this->prime=prime;}
void employee::setsalaire(int salaire){ this->salaire=salaire;}

bool employee::ajouter(){
  QString id_emp=QString::number(id_employe);
  QString tel=QString::number(num_tel_e);
  QString prim=QString::number(prime);
  QString sal=QString::number(salaire);
QSqlQuery query;
query.prepare("INSERT INTO EMPLOYES (id_employe,nom_e,prenom_e,num_tel_e,mdp,adresse_e,type_e,prime,salaire"
              "VALUES (:id_employe,:nom_e,:prenom_e,:num_tel_e,:mdp,:adresse_e,:type_e,:prime,:salaire)");
query.bindValue(":id_employe",id_emp);
query.bindValue(":nom_e",nom_e);
query.bindValue(":prenom_e",prenom_e);
query.bindValue(":num_tel_e",tel);
query.bindValue(":adresse_e",adresse_e);
query.bindValue(":type_e",type_e);
query.bindValue(":prime",prim);
query.bindValue(":salaire",sal);
return query.exec();
}
