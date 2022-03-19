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
#include <QRegExpValidator>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
ui->tab_contrat->setModel(c.afficher());
ui->le_num->setValidator( new QRegExpValidator(QRegExp("[0-9]{1,4}")));
ui->le_mode->setValidator( new QRegExpValidator(QRegExp("[a-z]{1,10}")));

ui->le_montant->setValidator( new QIntValidator(0,999999, this));
ui->le_cin->setValidator( new QRegExpValidator(QRegExp("[1-9]{1,8}")));

//ui->le_cin->setValidator( new QRegExpValidator(QRegExp("{1,10}")));


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ajout_clicked()
{


    QString numc= ui->le_num->text();


    QDate date_signification =ui->le_date->date();
    int montant =ui->le_montant->text().toInt();
    QString typec =ui->le_type->currentText();
    QString mode_paiement =ui->le_mode->text();

   QString cin =ui->le_cin->text();
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

    C1.setnum(ui->le_num_supp->text());
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

    c2.setnum(ui->le_num->text());
    c2.setdate(  ui->le_date->date());
    c2.setmontant(ui->le_montant->text().toInt());
    c2.settype(ui->le_type->currentText());
    c2.setmode(ui->le_mode->text());
    c2.setcin(ui->le_cin->text());
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

void MainWindow::on_radioButton_clicked()
{
    ui->tab_contrat->setModel(c.triercroissant());

}

void MainWindow::on_radioButton_2_clicked()
{
    ui->tab_contrat->setModel(c.trierdecroissant());

}


void MainWindow::on_pushButton_5_clicked()
{
    Contrat c3;

    c3.setnum(ui->recherche->text());
    ui->tab_contrat->setModel(c3.recherche(c3.getnum()));



}

void MainWindow::on_tab_contrat_activated(const QModelIndex &index)
{
    Contrat cc;
    QString val = ui->tab_contrat->model()->data(index).toString();
    Connection c;
if(!c.createconnect())
{
qDebug() <<"failed to open";
return;
}
c.createconnect();
    QSqlQuery query;
    query.prepare("select * from CONTRATS where numc='"+val+"' OR date_signification='"+val+"' OR montant='"+val+"' OR  typec='"+val+"' OR mode_paiement='"+val+"' OR cin='"+val+"' ");
    if (query.exec())
    {

        while (query.next())
        {
            ui->le_num->setText(query.value(0).toString());
            ui->le_date->setDate(query.value(1).toDate());
            ui->le_montant->setText(query.value(2).toString());
            ui->le_type->setCurrentText(query.value(3).toString());
            ui->le_mode->setText(query.value(4).toString());
            ui->le_cin->setText(query.value(5).toString());
        }
    }
    else
    {
        QMessageBox::critical(this,tr("erreur"),query.lastError().text());
    }
}

void MainWindow::on_QR_code_clicked()
{

    c.generateQr();

//    QString qr=ui->le_QR->text();
//    if(qr=="1")
//          {
//              QPixmap pix("C:/Users/Aziz-PC/OneDrive/Bureau/school/2eme anne/projet c++/qr/1.png");
//              int w = ui->label_pic_2->width();
//              int h = ui->label_pic_2->height();
//               ui->label_pic_2->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));


//          }
//   else if(qr=="2")
//          {
//              QPixmap pix("C:/Users/Aziz-PC/OneDrive/Bureau/school/2eme anne/projet c++/qr/2.png");
//              int w = ui->label_pic_2->width();
//              int h = ui->label_pic_2->height();
//               ui->label_pic_2->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));


//          }
//   else if(qr=="3")
//          {
//              QPixmap pix("C:/Users/Aziz-PC/OneDrive/Bureau/school/2eme anne/projet c++/qr/3.png");
//              int w = ui->label_pic_2->width();
//              int h = ui->label_pic_2->height();
//               ui->label_pic_2->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));


//          }
//    else
//    {
//        QMessageBox msgBox;

//               msgBox.setText("taper 1 ou 2 ou 3");
//           msgBox.exec();
}
