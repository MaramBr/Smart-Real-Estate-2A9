#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include "QSqlQueryModel"
#include "QMessageBox"
#include"QApplication"
#include"QIntValidator"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->le_id->setValidator(new QIntValidator(0,99999,this));
    ui->le_telephone->setValidator(new QIntValidator(0,99999999,this));
    ui->le_prime->setValidator(new QIntValidator(0,9999,this));
    ui->le_salaire->setValidator(new QIntValidator(0,9999,this));



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajout_clicked()
{
int id_employe=ui->le_id->text().toInt();
QString nom_e=ui->le_nom->text();
QString prenom_e=ui->le_prenom->text();
int num_tel_e=ui->le_telephone->text().toInt();
QString mdp=ui->le_mdp->text();
QString adresse_e=ui->l_adresse->text();
QString type_e=ui->le_type->text();
int prime=ui->le_prime->text().toInt();
int salaire=ui->le_salaire->text().toInt();
employee e(id_employe,nom_e,prenom_e,num_tel_e,mdp,adresse_e,type_e,prime, salaire);
bool test=e.ajouter();
if (test)
{
    QMessageBox::information(nullptr, QObject::tr(" ok"),
                                 QObject::tr("ajout effecte  .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

       }
       else
       {

        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("ajout non effecte .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}}

