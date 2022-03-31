#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "rdv.h"
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
    void on_pushButton_clicked();
    void on_pushButton_Supprimer_clicked();
    void on_pushButton_2_clicked();

    void on_pb_tricroi_clicked();

    void on_pb_tridecroi_clicked();

    void on_pushButton_4_clicked();

    void on_line_edit_Recherche_textChanged();

private:
    Ui::MainWindow *ui;
   rdv Et, Etu,R;
};


#endif // MAINWINDOW_H



