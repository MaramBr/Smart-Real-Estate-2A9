#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contrat.h"
#include "connexion.h"
#include <QString>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QApplication>
#include <QDate>
#include <QIntValidator>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
ui->tab_contrat->setModel(c.afficher());
ui->le_num->setValidator( new QIntValidator(0, 99999, this));
ui->le_montant->setValidator( new QIntValidator(0,999999, this));
ui->le_cin->setValidator( new QIntValidator(0,99999999, this));
ui->tab_contrat->setModel(c.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ajout_clicked()
{

    int numc= ui->le_num->text().toInt();
    QDate date_signification =ui->le_date->date();
    int montant =ui->le_montant->text().toInt();
    QString typec =ui->le_type->currentText();
    QString mode_paiement =ui->le_mode->text();
    int cin =ui->le_cin->text().toInt();
    Contrat C(numc,date_signification,montant,typec,mode_paiement,cin);
   bool test=C.ajouter();
if (test)
{
    ui->tab_contrat->setModel(c.afficher());

    QMessageBox::information(nullptr, QObject::tr(" ok"),
                             QObject::tr("ajout effecte  .\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);

   }
   else
   {

    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr("ajout non effecte .\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
   }
}





void MainWindow::on_supprimer_clicked()
{

    Contrat C1;

    C1.setnum(ui->le_num_supp->text().toInt());
    bool test =C1.supprimer(C1.getnum());
    QMessageBox msgBox;
    if(test)
    {
        ui->tab_contrat->setModel(C1.afficher());

        msgBox.setText("suppression aves succes.");
    }
    else
        msgBox.setText("echec de suppression");
    msgBox.exec();

}

void MainWindow::on_modifier_clicked()
{
 Contrat c2;

    c2.setnum(ui->le_num->text().toInt());
    c2.setdate(  ui->le_date->date());
    c2.setmontant(ui->le_montant->text().toInt());
    c2.settype(ui->le_type->currentText());
    c2.setmode(ui->le_mode->text());
    c2.setcin(ui->le_cin->text().toInt());
   bool test=c2.modifier(c2.getnum(),c2.getdate_s(),c2.getmontant(),c2.gettype(),c2.getmode(),c2.getcin());
if (test)
{
    ui->tab_contrat->setModel(c2.afficher());

    QMessageBox::information(nullptr, QObject::tr(" ok"),
                             QObject::tr("modif effecte  .\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);

   }
   else
   {

    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr("modif non effecte .\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
   }
}


void MainWindow::on_quitter_clicked()
{
    close();
}
