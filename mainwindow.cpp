#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appartements.h"
#include "connexion.h"
#include <QMessageBox>
#include<QApplication>
#include <QString>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>

#include <QIntValidator>
 #include <QTableView>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->tab_appartement->setModel(a.afficher());

    ui->le_nbchambres->setValidator( new QIntValidator(0,9, this));
    ui->le_prix->setValidator( new QIntValidator(0,999999, this));
    ui->le_id2->setValidator( new QIntValidator(0, 99999, this));
    ui->le_id->setValidator( new QRegExpValidator(QRegExp("[0-9]{1,4}")));
    //QPixmap outPixmap=QPixmap();



  //  ui->le_image->setPixmap(outPixmap.scaled(400,200,Qt::KeepAspectRatio));

    ui->tab_appartement->setModel(a.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_ajouter_clicked()
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


void MainWindow::on_supprimer_clicked()
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

void MainWindow::on_modifier_clicked()
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

void MainWindow::on_quitter_clicked()
{
    close();
}

void MainWindow::on_radioButton_5_clicked()
{
      ui->tab_appartement->setModel(a.triercroissant());
}

void MainWindow::on_radioButton_6_clicked()
{
      ui->tab_appartement->setModel(a.trierdecroissant());
}

void MainWindow::on_pushButton_4_clicked()
{
    Appartements a3;
    a3.setid_appartement(ui->id_rech->text());
    ui->tab_appartement->setModel(a3.rechercher(a3.getid_appartement()));
}




void MainWindow::on_pushButton_11_clicked()
{

    Appartements a4;
    a4.pdf();
    QString PdfFileName ="C:/pdf/a.pdf" ;
    QDesktopServices::openUrl(QUrl(PdfFileName, QUrl::TolerantMode));
         // QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
          //QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_9_clicked()
{
   //QSqlQuery q;
   QString fileName =QFileDialog::getOpenFileName(this,tr("choose an image "),"",tr("All files (*)"));

   qDebug()<<fileName+"url" ;
   ui->le_image->setText(fileName);


    }


void MainWindow::on_statistiques_clicked()
{
    ui->tab2->setCurrentIndex(3);
      Appartements a;


      a.stat(ui->widget);
}
ImageSqlQueryModel::ImageSqlQueryModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    // Le blob png est contenu dans la colonne image
    setQuery("SELECT id, nom, image FROM images");
}

QVariant ImageSqlQueryModel::data(const QModelIndex &item, int role) const
{
    // Colonne pour l'image
    if (item.column() == 2)
    {
        // Evite d'afficher l'image sous forme de texte
        if (role == Qt::DisplayRole || role == Qt::EditRole)
            return QVariant();
        // Renvoie un QPixmap quand la vue demande l'icône de cette
        // colonne
        if (role == Qt::DecorationRole)
        {
            QVariant variant(QSqlQueryModel::data(item, Qt::DisplayRole));
            QByteArray bytes(variant.toByteArray());
            QPixmap pixmap;
            pixmap.loadFromData(bytes, "png");
            return pixmap;
        }
    }
    return QSqlQueryModel::data(item, role);
}
