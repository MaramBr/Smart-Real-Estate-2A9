#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <calculatrice.h>
#include<QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QSqlQuery>
#include <QSqlError>

#include<QImage>
#include <qcustomplot.h>
#include <QrCode.hpp>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//pour les clients
    ui->tab_clients->setModel(C.afficher());
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
    //pour les contrats

    ui->tab_contrat->setModel(c.afficher());
    ui->le_numc->setValidator( new QRegExpValidator(QRegExp("[0-9]{1,4}")));
    ui->le_mode->setValidator( new QRegExpValidator(QRegExp("[a-z]{1,10}")));

    ui->le_montant->setValidator( new QIntValidator(0,999999, this));
    ui->le_cinc->setValidator( new QRegExpValidator(QRegExp("[1-9]{1,8}")));
    //pour les appartements
    ui->tab_appartement->setModel(a.afficher());

   ui->le_nbchambres->setValidator( new QIntValidator(0,9, this));
   ui->le_prix->setValidator( new QIntValidator(0,999999, this));
   ui->le_id2->setValidator( new QIntValidator(0, 99999, this));
   ui->le_id->setValidator( new QRegExpValidator(QRegExp("[0-9]{1,4}")));
   //QPixmap outPixmap=QPixmap();



 //  ui->le_image->setPixmap(outPixmap.scaled(400,200,Qt::KeepAspectRatio));

   ui->tab_appartement->setModel(a.afficher());



// Arduino pour tous
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }

    QObject::connect(A1.getserial(),SIGNAL(readyRead()),this,SLOT(update_alarme())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_parking())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).
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

void MainWindow::on_radioButton_5_clicked()
{
     ui->tab_clients->setModel(C2.triercroissant());
}

void MainWindow::on_radioButton_6_clicked()
{
     ui->tab_clients->setModel(C2.trierdecroissant());
}

void MainWindow::on_pushButton_13_clicked()
{
    Clients c3;
    c3.setcin(ui->cin_rech->text());
    ui->tab_clients->setModel(c3.recherche(c3.getcin()));
}

void MainWindow::on_historique_clicked()
{

    QString date=ui->choixdate->text();
    Clients c3;
    c3.save_historique(date);
    QString lien  = "file:///C:/historique/histo.txt";
    QDesktopServices::openUrl(QUrl(lien, QUrl::TolerantMode));
}

void MainWindow::on_pushButton_12_clicked()
{
    Clients c4;
    c4.excel();
    QString ExcelFileName  = "C:/excel/Clients.csv";
    QDesktopServices::openUrl(QUrl(ExcelFileName, QUrl::TolerantMode));
}

void MainWindow::on_ajoutcontrat_clicked()
{
    QString numc= ui->le_numc->text();
    QDate date_signification =ui->le_date->date();
    int montant =ui->le_montant->text().toInt();
    QString typec =ui->le_typec->currentText();
    QString mode_paiement =ui->le_mode->text();
   QString cin =ui->le_cinc->text();
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





void MainWindow::on_modifiercontrat_clicked()
{
    Contrat c2;

       c2.setnum(ui->le_numc->text());
       c2.setdate(  ui->le_date->date());
       c2.setmontant(ui->le_montant->text().toInt());
       c2.settype(ui->le_typec->currentText());
       c2.setmode(ui->le_mode->text());
       c2.setcin(ui->le_cinc->text());
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

void MainWindow::on_supprimercontrat_clicked()
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

void MainWindow::on_rechcontrat_clicked()
{
    Contrat c3;

    c3.setnum(ui->recherche->text());
    ui->tab_contrat->setModel(c3.recherche(c3.getnum()));

}

void MainWindow::on_radioButton_clicked()
{
        ui->tab_contrat->setModel(c.triercroissant());
}

void MainWindow::on_radioButton_2_clicked()
{
        ui->tab_contrat->setModel(c.trierdecroissant());
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tabWidget->setCurrentIndex(1);

}

void MainWindow::on_pushButton_4_clicked()
{
    ui->tabWidget->setCurrentIndex(2);

}

void MainWindow::on_retour_clicked()
{
      ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_retour_2_clicked()
{
  ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_calcul_clicked()
{
    Calculatrice calc;
    calc.setModal(true);
    calc.exec();
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
    qrcodegen::QrCode  qr = qrcodegen::QrCode::encodeText(numc.toUtf8().constData(), qrcodegen::QrCode::Ecc::HIGH);


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
    ui->tabWidget_2->setCurrentIndex(1);
    Contrat c;

    c.stat(ui->widget_3);

}

void MainWindow::on_pushButton_5_clicked()
{
    ui->tabWidget->setCurrentIndex(3);

}

void MainWindow::on_stattype_2_clicked()
{
    ui->tabWidget_4->setCurrentIndex(1);
   Clients c;

    c.statclient(ui->widget_7);
}

void MainWindow::update_alarme()
{
    data=A1.read_from_arduino();//lire les information de arduino vers qt
        qDebug() << data;
        QString temp = QString::fromStdString(data.toStdString());
        qDebug() << temp;
         //capteur presence + distance
         ui->Distance->setText(temp);
         if (temp.toFloat()<20 && temp.toFloat()!=0 ) // Il Y A une alarme sonor + insertion BD
         {
            ui->Etat->setText("DANGER");
            A1.write_to_arduino("1");
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
                                           /*.arg(query.lastError().text())*/);
                     return;
                 }
         }
         else
         {
              ui->Etat->setText("En Sécurité");
         }

}

void MainWindow::update_parking()
{
    data=A.read_from_arduino();
    qDebug() << data;
    QString temp = QString::fromStdString(data.toStdString());
    //qDebug() << temp;

     //clavier
     ui->CIN->setText(temp);
     int te=temp.toInt();
          QSqlQuery query;
          query.prepare("SELECT NOM_E FROM EMPLOYES where ID_EMPLOYE=:t");
          query.bindValue(":t",te);
          query.exec();
          if(!query.exec()) {
                  QMessageBox::critical(this, tr("Erreur base de données"),
                      tr("Erreur lors de l'exécution de la requête: %1")
                                       /* .arg(query.lastError().text())*/);
                  return;
              }
              if (!query.first()) {
                 // QMessageBox::warning(this, QObject::tr("Erreur !"),
                    //  "CIN employe inexistant");
                       ui->Etat_2->setText("CIN invalable");
                       //A.write_to_arduino("0");

                  return;
              }
              else{
          //QString state=query.value(0).toString();
          ui->Etat_2->setText("CIN valable");

          A.write_to_arduino("1");

          }
}

void MainWindow::on_pushButton_alarme_clicked()
{
    ui->tableView_alarme->setModel(A1.afficherAlarme());

}



void MainWindow::on_quitter_3_clicked()
{
    close();
}

void MainWindow::on_quitter_2_clicked()
{
    close();
}

void MainWindow::on_retour_4_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_retour_3_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}



void MainWindow::on_retour_5_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}

