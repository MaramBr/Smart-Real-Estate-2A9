#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appartements.h"
#include "connexion.h"
#include <QMessageBox>
#include<QApplication>
#include <QString>
#include <QSqlQueryModel>

#include <QIntValidator>
 #include <QTableView>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->tab_appartement->setModel(a.afficher());
    ui->le_id->setValidator( new QIntValidator(0, 99999, this));
    ui->le_nbchambres->setValidator( new QIntValidator(0,9, this));
    ui->le_prix->setValidator( new QIntValidator(0,999999, this));
    ui->le_id2->setValidator( new QIntValidator(0, 99999, this));

    ui->tab_appartement->setModel(a.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_ajouter_clicked()
{
    ui->tab_appartement->setModel(a.afficher());
       int id_appartement= ui->le_id->text().toInt();
       int prix =ui->le_prix->text().toInt();
       int nb_chambres =ui->le_nbchambres->text().toInt();
       QString description_A =ui->le_description->text();
       int id_immeuble= ui->le_id2->text().toInt();

        Appartements A(id_appartement,prix,nb_chambres,description_A,id_immeuble);
        bool test=A.ajouter();
    if (test)
    {
        ui->tab_appartement->setModel(a.afficher());
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
    Appartements a1;
    ui->tab_appartement->setModel(a1.afficher());
        a1.setid_appartement(ui->id_supp->text().toInt());
        bool test =a1.supprimer(a1.getid_appartement());
        QMessageBox msgBox;
        if(test)
            msgBox.setText("suppression aves succes.");
        else
            msgBox.setText("echec de suppression");
        msgBox.exec();

}
