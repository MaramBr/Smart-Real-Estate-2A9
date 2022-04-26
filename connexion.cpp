#include"connexion.h"
//test connexion
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source_projet2A");
db.setUserName("yoser");//inserer nom de l'utilisateur
db.setPassword("yoser");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
void Connection ::closeconnect(){db.close();}
