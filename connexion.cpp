#include"connexion.h"
//test connexion
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet");
db.setUserName("chaima");//inserer nom de l'utilisateur
db.setPassword("chaima");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
void Connection ::closeconnect(){db.close();}
