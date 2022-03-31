#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "appartements.h"
#include <QFileDialog>

#include <QMainWindow>

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

    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_quitter_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_9_clicked();

    void on_statistiques_clicked();

private:
    Ui::MainWindow *ui;
    Appartements a,a1,a2,a3,a4;
};
#endif // MAINWINDOW_H
