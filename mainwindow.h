#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "contrat.h"
#include <QMainWindow>
#include "QrCode.hpp"
#include "arduino.h"

#include <vector>
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
    void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
    // ce slot est lancé à chaque réception d'un message de Arduino


    void on_ajout_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_quitter_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_tab_contrat_activated(const QModelIndex &index);

    //void on_QR_code_clicked();

    void on_CODEQR_clicked();

    void on_stattype_clicked();

    void on_calcul_clicked();

    //void on_pushButton_2_clicked();

    void on_pushButton_alarme_clicked();

private:
    Ui::MainWindow *ui;
     Contrat c,C1,c2,c3;

     //Arduino
     QByteArray data; // variable contenant les données reçues

     Arduino A; // objet temporaire
};
#endif // MAINWINDOW_H
