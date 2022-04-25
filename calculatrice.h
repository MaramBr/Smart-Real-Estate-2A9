#ifndef CALCULATRICE_H
#define CALCULATRICE_H

#include <QDialog>

namespace Ui {
class Calculatrice;
}

class Calculatrice : public QDialog
{
    Q_OBJECT

public:
    explicit Calculatrice(QWidget *parent = nullptr);
    ~Calculatrice();

private:
    Ui::Calculatrice *ui;
private slots :
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
};

#endif // CALCULATRICE_H
