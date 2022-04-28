#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <clients.h>
#include <contrat.h>
#include <appartement.h>
#include <arduino.h>
#include <arduinoalarme.h>
#include <employee.h>
#include <immeuble.h>
#include <rdv.h>
#include "smtp.h"
#include <QtWidgets/QMessageBox>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


        //Arduino
    void update_alarme();   // slot permettant la mise à jour du label état de la lampe 1,
        // ce slot est lancé à chaque réception d'un message de Arduino

    void update_parking();


    void on_ajouter_3_clicked();

    void on_modifier_3_clicked();

    void on_supprimer_3_clicked();

    void on_radioButton_11_clicked();

    void on_radioButton_12_clicked();

    void on_pushButton_16_clicked();

    void on_historique_3_clicked();

    void on_pushButton_17_clicked();

    void on_ajoutcontrat_5_clicked();

    void on_modifiercontrat_5_clicked();

    void on_supprimercontrat_5_clicked();

    void on_rechcontrat_5_clicked();

    void on_radioButton_19_clicked();

    void on_radioButton_20_clicked();

    void on_calcul_5_clicked();

    void on_CODEQR_5_clicked();

    void on_stattype_13_clicked();

    void on_stattype_8_clicked();

    void on_pushButton_alarme_clicked();




    void on_ajouter_appartement_clicked();

    void on_modifier_appartement_clicked();

    void on_supprimer_appartement_clicked();

    void on_rech_appartement_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_8_clicked();

    void on_pdf_clicked();

    void on_pushButton_10_clicked();

    void on_stattype_3_clicked();

    void on_ajoutemp_3_clicked();

    void on_modifieremp_3_clicked();

    void on_supprimeremp_3_clicked();

    void on_rechemp_3_clicked();

    void on_radioButton_23_clicked();

    void on_radioButton_24_clicked();

    void on_stattype_4_clicked();




    void on_login_clicked();

    void on_client_clicked();

    void on_Appar_clicked();

    void on_embarque_clicked();

    void on_retourCl_clicked();

    void on_quitterCl_clicked();

    void on_retourC_clicked();

    void on_quitterC_clicked();

    void on_retourApp_clicked();

    void on_quitterApp_clicked();

    void on_retouremp_clicked();

    void on_quitteremp_clicked();

    void on_retoural_clicked();

    void on_retourpar_clicked();

    void on_quitter_immeuble_clicked();

     void on_retour_immeuble_clicked();
//immeuble
    void on_ajouterimmeuble_clicked();

    void on_modifierimmeuble_clicked();

    void on_supprimerimmeuble_clicked();

    void on_rechimmeuble_clicked();

    void on_triimmeuble_clicked();

    void on_triimmeuble_2_clicked();





    void on_statimmeuble_clicked();

    void on_immeuble_clicked();

    void on_ajouterrdv_clicked();

    void on_modifrdv_clicked();

    void on_supprdv_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_statrdv_clicked();



    void on_numrdv_3_textChanged();

    void on_calendarWidget_2_clicked(const QDate &date);

    void on_RDV_clicked();

    void on_quitterrdv_clicked();

    void on_retourrdv_clicked();

    void sendMail();
        void mailSent(QString);
        void browse();




private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
            QWidget *page;
            QWidget *page2;
    //Client
    Clients C,C1,C2,C3;
    //Contrat
Contrat c,c1,c2,c3;
    //appartement
Appartements a,a1,a2;
//employees
employee e,e1,e2,e3;
//Rendez-vous
rdv R,R1,R2,R3;
QStringList files;
//immeuble
 immeuble Etmp,Etmp1;
//Arduinoo
QByteArray data; // variable contenant les données reçues
Arduino A,A1;

};
#endif // MAINWINDOW_H
