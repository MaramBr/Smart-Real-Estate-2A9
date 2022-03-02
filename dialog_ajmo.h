#ifndef DIALOG_AJMO_H
#define DIALOG_AJMO_H

#include <QDialog>

namespace Ui {
class Dialog_ajmo;
}

class Dialog_ajmo : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_ajmo(QWidget *parent = nullptr);
    ~Dialog_ajmo();

private:
    Ui::Dialog_ajmo *ui;
};

#endif // DIALOG_AJMO_H
