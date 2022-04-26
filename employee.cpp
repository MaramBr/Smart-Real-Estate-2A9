#include "employee.h"
#include<QString>
#include<QSqlQuery>
#include<QObject>
#include <QSqlQueryModel>

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

bool employee::ajouter()
{
    QSqlQuery query;
  QString res=QString::number(id_employe);
  QString tel=QString::number(num_tel_e);
  QString prim=QString::number(prime);
  QString sal=QString::number(salaire);

query.prepare("insert into employes (id_employe,nom_e,prenom_e,num_tel_e,mdp,adresse_e,type_e,prime,salaire)"
              "VALUES (:id_employe,:nom_e,:prenom_e,:num_tel_e,:mdp,:adresse_e,:type_e,:prime,:salaire)");
query.bindValue(":id_employe",res);
query.bindValue(":nom_e",nom_e);
query.bindValue(":prenom_e",prenom_e);
query.bindValue(":num_tel_e",num_tel_e);
query.bindValue(":mdp",mdp);
query.bindValue(":adresse_e",adresse_e);
query.bindValue(":type_e",type_e);
query.bindValue(":prime",prime);
query.bindValue(":salaire",salaire);
return query.exec();
}

bool employee ::modifier (int id_employe,QString nom_e,QString prenom_e,int num_tel_e,QString mdp,QString adresse_e,QString type_e,int prime,int salaire)
        {
QString res=QString::number(id_employe);
QString tel=QString::number(num_tel_e);
QString prim=QString::number(prime);
QString sal=QString::number(salaire);
QSqlQuery query;
query.prepare("update employes set id_employe=:id_employe,nom_e=:nom_e,prenom_e=:prenom_e,num_tel_e=:num_tel_e,mdp=:mdp,adresse_e=:adresse_e,type_e=:type_e,prime=:prime,salaire=:salaire where id_employe=:id_employe");
query.bindValue(":id_employe",res);
query.bindValue(":nom_e",nom_e);
query.bindValue(":prenom_e",prenom_e);
query.bindValue(":num_tel_e",tel);
query.bindValue(":mdp",mdp);
query.bindValue(":adresse_e",adresse_e);
query.bindValue(":type_e",type_e);
query.bindValue(":prime",prim);
query.bindValue(":salaire",sal);
return query.exec();
}

bool employee::supprimer(int id_employe )
{
QSqlQuery query;
query.prepare(" DELETE from employes where id_employe=:id_employe");
            query.bindValue(":id_employe",id_employe);

            return query.exec();
}


