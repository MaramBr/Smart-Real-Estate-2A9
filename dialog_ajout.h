#ifndef DIALOG_AJOUT_H
#define DIALOG_AJOUT_H

#include <QDialog>

namespace Ui {
class Dialog_ajout;
}

class Dialog_ajout : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_ajout(QWidget *parent = nullptr);
    ~Dialog_ajout();

private:
    Ui::Dialog_ajout *ui;
};

#endif // DIALOG_AJOUT_H
