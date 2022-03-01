#include "dialog_modification.h"
#include "ui_dialog_modification.h"

Dialog_modification::Dialog_modification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_modification)
{
    ui->setupUi(this);
}

Dialog_modification::~Dialog_modification()
{
    delete ui;
}
