#include "dialog_ajmo.h"
#include "ui_dialog_ajmo.h"

Dialog_ajmo::Dialog_ajmo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ajmo)
{
    ui->setupUi(this);
}

Dialog_ajmo::~Dialog_ajmo()
{
    delete ui;
}
