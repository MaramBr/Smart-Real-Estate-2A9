#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "immeuble.h"
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

    void on_Supprimer_clicked();

    void on_Modifier_clicked();

    void on_tri_id_clicked();

    void on_rechercher_clicked();

    void on_sombre_clicked();

    void on_blanc_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    immeuble Etmp;
};
#endif // MAINWINDOW_H
