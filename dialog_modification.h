#ifndef DIALOG_MODIFICATION_H
#define DIALOG_MODIFICATION_H

#include <QDialog>

namespace Ui {
class Dialog_modification;
}

class Dialog_modification : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_modification(QWidget *parent = nullptr);
    ~Dialog_modification();

private:
    Ui::Dialog_modification *ui;
};

#endif // DIALOG_MODIFICATION_H
