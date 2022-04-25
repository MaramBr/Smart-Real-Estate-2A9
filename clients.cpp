#include "clients.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include <QObject>
#include <QString>
#include <QSqlRecord>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <string>

using namespace std;

Clients::Clients()
{
CIN="";
nom="";
prenom="";
num_tel="";
type="";
}

Clients::Clients(QString CIN,QString nom,QString prenom,QString num_tel,QString type,QDate date_ajout)
{
 this->CIN=CIN;
 this->nom=nom;
 this->prenom=prenom;
 this->num_tel=num_tel;
 this->type=type;
 this->date_ajout=date_ajout;
}
QString Clients:: getcin()
{
    return CIN;
}
QString Clients:: getnom()
{
    return nom;
}
QString Clients:: getprenom()
{
    return prenom;
}
QString Clients:: getnum()
{
    return num_tel;
}
QString Clients:: gettype()
{
    return type;
}
QDate Clients:: getdate()
{
    return date_ajout;
}
void Clients:: setcin(QString CIN)
{
     this->CIN=CIN;
}
void Clients:: setnom(QString nom)
{
     this->nom=nom;
}
void Clients:: setprenom(QString prenom)
{
     this->prenom=prenom;
}
void Clients:: setnum(QString num_tel)
{
     this->num_tel=num_tel;
}
void Clients:: settype(QString type)
{
     this->type=type;
}
void Clients:: setdate(QDate date_ajout)
{
     this->date_ajout=date_ajout;
}
bool Clients:: ajouter()
{

        QSqlQuery query;

        query.prepare("INSERT INTO CLIENTS (CIN,nom,prenom,num_tel,type,date_ajout) "
                      "VALUES (:CIN,:nom,:prenom,:num_tel,:type,:date_ajout)");

        query.bindValue(":CIN",CIN);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":num_tel",num_tel);
        query.bindValue(":type",type);
        query.bindValue(":date_ajout",date_ajout);

        return query.exec();
}
bool Clients::modifier(QString CIN, QString nom, QString prenom, QString num_tel, QString type)
{

    QSqlQuery query;
       query.prepare("update clients set CIN=:CIN,nom=:nom,prenom=:prenom,num_tel=:num_tel,type=:type where CIN=:CIN");

       query.bindValue(":CIN",CIN);
       query.bindValue(":nom",nom);
       query.bindValue(":prenom",prenom);
       query.bindValue(":num_tel",num_tel);
       query.bindValue(":type",type);
     //  query.bindValue(":date_ajout",date_ajout);

       return query.exec();

}
bool Clients::supprimer(QString CIN)
{
    QSqlQuery query;

    query.prepare(" DELETE from clients where CIN=:CIN");
    query.bindValue(":CIN",CIN);

    return query.exec();
}

QSqlQueryModel*Clients::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select * from clients");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("num_tel"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_ajout"));
return model;
}
QSqlQueryModel*Clients::triercroissant()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select * from clients order by nom asc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("num_tel"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_ajout"));
return model;
}
QSqlQueryModel*Clients::trierdecroissant()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select * from clients order by nom desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("num_tel"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_ajout"));
return model;
}
QSqlQueryModel*Clients::recherche(QString CIN)
{
    QString rech=CIN;
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("select * from clients where CIN ='"+rech+"'");

return model;
}
bool Clients::excel()
{
    QSqlQuery q("select * from clients");
      QSqlRecord rec = q.record();

      QFile fichier("C:/excel/Clients.csv");

      if(fichier.open(QIODevice::WriteOnly | QIODevice::Text))
      {
          QTextStream stream(&fichier);

      int cinCol = rec.indexOf("CIN");
      int nomCol = rec.indexOf("nom");
      int prenomCol = rec.indexOf("prenom");
      int numCol = rec.indexOf("num_tel");
      int typecol = rec.indexOf("type");
      int datecol = rec.indexOf("date_ajout");

        //std::cout << "cinCol " << cinCol << std::endl;
        //std::cout << "nomCol " << nomCol << std::endl;

      stream << "CIN" << ";" << "nom" << ";" << "prenom" << ";" << "num_tel" << ";" << "type"<< ";" << "date_ajout" <<  "\n";

      while (q.next())
          stream  << q.value(cinCol).toString() << ";" << q.value(nomCol).toString() << ";" << q.value(prenomCol).toString() << ";"
                  << q.value(numCol).toString()<< ";" <<  q.value(typecol).toString()<< ";" <<  q.value(datecol).toString().left(10) << "\n";

        }
      fichier.close();
      return q.exec();
}

