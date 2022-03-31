#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rdv.h"
#include <QMessageBox>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Et.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int NUM_RDV = ui->lineEdit_num->text().toInt();
    QDate DATE_RDV = ui->dateEdit->date();
    QString type;
if (ui->radioButton->isChecked())
{ type="location" ; }
if (ui->radioButton_vente->isChecked())
{ type="vente" ; }


    rdv R (NUM_RDV, DATE_RDV,type);
    bool test = R.ajouter();

    if (test){
        ui->tableView->setModel(Et.afficher());
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

void MainWindow::on_pushButton_Supprimer_clicked()
{
    int num_rdv = ui->lineEdit_ID_4->text().toInt();
    bool test = Et.supprimer(num_rdv);

    if (test){
        ui->tableView->setModel(Et.afficher());
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


void MainWindow::on_pushButton_2_clicked()
{
    // modifier
    int NUM_RDV = ui->lineEdit_num->text().toInt();
    QDate DATE_RDV = ui->dateEdit->date();
    QString type;
if (ui->radioButton->isChecked())
{ type="location" ; }
if (ui->radioButton_vente->isChecked())
{ type="vente" ; }
    rdv R2(NUM_RDV, DATE_RDV,type);
    bool test = R2.modifier();
    if (test){
        ui->tableView->setModel(Et.afficher());
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
