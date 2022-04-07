#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QInputDialog>
#include "connexion.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    Connection c;
    bool test=c.createconnect();
//*********************
    QTranslator t;
     QTranslator guiTranslator;
    QStringList languages;
    languages <<"Frensh"<<"English";
    QString lang = QInputDialog::getItem(NULL,"select Language",
                                         "Language",languages);
    if(lang=="English")
    {
        t.load(":/english.qm");
        a.installTranslator(&t);
    }

//**********************
    MainWindow w;
    if(test)
    {w.show();
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
