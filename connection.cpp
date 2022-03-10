#include "connection.h"

Connection::Connection(){
}

bool Connection::createconnection(){
    db = QSqlDatabase::addDatabase("QODBC");
    bool test = false;
    db.setDatabaseName("Project");
    db.setUserName("Maram");
    db.setPassword("esprit21");
    if (db.open()) test=true;
    return test;
}
void Connection::closeConnection(){
    db.close();
}
