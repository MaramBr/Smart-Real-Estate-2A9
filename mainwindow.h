#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "contrat.h"
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


    void on_ajout_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_quitter_clicked();

private:
    Ui::MainWindow *ui;
     Contrat c,C1,c2;
};
#endif // MAINWINDOW_H
