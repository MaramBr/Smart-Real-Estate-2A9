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
#include <Calculatrice.h>


using namespace qrcodegen;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

  // QTabBar *tabBar = ui->tab_contrat_2->findChild<QTabBar *>();
   // tabBar->hide();

ui->tab_contrat->setModel(c.afficher());
ui->le_num->setValidator( new QRegExpValidator(QRegExp("[0-9]{1,4}")));
ui->le_mode->setValidator( new QRegExpValidator(QRegExp("[a-z]{1,10}")));

ui->le_montant->setValidator( new QIntValidator(0,999999, this));
ui->le_cin->setValidator( new QRegExpValidator(QRegExp("[1-9]{1,8}")));

//ui->le_cin->setValidator( new QRegExpValidator(QRegExp("{1,10}")));

//Arduino
int ret=A.connect_arduino(); // lancer la connexion à arduino
switch(ret){
case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
    break;
case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
   break;
case(-1):qDebug() << "arduino is not available";
}
 QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
 //le slot update_label suite à la reception du signal readyRead (reception des données).


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
    //Connection c;

//c.createconnect();
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
    /*
    else
    {
        QMessageBox::critical(this,tr("erreur"),query.lastError().text());
    }*/
}

void MainWindow::on_CODEQR_clicked()
{
    // NOTE: At this point you will use the API to get the encoding and format you want, instead of my hardcoded stuff:

    int tabprod=ui->tab_contrat->currentIndex().row();
    QVariant numcc=ui->tab_contrat->model()->data(ui->tab_contrat->model()->index(tabprod,0));
    QString numc= numcc.toString();
    QSqlQuery qry;
    qry.prepare("select * from CONTRATS where numc=:numc");
    qry.bindValue(":numc",numc);
    qry.exec();
   // QDate date_signification;
    QString montant,typec,mode_paiement,cin;
    while(qry.next()){
        montant=qry.value(1).toString();
        typec=qry.value(2).toString();
        mode_paiement=qry.value(3).toString();
       // cin==qry.value(4).toString();
    }
   // numcs=QString::number(numc);
    numc="numc: "+montant+" montant: "+typec+" typec: "+mode_paiement+"mode_paiement: ";
    QrCode qr = QrCode::encodeText(numc.toUtf8().constData(), QrCode::Ecc::HIGH);


    QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
    // NOTE: For performance reasons my implementation only draws the foreground parts in supplied color.
    // It expects background to be prepared already (in white or whatever is preferred).
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            int color = qr.getModule(x, y);  // 0 for white, 1 for black

            // You need to modify this part
            if(color==0)
                im.setPixel(x, y,qRgb(254, 254, 254));
            else
                im.setPixel(x, y,qRgb(0, 0, 0));
        }
    }
    im=im.scaled(200,200);
    ui->qrlabel->setPixmap(QPixmap::fromImage(im));
}

void MainWindow::on_stattype_clicked()
{

    ui->tab_contrat_2->setCurrentIndex(3);
    Contrat c;

    c.stat(ui->widget);

}

void MainWindow::on_calcul_clicked()
{
    Calculatrice calc;
    calc.setModal(true);
    calc.exec();
   // hide();
     //calcul cc;
    //QString val = QString::number(c.calucul());
    //ui->le_montant->setText(val);

//calcul c;

   //c.exec();

}
void MainWindow::update_label()
{
    data=A.read_from_arduino();//lire les information de arduino vers qt
        qDebug() << data;
        QString temp = QString::fromStdString(data.toStdString());
        qDebug() << temp;
         //capteur presence + distance
         ui->Distance->setText(temp);
         if (temp.toFloat()<20 && temp.toFloat()!=0 ) // Il Y A une alarme sonor + insertion BD
         {
            ui->Etat->setText("DANGER");
            A.write_to_arduino("1");
             QSqlQuery query;
                 int te=temp.toInt();
                 //prepare()prend la requete en param pour la preparer a l'execution
                  query.prepare("insert into alarme (distance) values(:dis)");
                 //creation des variable liés
                 query.bindValue(":dis",te);
             query.exec();
             if(!query.exec()) {
                     QMessageBox::critical(this, tr("Erreur base de données"),
                         tr("Erreur lors de l'exécution de la requête: %1")
                                           .arg(query.lastError().text()));
                     return;
                 }
         }
         else
         {
              ui->Etat->setText("En Sécurité");
         }

}
void MainWindow::on_pushButton_alarme_clicked()
{
             ui->tableView_alarme->setModel(A.afficherAlarme());
}
