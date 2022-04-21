#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "immeuble.h"
#include <QMessageBox>

#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    int id_immeuble = ui->lineEdit_IDi->text().toInt();
    QString adresse = ui->lineEdit_Adresse->text();
    QString description = ui->lineEdit_Description->text();
    int nb_etage = ui->lineEdit_Nbetage->text().toInt();

    immeuble I(id_immeuble, nb_etage, adresse, description);
    bool test = I.ajouter();

    if (test){
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Ajout effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Ajouter non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void MainWindow::on_Supprimer_clicked()
{
    int id_immeuble = ui->lineEdit_idS->text().toInt();

    bool test = Etmp.supprimer(id_immeuble);

    if (test){
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Suppression effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Suppression non effectué"),
                              QMessageBox::Cancel
                              );
    }
}


void MainWindow::on_Modifier_clicked()
{
    int id_immeuble = ui->lineEdit_idm->text().toInt();
    QString adresse = ui->lineEdit_adressem->text();
    QString description = ui->lineEdit_descriptionm->text();
    int nb_etage = ui->lineEdit_nbetagem->text().toInt();


    immeuble I(id_immeuble, nb_etage, adresse, description);
    bool test = I.modifier(id_immeuble);
    if (test){
        ui->tableView->setModel(I.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("modification effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("modification non effectué"),
                              QMessageBox::Cancel
                              );
    }
}




void MainWindow::on_tri_id_clicked()
{
    immeuble I;
    ui->tableView->setModel(I.trier());
}

void MainWindow::on_rechercher_clicked()
{
    immeuble I;
    QString rech_field = ui->lineEdit_adresse_recherche->text();
    ui->tableView->setModel(I.chercher(rech_field));
}

void MainWindow::on_sombre_clicked()
{
    QFile styleSheetFile("C:/Users/meyzi/Documents/immeuble/Diffnes.qss");
            styleSheetFile.open(QFile::ReadOnly);
            QString styleSheet = QLatin1String (styleSheetFile.readAll());
            MainWindow::setStyleSheet(styleSheet);
}

void MainWindow::on_blanc_clicked()
{
    QFile styleSheetFile("C:/Users/meyzi/Documents/immeuble/Integrid.qss");
            styleSheetFile.open(QFile::ReadOnly);
            QString styleSheet = QLatin1String (styleSheetFile.readAll());
            MainWindow::setStyleSheet(styleSheet);

}

void MainWindow::on_pushButton_clicked()
{
    //ui->stackedWidget_2->setCurrentIndex(1);
                QSqlQueryModel * model= new QSqlQueryModel();
                model->setQuery("select * from IMMEUBLES where NB_ETAGES < 3 ");
                float taille=model->rowCount();
                model->setQuery("select * from IMMEUBLES where NB_ETAGES  between 3 and 5 ");
                float taillee=model->rowCount();
                model->setQuery("select * from IMMEUBLES where NB_ETAGES >6");
                float tailleee=model->rowCount();
                float total=taille+taillee+tailleee;
                QString a=QString("nombre etages  inf a 3 . "+QString::number((taille*100)/total,'f',2)+"%" );
                QString b=QString("nombre etages entre 3 et 5 .  "+QString::number((taillee*100)/total,'f',2)+"%" );
                QString c=QString("nombre etages sup a 6 . "+QString::number((tailleee*100)/total,'f',2)+"%" );
                QPieSeries *series = new QPieSeries();
                series->append(a,taille);
                series->append(b,taillee);
                series->append(c,tailleee);
                if (taille!=0)
                {QPieSlice *slice = series->slices().at(0);
                    slice->setLabelVisible();
                    slice->setPen(QPen());}
                if ( taillee!=0)
                {
                    // Add label, explode and define brush for 2nd slice
                    QPieSlice *slice1 = series->slices().at(1);
                    //slice1->setExploded();
                    slice1->setLabelVisible();
                }
                if(tailleee!=0)
                {
                    // Add labels to rest of slices
                    QPieSlice *slice2 = series->slices().at(2);
                    //slice1->setExploded();
                    slice2->setLabelVisible();
                }


                // Create the chart widget
                QChart *chart = new QChart();
                // Add data to chart with title and hide legend
                chart->addSeries(series);
                chart->setTitle("distribution immeuble :Nombre Des immeubles "+ QString::number(total));
                chart->legend()->hide();
                // Used to display the chart
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->resize(1000,500);
                chartView->show();
    }