void Clients::stat(QCustomPlot *customPlot)
{
    QSqlQuery query;
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
    fossil->setName("statistique selon le type de clients");
    fossil->setPen(QPen(QColor(26, 188, 156).lighter(170)));
    fossil->setBrush(QColor(26, 188, 156));

    QVector<double> ticks;
    QVector<QString> labels;
    query.prepare("SELECT COUNT(DISTINCT CIN) FROM clients where type='locataire' ");
    query.exec();
    int un;
    while(query.next())
    {
        un=query.value(0).toInt();
        qDebug()<<un;
    }

    query.prepare("SELECT COUNT(DISTINCT CIN) FROM clients where type='propreataire'");
    query.exec();
    int deux;
    while(query.next())
    {
        deux=query.value(0).toInt();
    }

    ticks << 1 << 2 ;
    labels << "Locataires" << "Propreataires"  ;
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
    customPlot->yAxis->setPadding(5);
    customPlot->yAxis->setLabel("Nombre de Clients");
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
    regenData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
    fossil->setData(ticks, fossilData);
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
 void Clients::save_historique(QString selected_date)
 {

     QSqlQuery q("select * from clients order by date_ajout");
       QSqlRecord rec = q.record();

        QFile fichier("C:/historique/histo.txt");

       if(fichier.open(QIODevice::WriteOnly | QIODevice::Text))
       {
           QTextStream stream(&fichier);

       int cinCol = rec.indexOf("CIN");
       int nomCol = rec.indexOf("nom");
       int prenomCol = rec.indexOf("prenom");
       int numCol = rec.indexOf("num_tel");
       int typecol = rec.indexOf("type");
       int datecol = rec.indexOf("date_ajout");

         //std::cout << "cinCol " << cinCol << std::endl;
         //std::cout << "nomCol " << nomCol << std::endl;

      // stream << "CIN" << ";" << "nom" << ";" << "prenom" << ";" << "num_tel" << ";" << "type"<< ";" << "date_ajout" <<  "\n";
           QDate date_pred;
           bool first = true;
           QDate selected_qdate(selected_date.right(4).toInt(),selected_date.mid(3,2).toInt(),selected_date.left(2).toInt());
              //  cout <<" hgv "<<selected_date.toStdString()<<endl;
                //     cout <<" hgv "<<selected_qdate.toString().toStdString()<<endl;
           while (q.next()) {
               QString date=q.value(datecol).toString().left(10);
               QDate date_ajout(date.left(4).toInt(),date.mid(5,2).toInt(),date.right(2).toInt());
               if (selected_qdate>=date_ajout){
                   if ((first) || (date_pred!=date_ajout)) {
                       if(!first) stream << endl;
                       stream << "-----------------------------------" << endl;
                       stream << date_ajout.toString("dd/MM/yyyy") << endl;
                       stream << "-----------------------------------" << endl;
                       if (first) first=false;
                       date_pred=date_ajout;
                   }
                   stream << "    CIN: " << q.value(cinCol).toString() << endl;
                   stream << "    Nom: " << q.value(nomCol).toString() << endl;
                   stream << "    Prenom: " << q.value(prenomCol).toString() << endl;
                   stream << "    Num_Tel: " << q.value(numCol).toString()<< endl;
                   stream << "    Type: " << q.value(typecol).toString()<< endl;

                  // cout<<" year "<<date.left(4).toStdString()<<" month "<<date.mid(5,2).toStdString()<<" day "<< date.right(2).toStdString()<<endl;
                   //stream << "Date: " << date_ajout.toString("dd/MM/yyyy") << endl;
                  // stream << "Date: " << q.value(datecol).toString() << endl;
                   stream << endl;
              }
           }
        fichier.close();

         } else {
           qDebug()<<"erreur";
         }
 }

