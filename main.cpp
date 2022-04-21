#include "mainwindow.h"
#include "QApplication"
#include "connexion.h"
#include <QMessageBox>
#include <QTranslator>
#include <QInputDialog>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
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

    bool test = c.createconnection();
    MainWindow w;
    if (test){
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Connection successful"),
                              QMessageBox::Ok
                              );


    }else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Connection failed"),
                              QMessageBox::Cancel
                              );
    }
    return a.exec();

}
