#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clients.h"
#include "connexion.h"
#include <QMessageBox>
#include <QApplication>
#include <QString>
#include <QSqlQueryModel>
#include <QDate>
#include <QTableView>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QSqlQuery>
#include <QDesktopServices>
#include <QUrl>
#include <qcustomplot.h>
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_clients->setModel(c.afficher());
    ui->le_cin->setValidator( new QRegExpValidator (QRegExp("[0-9]{1,8}")));
    ui->le_nom->setValidator( new QRegExpValidator (QRegExp("[a-z]{1,10}")));
    ui->le_prenom->setValidator( new QRegExpValidator (QRegExp("[a-z]{1,10}")));
    ui->le_num->setValidator( new QRegExpValidator (QRegExp("[0-9]{1,8}")));
    ui->le_type->setValidator( new QRegExpValidator (QRegExp("[a-z]{1,15}")));
    ui->cin_sup->setValidator( new QRegExpValidator (QRegExp("[0-9]{1,8}")));
    ui->cin_rech->setValidator( new QRegExpValidator (QRegExp("[0-9]{1,8}")));
    QString current_date=QDateTime::currentDateTime().toString("dd.MM.yyyy");
    QDate current_qdate(current_date.right(4).toInt(),current_date.mid(3,2).toInt(),current_date.left(2).toInt());
    ui->choixdate->setDate(current_qdate);

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_ajouter_clicked()
{
    QString CIN= ui->le_cin->text();
    QString nom= ui->le_nom->text();
    QString prenom= ui->le_prenom->text();
    QString num_tel =ui->le_num->text();
    QString type =ui->le_type->text();
    QString date=QDateTime::currentDateTime().toString("dd.MM.yyyy");
    QDate date_ajout(date.right(4).toInt(),date.mid(3,2).toInt(),date.left(2).toInt());
   // cout<<" year "<<date.right(4).toStdString()<<" month "<<date.mid(3,2).toStdString()<<" day "<< date.left(2).toStdString()<<endl;
    //cout<<"ytf"<<date_ajout.toString().toStdString()<<endl;
    Clients C(CIN,nom,prenom,num_tel,type,date_ajout);
    bool test=C.ajouter();
    if (test)
    {
        ui->tab_clients->setModel(C.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("ajout effectuer  .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

       }
       else
       {

        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("ajout non effectuer .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_supprimer_clicked()
{
    Clients c1;

        c1.setcin(ui->cin_sup->text());
        bool test =c1.supprimer(c1.getcin());
        QMessageBox msgBox;
        if(test)
        {
            ui->tab_clients->setModel(c1.afficher());
            msgBox.setText("supprimer avec succés.");
        }
        else
            msgBox.setText("echec de suppression");
        msgBox.exec();
}

void MainWindow::on_modifier_clicked()
{
    Clients c2;

        c2.setcin(ui->le_cin->text());
        c2.setnom(ui->le_nom->text());
        c2.setprenom(ui->le_prenom->text());
        c2.setnum(ui->le_num->text());
        c2.settype(ui->le_type->text());
      //  c2.setdate(  ui->le_date->date());

       bool test=c2.modifier(c2.getcin(),c2.getnom(),c2.getprenom(),c2.getnum(),c2.gettype());
    if (test)
    {
        ui->tab_clients->setModel(c2.afficher());

        QMessageBox::information(nullptr, QObject::tr(" ok"),
                                 QObject::tr("modif effectuer  .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

       }
       else
       {

        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("modif non effectuer .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
       }
}

void MainWindow::on_quitter_clicked()
{
    close();
}

void MainWindow::on_radioButton_5_clicked()
{
     ui->tab_clients->setModel(c2.triercroissant());
}

void MainWindow::on_radioButton_6_clicked()
{
     ui->tab_clients->setModel(c2.trierdecroissant());
}


void MainWindow::on_pushButton_13_clicked()
{
    Clients c3;
    c3.setcin(ui->cin_rech->text());
    ui->tab_clients->setModel(c3.recherche(c3.getcin()));
}

void MainWindow::on_pushButton_12_clicked()
{
    Clients c4;
    c4.excel();
    QString ExcelFileName  = "C:/excel/Clients.csv";
    QDesktopServices::openUrl(QUrl(ExcelFileName, QUrl::TolerantMode));
}
void MainWindow::on_pushButton_3_clicked()
{
    ui->tab_clients_2->setCurrentIndex(3);
       Clients c;
       c.stat(ui->widget);
}
void MainWindow::on_historique_clicked()
{
    QString date=ui->choixdate->text();
    Clients c3;
    c3.save_historique(date);
    QString lien  = "file:///C:/historique/histo.txt";
    QDesktopServices::openUrl(QUrl(lien, QUrl::TolerantMode));
}
