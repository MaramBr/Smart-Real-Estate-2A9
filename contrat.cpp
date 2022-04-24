#include "contrat.h"
#include <QString>
#include <QSqlQuery>
#include <QDate>
#include <QObject>

#include<qiterator.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Contrat::Contrat()
{
numc="";
montant=0;
typec="";
mode_paiement="";
cin="";


}
Contrat::Contrat(QString numc, QDate date_signification , int montant , QString typec , QString mode_paiement ,QString cin)
{
    this->numc=numc;
    this->date_signification=date_signification;
    this->montant=montant;
    this->typec=typec;
    this->mode_paiement=mode_paiement;
    this->cin=cin;
}
QString Contrat::getnum(){return numc;}
QDate Contrat::getdate_s(){return date_signification;}
int Contrat::getmontant(){return montant;}
QString Contrat::gettype(){return typec;}
QString Contrat::getmode(){return mode_paiement;}
QString Contrat::getcin(){return cin;}
void Contrat::setnum(QString numc){this->numc=numc;}
void Contrat::setdate(QDate date_signification){this->date_signification=date_signification;}
void Contrat::setmontant(int montant){this->montant=montant;}
void Contrat::settype(QString typec){this->typec=typec;}
void Contrat ::setmode(QString mode_paiement){this->mode_paiement=mode_paiement;}
void Contrat::setcin(QString cin) {this->cin=cin;}
bool Contrat::ajouter()
{
    QString montant_string=QString::number(montant);

    QSqlQuery queury;
    queury.prepare("INSERT INTO CONTRATS (numc,date_signification,montant,TYPEC,mode_paiement,cin)"
                   "VALUES(:numc,:date_signification,:montant,:typec,:mode_paiement,:cin)");
    queury.bindValue(":numc",numc);
    queury.bindValue(":date_signification",date_signification);
    queury.bindValue(":montant",montant_string);
    queury.bindValue(":typec",typec);
    queury.bindValue(":mode_paiement",mode_paiement);
    queury.bindValue(":cin",cin);
    return queury.exec();

}
bool Contrat::modifier(QString numc,QDate date_signification,int montant,QString typec,QString mode_paiement,QString cin)
{
    //QString numcf=QString::number(numc);
    QString montant_string=QString::number(montant);
    QSqlQuery query;
   query.prepare("update contrats set numc=:numc,date_signification=:date_signification,montant=:montant,typec=:typec,mode_paiement=:mode_paiement,cin=:cin where numc=:numc");
   query.bindValue(":numc",numc);
   query.bindValue(":date_signification",date_signification);
   query.bindValue(":montant",montant_string);
   query.bindValue(":typec",typec);
   query.bindValue(":mode_paiement",mode_paiement);
   query.bindValue(":cin",cin);
   return query.exec();

}
bool Contrat::supprimer(QString numc)
{


    QSqlQuery query;

    query.prepare(" DELETE from contrats where numc=:numc");
    query.bindValue(":numc",numc);

    return query.exec();
}

QSqlQueryModel * Contrat::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select * from CONTRATS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("numc"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_signification"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mode_paiement"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("cin"));
return model;
}
QSqlQueryModel * Contrat::triercroissant()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select * from CONTRATS order by montant asc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("numc"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_signification"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mode_paiement"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("cin"));
return model;
}
QSqlQueryModel * Contrat::trierdecroissant()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select * from CONTRATS order by montant desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("numc"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_signification"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mode_paiement"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("cin"));
return model;
}
QSqlQueryModel * Contrat::recherche(QString numc)
{
    QSqlQueryModel * model= new QSqlQueryModel();
     QString res= numc;
     model->setQuery("select * from contrats where numc='"+res+"'");

    return model;
}



void Contrat::stat(QCustomPlot *customPlot)
{
    QSqlQuery query,query1;
    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(156, 212, 114));
    gradient.setColorAt(0.38, QColor(191, 234, 170));
    gradient.setColorAt(1, QColor(212, 236, 201));
    customPlot->clearPlottables();
    customPlot->clearGraphs();
    customPlot->replot();

    customPlot->setBackground(QBrush(gradient));


    QCPBars *fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    fossil->setAntialiased(false);

    fossil->setStackingGap(1);
    // set names and colors:
    fossil->setName("statistique selon le type");
    fossil->setPen(QPen(QColor(125,198, 209).lighter(170)));
    fossil->setBrush(QColor(125,198, 209));

    QVector<double> ticks;
    QVector<QString> labels;
    query.prepare("SELECT COUNT(DISTINCT numc) FROM contrats where typec='location'");
    query.exec();
    int un;
    while(query.next())
    {
        un=query.value(0).toInt();
        qDebug()<<un;
    }

    query.prepare("SELECT COUNT(DISTINCT numc) FROM contrats where typec='vendre'");
    query.exec();
    int deux;
    while(query.next())
    {
        deux=query.value(0).toInt();
    }
/*
    query.prepare("SELECT COUNT(DISTINCT numc) FROM contrats where MONTANT between 10000 and 100000");
    query.exec();
    int trois;
    while(query.next())
    {
        trois=query.value(0).toInt();
    }

*/



    ticks << 1 << 2  ;
    labels << "location" << "vendre"  ;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setTickLabelRotation(60);
    customPlot->xAxis->setSubTicks(false);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setRange(0, 8);
    customPlot->xAxis->setBasePen(QPen(Qt::black));
    customPlot->xAxis->setTickPen(QPen(Qt::white));
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->xAxis->setTickLabelColor(Qt::black);
    customPlot->xAxis->setLabelColor(Qt::green);

    // prepare y axis:
    customPlot->yAxis->setRange(0, 20);
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Nombre de contrats");
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
    fossilData  << un <<deux  ;
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

double Contrat::calucul()
{

        QSqlQuery query;
        query.prepare("SELECT montant FROM contrats");

        double somme=0;
        if(query.exec())
        {
            while(query.next())
            {
                double montant = query.value(0).toString().toInt();//Récupère le résultat de la requête
                 somme=somme+montant;

            }
        }
        return somme;
}

