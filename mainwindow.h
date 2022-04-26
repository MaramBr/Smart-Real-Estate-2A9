#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <clients.h>
#include <contrat.h>
#include <appartement.h>
#include <arduino.h>

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


    void on_ajouter_clicked();

    void on_modifier_clicked();

    void on_supprimer_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_pushButton_13_clicked();

    void on_historique_clicked();

    void on_pushButton_12_clicked();

    void on_ajoutcontrat_clicked();

    void on_modifiercontrat_clicked();

    void on_supprimercontrat_clicked();

    void on_rechcontrat_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_retour_clicked();

    void on_retour_2_clicked();

    void on_calcul_clicked();



    void on_CODEQR_clicked();

    void on_stattype_clicked();

    void on_pushButton_5_clicked();

    void on_stattype_2_clicked();

    void on_pushButton_alarme_clicked();


    void on_quitter_3_clicked();

    void on_quitter_2_clicked();

    void on_retour_4_clicked();

    void on_retour_3_clicked();



    void on_retour_5_clicked();

    void on_pushButton_7_clicked();

    void on_quitter_clicked();

    void on_ajouter_appartement_clicked();

    void on_modifier_appartement_clicked();

    void on_supprimer_appartement_clicked();

    void on_rech_appartement_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_8_clicked();

    void on_pdf_clicked();

    void on_pushButton_10_clicked();

    void on_stattype_3_clicked();

private:
    Ui::MainWindow *ui;
    //Client
    Clients C,C1,C2,C3;
    //Contrat
Contrat c,c1,c2,c3;
    //appartement
Appartements a,a1,a2;
//Arduinoo
QByteArray data; // variable contenant les données reçues
Arduino A,A1,A2;
};
#endif // MAINWINDOW_H
