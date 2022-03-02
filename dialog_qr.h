#ifndef DIALOG_QR_H
#define DIALOG_QR_H

#include <QDialog>

namespace Ui {
class Dialog_qr;
}

class Dialog_qr : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_qr(QWidget *parent = nullptr);
    ~Dialog_qr();

private:
    Ui::Dialog_qr *ui;
};

#endif // DIALOG_QR_H
