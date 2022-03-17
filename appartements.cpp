#include "appartements.h"
#include <QSqlQueryModel>
#include<QString>

Appartements::Appartements()
{
    id_appartement="";
    prix=0;
    nb_chambres=0;
    description_A="";
    id_immeuble=0;

}
Appartements::Appartements(QString id_appartement,int prix,int nb_chambres,QString description_A,int id_immeuble)
{
      this->id_appartement=id_appartement;
      this->prix=prix;
      this->nb_chambres=nb_chambres;
      this->description_A=description_A;
      this->id_immeuble=id_immeuble;
}
 QString Appartements:: getid_appartement()
{
    return id_appartement;
}
QString Appartements:: getdescription_A()
{
    return description_A;
}
int Appartements :: getnb_chambres()
{
  return nb_chambres;
}
 int Appartements :: getprix()
 {
     return prix;
 }
 int Appartements:: getid_immeuble()
 {
     return id_immeuble;
 }
   void Appartements :: setid_appartement( QString id_appartement)
   {
      this->id_appartement=id_appartement;
   }

    void Appartements :: setdescription_A(QString description_A)
    {
        this->description_A=description_A;
    }
      void Appartements :: setnb_chambres(int nb_chambres)
      {
          this->nb_chambres=nb_chambres;
      }
       void Appartements ::  setprix(int prix)
       {
           this->prix=prix;
       }
       void Appartements :: setid_immeuble(int id_immeuble)
       {
          this->id_immeuble=id_immeuble;
       }

        bool Appartements :: ajouter()
        {

            QString prix_string=QString::number(prix);
            QString nb_chambres_string=QString::number(nb_chambres);

            QString id_immeuble_string=QString::number(id_immeuble);
                QSqlQuery query;

                query.prepare("INSERT INTO APPARTEMENTS (id_appartement,prix,nb_chambres,description_A,id_immeuble) "
                              "VALUES (:id_appartement,:prix,:nb_chambres,:description_A,:id_immeuble)");
                query.bindValue(":id_appartement",id_appartement);
                query.bindValue(":prix",prix_string);
                query.bindValue(":nb_chambres",nb_chambres_string);

                query.bindValue(":description_A",description_A);
                query.bindValue(":id_immeuble",id_immeuble_string);



                return query.exec();

        }
        bool Appartements ::modifier ( QString id_appartement, int prix, int nb_chambres, QString description_A, int id_immeuble)
        {

            QString prix_string=QString::number(prix);
            QString nb_chambres_string=QString::number(nb_chambres);

            QString id_immeuble_string=QString::number(id_immeuble);
                QSqlQuery query;



               query.prepare("update appartements set id_appartement=:id_appartement,prix=:prix,nb_chambres=:nb_chambres,description_A=:description_A,id_immeuble=:id_immeuble where id_appartement=:id_appartement");
               query.bindValue(":id_appartement",id_appartement);
               query.bindValue(":prix",prix_string);
               query.bindValue(":nb_chambres",nb_chambres_string);

               query.bindValue(":description_A",description_A);
               query.bindValue(":id_immeuble",id_immeuble_string);

               return query.exec();
        }
        bool Appartements::supprimer( QString id_appartement)
        {


            QSqlQuery query;

            query.prepare(" DELETE from appartements where id_appartement=:id_appartement");
            query.bindValue(":id_appartement",id_appartement);

            return query.exec();
        }

        QSqlQueryModel * Appartements::afficher()
        {

            QSqlQueryModel* model =new QSqlQueryModel();
            model->setQuery("select * from APPARTEMENTS");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_appartement"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("nb_chambres"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("description_A"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_immeuble"));


        return model;
        }

        QSqlQueryModel * Appartements::triercroissant()
        {

            QSqlQueryModel* model =new QSqlQueryModel();
            model->setQuery("select * from APPARTEMENTS order by prix asc");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_appartement"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("nb_chambres"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("description_A"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_immeuble"));


        return model;
        }
        QSqlQueryModel * Appartements::trierdecroissant()
        {

            QSqlQueryModel* model =new QSqlQueryModel();
            model->setQuery("select * from APPARTEMENTS order by prix desc");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_appartement"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("nb_chambres"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("description_A"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_immeuble"));


        return model;
        }
       QSqlQueryModel * Appartements::rechercher(QString id_appartement)
         {

           QSqlQueryModel * model= new QSqlQueryModel();
            QString res= id_appartement;
            model->setQuery("select * from Appartements where id_appartement='"+res+"'");

           return model;
         }


