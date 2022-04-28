#include "rdv.h"
#include <smtp.h>


rdv::rdv()
{
        NUM_RDV=0;
        DATE_RDV="";
        TYPE_R="";
         EMAIL="";
}

rdv::rdv(int NUM_RDV, QString DATE_RDV ,QString TYPE_R,QString EMAIL){
    this->NUM_RDV=NUM_RDV;
    this->DATE_RDV=DATE_RDV;
    this->TYPE_R=TYPE_R;
     this->EMAIL=EMAIL;
}
bool rdv::ajouter(){
    QSqlQuery query;
    QString res = QString::number(NUM_RDV);
    query.prepare("insert into RDV values (:NUM_RDV, :DATE_RDV , :TYPE_R,:EMAIL)");
    query.bindValue(":NUM_RDV",res);
    query.bindValue(":DATE_RDV", DATE_RDV);
    query.bindValue(":TYPE_R",TYPE_R);
    query.bindValue(":EMAIL",EMAIL);


    return query.exec();
}
QSqlQueryModel * rdv::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from RDV");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("NUM_RDV"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("DATE_RDV"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("TYPE_R"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("EMAIL"));

    return model;
}
bool rdv::supprimer(int NUM_RDV){
    QSqlQuery query;
    QString res = QString::number(NUM_RDV);
    query.prepare("delete from RDV where NUM_RDV = :NUM_RDV");
    query.bindValue(":NUM_RDV", res);
    return query.exec();
}
bool rdv::modifier(){
    QSqlQuery query;
        QString res = QString::number(NUM_RDV);
        query.prepare("update RDV SET DATE_RDV = :DATE_RDV, TYPE_R=:TYPE_R ,EMAIL=:EMAIL where NUM_RDV = :NUM_RDV");
        query.bindValue(":NUM_RDV",res);
        query.bindValue(":DATE_RDV", DATE_RDV);
        query.bindValue(":TYPE_R",TYPE_R);
        query.bindValue(":EMAIL",EMAIL);


        return query.exec();


}


QSqlQueryModel* rdv::Rechercherdv(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM RDV WHERE NUM_RDV LIKE '"+recherche+"%'");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_RDV"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_RDV"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));

return model;
}
QSqlQueryModel * rdv::tricroi()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from RDV order by NUM_RDV "  );
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_RDV"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_RDV"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    return model;

}
QSqlQueryModel * rdv::tridecroi()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from RDV order by NUM_RDV desc "  );
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_RDV"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_RDV"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    return model;

}

QSqlQueryModel * rdv::recherche_date(QString d)
{
   // QString res=nom;
    QSqlQueryModel * model =new QSqlQueryModel();
     model->setQuery("SELECT * from RDV where DATE_RDV like '"+d+"%' ");
     model->setHeaderData(0, Qt::Horizontal,QObject:: tr("NUM_RDV"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_RDV"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE_R"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));

     return model;
}





void rdv::statrdv(QCustomPlot *customPlot)
{
    QSqlQuery query,query1;
    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(41,171, 145));
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
    fossil->setName("statistique selon le type");
    fossil->setPen(QPen(QColor(26,188, 156).lighter(170)));
    fossil->setBrush(QColor(26,188, 156));

    QVector<double> ticks;
    QVector<QString> labels;
    query.prepare("SELECT COUNT(DISTINCT NUM_RDV) FROM rdv where TYPE_R='location'");
    query.exec();
    int un;
    while(query.next())
    {
        un=query.value(0).toInt();
        qDebug()<<un;
    }

    query.prepare("SELECT COUNT(DISTINCT NUM_RDV) FROM rdv where TYPE_R='vente'");
    query.exec();
    int deux;
    while(query.next())
    {
        deux=query.value(0).toInt();
    }




    ticks << 1 << 2  ;
    labels << "location" << "vente"  ;
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
    customPlot->yAxis->setLabel("Nombre de Rendez-Vouz");
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


