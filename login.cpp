#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <contrat.h>
#include <QMessageBox>
#include <QThread>
#include <QDebug>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}


void login::on_login_2_clicked()
{

}
