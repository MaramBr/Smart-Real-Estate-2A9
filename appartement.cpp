#include "appartement.h"
#include <QSqlQueryModel>
#include<QString>
#include <QPdfWriter>
#include <QPainter>
#include "mainwindow.h"
#include "ui_mainwindow.h"


Appartements::Appartements()
{
    id_appartement="";
    prix=0;
    nb_chambres=0;
    description_A="";
    id_immeuble=0;
    image="";


}
Appartements::Appartements(QString id_appartement,int prix,int nb_chambres,QString description_A,int id_immeuble,QString image)
{
      this->id_appartement=id_appartement;
      this->prix=prix;
      this->nb_chambres=nb_chambres;
      this->description_A=description_A;
      this->id_immeuble=id_immeuble;
      this->image=image;

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
            QFile file1(image);
            if(!file1.open(QIODevice::ReadOnly))
                qDebug()<<image+"url" ;
            QByteArray intByteArray=file1.readAll();
                QSqlQuery query;

                query.prepare("INSERT INTO APPARTEMENTS (id_appartement,prix,nb_chambres,description_A,id_immeuble,image) "
                              "VALUES (:id_appartement,:prix,:nb_chambres,:description_A,:id_immeuble,:image)");
                query.bindValue(":id_appartement",id_appartement);
                query.bindValue(":prix",prix_string);
                query.bindValue(":nb_chambres",nb_chambres_string);

                query.bindValue(":description_A",description_A);
                query.bindValue(":id_immeuble",id_immeuble_string);
                query.bindValue(":image",intByteArray);




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
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("image"));







        return model;
        }

        QSqlQueryModel * Appartements::triercroissant()
        {

            QSqlQueryModel* model =new QSqlQueryModel();  //??
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
      bool Appartements :: pdf()
      {

          QPdfWriter pdf("C:/pdf/a.pdf");
          QPainter painter(&pdf);
          int i = 4000;
                painter.setPen(Qt::red);
                painter.setFont(QFont("Time New Roman", 25));
                painter.drawText(3000,1400,"Liste Des appartements");
                painter.setPen(Qt::black);
              //  painter.setFont(QFont("Time New Roman", 25));
                painter.drawRect(100,100,9400,2500); // dimension rectangle liste des appartements
                painter.drawRect(100,3000,9400,500);
                painter.setFont(QFont("Time New Roman", 9));
                painter.drawText(400,3300,"id_appartement");
                painter.drawText(1550,3300,"prix");
                painter.drawText(2200,3300,"nb_chambres");
                painter.drawText(3400,3300,"description_A");
                painter.drawText(4400,3300,"id_immeuble");
                painter.drawRect(100,3000,9400,9000);

                QSqlQuery query;
                query.prepare("select * from Appartements");
                query.exec();
                while (query.next())
                {
                    painter.drawText(400,i,query.value(0).toString());
                    painter.drawText(1550,i,query.value(1).toString());
                    painter.drawText(2300,i,query.value(2).toString());
                    painter.drawText(3400,i,query.value(3).toString());
                    painter.drawText(4400,i,query.value(4).toString());
                   i = i + 350;
                }
                 return query.exec();

      }
      void Appartements::stat(QCustomPlot *customPlot)
      {
          QSqlQuery query,query1;
          // set dark background gradient:
          QLinearGradient gradient(0, 0, 0, 400);  //degradation couleurs
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
          fossil->setName("statistique selon le prix");
          fossil->setPen(QPen(QColor(26, 188, 156).lighter(170)));
          fossil->setBrush(QColor(26, 188, 156));

          QVector<double> ticks;
          QVector<QString> labels;
          query.prepare("SELECT COUNT(DISTINCT id_appartement) FROM Appartements where prix between 100 and 1000");
          query.exec();
          int un;
          while(query.next())
          {
              un=query.value(0).toInt();
              qDebug()<<un;
          }

          query.prepare("SELECT COUNT(DISTINCT id_appartement) FROM Appartements where prix between 1000 and 10000");
          query.exec();
          int deux;
          while(query.next())
          {
              deux=query.value(0).toInt();
          }

          query.prepare("SELECT COUNT(DISTINCT id_appartement) FROM Appartements where prix between 10000 and 100000");
          query.exec();
          int trois;
          while(query.next())
          {
              trois=query.value(0).toInt();
          }





          ticks << 1 << 2 << 3 ;
          labels << "[100,1000]" << "[1001,10000]" << "[10001,100000]" ;
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
          customPlot->yAxis->setLabel("Nombre des appartements");
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