void MainWindow::on_quitter_clicked()
{
   close();
}

void MainWindow::on_ajouter_appartement_clicked()
{
    QString id_appartement= ui->le_id->text();
    int prix =ui->le_prix->text().toInt();
    int nb_chambres =ui->le_nbchambres->text().toInt();
    QString description_A =ui->le_description->text();
    int id_immeuble= ui->le_id2->text().toInt();
    QString image=ui->le_image->text();


     Appartements A(id_appartement,prix,nb_chambres,description_A,id_immeuble,image);
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

void MainWindow::on_modifier_appartement_clicked()
{
    Appartements a2;

        a2.setid_appartement(ui->le_id->text());
        a2.setprix(ui->le_prix->text().toInt());
        a2.setnb_chambres(ui->le_nbchambres->text().toInt());
        a2.setdescription_A(ui->le_description->text());
        a2.setid_immeuble(ui->le_id2->text().toInt());

       bool test=a2.modifier(a2.getid_appartement(),a2.getprix(),a2.getnb_chambres(),a2.getdescription_A(),a2.getid_immeuble());
    if (test)
    {
        ui->tab_appartement->setModel(a2.afficher());

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

void MainWindow::on_supprimer_appartement_clicked()
{
    Appartements a1;

        a1.setid_appartement(ui->id_supp->text());
        bool test =a1.supprimer(a1.getid_appartement());
        QMessageBox msgBox;
        if(test)
        {
             ui->tab_appartement->setModel(a1.afficher());
            msgBox.setText("suppression aves succes.");
        }
        else
            msgBox.setText("echec de suppression");
        msgBox.exec();
}

void MainWindow::on_rech_appartement_clicked()
{
    Appartements a3;
    a3.setid_appartement(ui->id_rech->text());
    ui->tab_appartement->setModel(a3.rechercher(a3.getid_appartement()));
}

void MainWindow::on_radioButton_7_clicked()
{
    ui->tab_appartement->setModel(a.triercroissant());
}

void MainWindow::on_radioButton_8_clicked()
{
    ui->tab_appartement->setModel(a.trierdecroissant());
}

void MainWindow::on_pdf_clicked()
{
    Appartements a4;
    a4.pdf();
    QString PdfFileName ="C:/pdf/a.pdf" ;
    QDesktopServices::openUrl(QUrl(PdfFileName, QUrl::TolerantMode));
         // QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
          //QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_10_clicked()
{
    //QSqlQuery q;
    QString fileName =QFileDialog::getOpenFileName(this,tr("choose an image "),"",tr("All files (*)"));

    qDebug()<<fileName+"url" ;
    ui->le_image->setText(fileName);
}

void MainWindow::on_stattype_3_clicked()
{
    ui->tab2->setCurrentIndex(1);
      Appartements a;


      a.stat(ui->widget_9);
}
