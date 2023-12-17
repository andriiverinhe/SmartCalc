#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QDialog>

namespace Ui {
class creditcalc;
}

class creditcalc : public QDialog
{
    Q_OBJECT

public:
    explicit creditcalc(QWidget *parent = nullptr);
    ~creditcalc();

private slots:
    void on_pushButton_calculate_clicked();

private:
    Ui::creditcalc *ui;
};

#endif // CREDITCALC_H
