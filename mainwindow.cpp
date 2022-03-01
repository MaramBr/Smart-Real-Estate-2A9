#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_ajout.h"
#include "dialog_modification.h"
#include "clients.h"
#include "connexion.h"
#include <QMessageBox>
#include <QApplication>
#include <QString>
#include <QSqlQueryModel>
#include <QDate>
#include <QIntValidator>
#include <QTableView>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_clients->setModel(c.afficher());
    ui->le_cin->setValidator( new QIntValidator(0,99999999, this));
    ui->le_num->setValidator( new QIntValidator(0,99999999, this));
    ui->tab_clients->setModel(c.afficher());
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Dialog_ajout d_ajout;
    d_ajout.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    Dialog_modification d_modification;
    d_modification.exec();
}

void MainWindow::on_ajouter_clicked()
{
    ui->tab_clients->setModel(c.afficher());
    int CIN= ui->le_cin->text().toInt();
    QString nom= ui->le_nom->text();
    QString prenom= ui->le_prenom->text();
    int num_tel =ui->le_num->text().toInt();
    QString type =ui->le_type->text();
    QDate date_ajout =ui->le_date->date();
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

        c1.setcin(ui->cin_sup->text().toInt());
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
