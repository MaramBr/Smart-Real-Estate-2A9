#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>

namespace Ui {
class calcul;
}

class calcul : public QDialog
{
    Q_OBJECT

public:
    explicit calcul(QWidget *parent = nullptr);
    ~calcul();

private slots:
    void on_pushButton_r_clicked();

private:
    Ui::calcul *ui;
private slots :
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
    void on_pushButton_Q_clicked();
};

#endif // CALCULATOR_H
