#include"connexion.h"
//test connexion
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Project");
db.setUserName("Maram");//inserer nom de l'utilisateur
db.setPassword("esprit21");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
void Connection ::closeconnect(){db.close();}
