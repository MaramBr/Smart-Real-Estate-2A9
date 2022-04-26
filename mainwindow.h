#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "rdv.h"
#include <QMainWindow>
#include "smtp.h"
#include <QtWidgets/QMessageBox>
#include <QFileDialog>
#include "arduino.h"
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
    void on_recherche_date(QString d);

    void on_calendarWidget_clicked(const QDate &date);
    void sendMail();
    void mailSent(QString);
    void browse();
void update_label();

void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
   rdv Et, Etu,R;
   QStringList files;
   QByteArray data; // variable contenant les données reçues

   Arduino A; //

};


#endif // MAINWINDOW_H



