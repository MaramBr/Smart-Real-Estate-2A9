#include "dialog_modif.h"
#include "ui_dialog_modif.h"

Dialog_modif::Dialog_modif(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_modif)
{
    ui->setupUi(this);
}

Dialog_modif::~Dialog_modif()
{
    delete ui;
}