QSqlQueryModel * employee::afficher()
        {
            QSqlQueryModel* model =new QSqlQueryModel();
            model->setQuery("select * from EMPLOYES");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_employe"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_e"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom_e"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("num_tel_e"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("mdp"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse_e"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("type_e"));
            model->setHeaderData(7, Qt::Horizontal, QObject::tr("prime"));
             model->setHeaderData(8, Qt::Horizontal, QObject::tr("salaire"));


        return model;
        }


          QSqlQueryModel * employee ::triercroissant()
        {

            QSqlQueryModel* model =new QSqlQueryModel();
            model->setQuery("select * from EMPLOYES order by salaire asc");

            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_employe"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_e"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom_e"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("num_tel_e"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("mdp"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse_e"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("type_e"));
            model->setHeaderData(7, Qt::Horizontal, QObject::tr("prime"));
             model->setHeaderData(8, Qt::Horizontal, QObject::tr("salaire"));



        return model;
        }

          QSqlQueryModel * employee::trierdecroissant()
                  {

                      QSqlQueryModel* model =new QSqlQueryModel();
                      model->setQuery("select * from EMPLOYES order by salaire desc");

                      model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_employe"));
                      model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_e"));
                     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom_e"));
                     model->setHeaderData(3, Qt::Horizontal, QObject::tr("num_tel_e"));
                      model->setHeaderData(4, Qt::Horizontal, QObject::tr("mdp"));
                      model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse_e"));
                      model->setHeaderData(6, Qt::Horizontal, QObject::tr("type_e"));
                      model->setHeaderData(7, Qt::Horizontal, QObject::tr("prime"));
                       model->setHeaderData(8, Qt::Horizontal, QObject::tr("salaire"));

                  return model;
                  }

          QSqlQueryModel * employee::rechercher(QString adresse_e)
          {
              QSqlQueryModel * model= new QSqlQueryModel();
               QString res= adresse_e;
               model->setQuery("select * from EMPLOYES where adresse_e='"+res+"'");

              return model;
          }


          void employee::stat(QCustomPlot *customPlot)
          {
              QSqlQuery query,query1;
              // set dark background gradient:
              QLinearGradient gradient(0, 0, 0, 400);
              gradient.setColorAt(0, QColor(41, 171, 145));
              gradient.setColorAt(0.38, QColor(22, 230, 208));
              gradient.setColorAt(1, QColor(255, 255, 255));
              customPlot->clearPlottables();
              customPlot->clearGraphs();
              customPlot->replot();

              customPlot->setBackground(QBrush(gradient));


              QCPBars *fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);

              fossil->setAntialiased(false);

              fossil->setStackingGap(1);
              // set names and colors:
              fossil->setName("statistique selon le type ");
              fossil->setPen(QPen(QColor(26, 188, 156).lighter(170)));
              fossil->setBrush(QColor(26, 188, 156));

              QVector<double> ticks;
              QVector<QString> labels;
              query.prepare("SELECT COUNT(DISTINCT id_employe) FROM employes where type_e = 'commercial'");
              query.exec();
              int un;
              while(query.next())
              {
                  un=query.value(0).toInt();
                  qDebug()<<un;
              }

              query.prepare("SELECT COUNT(DISTINCT id_employe) FROM employes where type_e = 'financier'");
              query.exec();
              int deux;
              while(query.next())
              {
                  deux=query.value(0).toInt();
              }

              query.prepare("SELECT COUNT(DISTINCT id_employe) FROM employes where type_e = 'hr'");
              query.exec();
              int trois;
              while(query.next())
              {
                  trois=query.value(0).toInt();
              }





              ticks << 1 << 2 << 3 ;  //vecteur
              labels << "commercial" << "financier" << "hr" ;
              QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
              textTicker->addTicks(ticks, labels);
              customPlot->xAxis->setTicker(textTicker);
              customPlot->xAxis->setTickLabelRotation(60);
              customPlot->xAxis->setSubTicks(false);
              customPlot->xAxis->setTickLength(0, 4);
              customPlot->xAxis->setRange(0, 8);
              customPlot->xAxis->setBasePen(QPen(Qt::black));
              customPlot->xAxis->setTickPen(QPen(Qt::black));
              customPlot->xAxis->grid()->setVisible(true);
              customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
              customPlot->xAxis->setTickLabelColor(Qt::black);
              customPlot->xAxis->setLabelColor(Qt::green);

              // prepare y axis:
              customPlot->yAxis->setRange(0, 20);
              customPlot->yAxis->setPadding(5); // a bit more space to the left border
              customPlot->yAxis->setLabel("Nombre des employes");
              customPlot->yAxis->setBasePen(QPen(Qt::black));
              customPlot->yAxis->setTickPen(QPen(Qt::black));
              customPlot->yAxis->setSubTickPen(QPen(Qt::black));
              customPlot->yAxis->grid()->setSubGridVisible(true);
              customPlot->yAxis->setTickLabelColor(Qt::black);
              customPlot->yAxis->setLabelColor(Qt::black);
              customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
              customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

              // Add data:
              QVector<double> fossilData, nuclearData, regenData;
              fossilData  << un <<deux <<trois ;
             // nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
              regenData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
              fossil->setData(ticks, fossilData);
            //  nuclear->setData(ticks, nuclearData);
           //   regen->setData(ticks, regenData);

              // setup legend:
              customPlot->legend->setVisible(true);
              customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
              customPlot->legend->setBrush(QColor(255, 255, 255, 100));
              customPlot->legend->setBorderPen(Qt::NoPen);
              QFont legendFont = QFont();
              legendFont.setPointSize(10);
              customPlot->legend->setFont(legendFont);
              customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

          }



