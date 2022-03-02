#ifndef DIALOG_MODIF_H
#define DIALOG_MODIF_H

#include <QDialog>

namespace Ui {
class Dialog_modif;
}

class Dialog_modif : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_modif(QWidget *parent = nullptr);
    ~Dialog_modif();

private:
    Ui::Dialog_modif *ui;
};

#endif // DIALOG_MODIF_H
