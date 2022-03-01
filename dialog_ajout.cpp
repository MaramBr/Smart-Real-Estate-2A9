#include "dialog_ajout.h"
#include "ui_dialog_ajout.h"

Dialog_ajout::Dialog_ajout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ajout)
{
    ui->setupUi(this);
}

Dialog_ajout::~Dialog_ajout()
{
    delete ui;
}
