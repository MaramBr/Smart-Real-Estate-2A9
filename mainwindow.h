#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "clients.h"
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

    void on_pushButton_13_clicked();

private:
    Ui::MainWindow *ui;
    Clients c,c1,c2,c3;
};
#endif // MAINWINDOW_H
