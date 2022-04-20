#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "clients.h"
#include "arduino.h"
#include <QMainWindow>
#include <QSqlError>
#include "QMessageBox"

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

    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_quitter_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_3_clicked();

    void on_historique_clicked();
    //

private:
    Ui::MainWindow *ui;
    Clients c,c1,c2,c3,c4;
    //Arduino
    QByteArray data; // variable contenant les données reçues d'arduino
    arduino A; // objet temporaire
};
#endif // MAINWINDOW_H
