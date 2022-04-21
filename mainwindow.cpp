#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rdv.h"
#include <QMessageBox>
#include <QDate>
#include <QIntValidator>
#include <QPainter>
#include <QtCharts>
#include <QPieSlice>
#include <QPieSeries>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
    ui->lineEdit_num->setValidator(new QIntValidator (0,9999,this)) ;


    ui->tableView->setModel(Et.afficher());
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
void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

//
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int NUM_RDV = ui->lineEdit_num->text().toInt();
    QDate DATE_RDV = ui->dateEdit->date();
    QString type;
    QString EMAIL= ui->emaill->text();

if (ui->radioButton->isChecked())
{ type="location" ; }
if (ui->radioButton_vente->isChecked())
{ type="vente" ; }


    rdv R (NUM_RDV,DATE_RDV,type,EMAIL);
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
    QString EMAIL=ui->emaill->text();
if (ui->radioButton->isChecked())
{ type="location" ; }
if (ui->radioButton_vente->isChecked())
{ type="vente" ; }
    rdv R2(NUM_RDV, DATE_RDV,type,EMAIL);
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



void MainWindow::on_pb_tricroi_clicked()
{
    ui->tableView->setModel(Et.tricroi());

}


void MainWindow::on_pb_tridecroi_clicked()
{
    ui->tableView->setModel(Et.tridecroi());

}





void MainWindow::on_pushButton_4_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                     model->setQuery("select * from RDV where NUM_RDV < 10 ");
                     float NUM_RDV1=model->rowCount();
                     model->setQuery("select * from RDV where NUM_RDV  between 10 and 20 ");
                     float NUM_RDV2=model->rowCount();
                     model->setQuery("select * from RDV where NUM_RDV >20 ");
                     float NUM_RDV3=model->rowCount();
                     float total=NUM_RDV1+NUM_RDV2+NUM_RDV3;
                     QString a=QString("inferieur a 10  "+QString::number((NUM_RDV1*100)/total,'f',2)+"%" );
                     QString b=QString("entre 10 et 20  "+QString::number((NUM_RDV2*100)/total,'f',2)+"%" );
                     QString c=QString("+20  "+QString::number((NUM_RDV3*100)/total,'f',2)+"%" );
                     QPieSeries *series = new QPieSeries();
                     series->append(a,NUM_RDV1);
                     series->append(b,NUM_RDV2);
                     series->append(c,NUM_RDV3);
             if (NUM_RDV1!=0)
             {QPieSlice *slice = series->slices().at(0); //pourcentage de chaque slice
              slice->setLabelVisible();
              slice->setPen(QPen());}
             if ( NUM_RDV2!=0)
             {
                      // Add label, explode and define brush for 2nd slice
                      QPieSlice *slice1 = series->slices().at(1);
                      //slice1->setExploded();
                      slice1->setLabelVisible();
             }
             if(NUM_RDV3!=0)
             {
                      // Add labels to rest of slices
                      QPieSlice *slice2 = series->slices().at(2);
                      //slice1->setExploded();
                      slice2->setLabelVisible();
             }
                     // Create the chart widget
                     QChart *chart = new QChart();
                     // Add data to chart with title and hide legend
                     chart->addSeries(series);
                     chart->setTitle("Pourcentage Par num :Numero rendez-vous "+ QString::number(total));
                     chart->legend()->hide();
                     // Used to display the chart
                     QChartView *chartView = new QChartView(chart);
                     chartView->setRenderHint(QPainter::Antialiasing);
                     chartView->resize(1000,500);
                     chartView->show();
}

void MainWindow::on_line_edit_Recherche_textChanged()
{
    QString rech=ui->line_edit_Recherche->text();
    ui->tableView->setModel(R.Rechercherdv(rech));

}


void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QString newdate= date.toString("dd/MM/yyyy");
        qInfo() << newdate ;
        ui->tableView_2->setModel((R.recherche_date(newdate)));
}
void MainWindow::update_label()
{
    data=A.read_from_arduino();
        QSqlQuery q;
        if (data=="1")
       { q.prepare("Select * from EMPLOYES where ID_EMPLOYE=456");

        q.exec();
        q.first();
    ui->arduinoo->setText(q.value(1).toString());
       ui->pre->setText(q.value(2).toString()); }
else if  (data=="2")
        { q.prepare("Select * from EMPLOYES where ID_EMPLOYE=583");

         q.exec();
         q.first();
     ui->arduinoo->setText(q.value(1).toString());
        ui->pre->setText(q.value(2).toString()); }
   // ui->textEdit->append(data);



}

