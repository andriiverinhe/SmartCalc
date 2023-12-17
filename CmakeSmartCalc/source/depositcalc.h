#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include <QDialog>

namespace Ui {
class depositcalc;
}

class depositcalc : public QDialog
{
    Q_OBJECT

public:
    explicit depositcalc(QWidget *parent = nullptr);
    ~depositcalc();

private slots:
    void on_pushButton_calculate_clicked();

    void on_pushButton_addPays_clicked();

    void on_pushButton_addWithdrawals_clicked();

    void on_checkBox_listPays_clicked();

    void on_checkBox_Withdrawals_clicked();

    void on_pushButton_removePays_clicked();

    void on_pushButton_removeWithdrawals_clicked();

private:
    Ui::depositcalc *ui;
};

#endif // DEPOSITCALC_H
