#include "dialog_qr.h"
#include "ui_dialog_qr.h"

Dialog_qr::Dialog_qr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_qr)
{
    ui->setupUi(this);
}

Dialog_qr::~Dialog_qr()
{
    delete ui;
}
