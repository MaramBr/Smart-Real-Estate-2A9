#include "immeuble.h"
#include "qcustomplot.h"

#include <QtDebug>


immeuble::immeuble()
{

}
immeuble::immeuble(int id_immeuble, int nb_etages, QString adresse, QString description)
{
    this->id_immeuble=id_immeuble;
    this->nb_etages=nb_etages;
    this->adresse=adresse;
    this->description=description;
}
bool immeuble::ajouter(){
    QSqlQuery query;
    QString res = QString::number(id_immeuble);
    query.prepare("insert into IMMEUBLES values (:id_immeuble, :nb_etages, :adresse, :description)");
    query.bindValue(":id_immeuble",res);
    query.bindValue(":nb_etages", nb_etages);
    query.bindValue(":adresse", adresse);
    query.bindValue(":description", description);

    return query.exec();
}
QSqlQueryModel * immeuble::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from IMMEUBLES");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant Immeuble"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nombre Des Etages"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Description"));

    return model;
}
bool immeuble::supprimer(int id_immeuble){
    QSqlQuery query;
    QString res = QString::number(id_immeuble);
    query.prepare("delete from IMMEUBLES where id_immeuble = :id_immeuble");
    query.bindValue(":id_immeuble", res);
    return query.exec();
}
bool immeuble::modifier(int id_immeuble){
    QSqlQuery query;
    QString res = QString::number(id_immeuble);
    query.prepare("UPDATE IMMEUBLES SET nb_etages = :nb_etages ,adresse = :adresse, description = :description WHERE id_immeuble = :id_immeuble");
    query.bindValue(":id_immeuble",res);
    query.bindValue(":nb_etages", nb_etages);
    query.bindValue(":adresse", adresse);
    query.bindValue(":description", description);
    return query.exec();
}


QSqlQueryModel * immeuble::triercroissant(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from IMMEUBLES order by id_immeuble asc");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant Immeuble"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nombre Des Etages"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Description"));

    return model;
}
QSqlQueryModel * immeuble::trierdecroissant(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from IMMEUBLES order by id_immeuble desc");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant Immeuble"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nombre Des Etages"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Description"));

    return model;
}
QSqlQueryModel* immeuble::chercher(QString field){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from IMMEUBLES where (adresse) LIKE '%"+field+"%' ");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant Immeuble"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nombre Des Etages"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Description"));

    return model;
}

void immeuble::statimmeuble(QCustomPlot *customPlot)
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
    fossil->setName("statistique selon le nombre d'etages");
    fossil->setPen(QPen(QColor(26, 188, 156).lighter(170)));
    fossil->setBrush(QColor(26, 188, 156));

    QVector<double> ticks;
    QVector<QString> labels;
    query.prepare("SELECT COUNT(DISTINCT id_immeuble) FROM immeubles where nb_etages between 1 and 3 ");
    query.exec();
    int un;
    while(query.next())
    {
        un=query.value(0).toInt();
        qDebug()<<un;
    }

    query.prepare("SELECT COUNT(DISTINCT id_immeuble) FROM immeubles where nb_etages between 4 and 6");
    query.exec();
    int deux;
    while(query.next())
    {
        deux=query.value(0).toInt();
    }

    ticks << 1 << 2 ;
    labels << "[1,3]" << "[4,6]"  ;
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
    customPlot->yAxis->setLabel("Nombre des etages");
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


