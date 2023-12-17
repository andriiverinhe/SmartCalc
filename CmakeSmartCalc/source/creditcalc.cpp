#include "creditcalc.h"
#include "../ui_creditcalc.h"
#include <QValidator>
#include <QMessageBox>

#ifdef __cplusplus
extern "C" {
#endif
#include "../SmartCalc/s21_smartCalc.h"

#ifdef __cplusplus
}
#endif

creditcalc::creditcalc(QWidget *parent) :
    QDialog(parent),

    ui(new Ui::creditcalc)
{
    ui->setupUi(this);
    ui->lineEdit_SumCredit->setValidator( new QDoubleValidator(0, 100, 2, this));
    ui->lineEdit_Procent->setValidator( new QDoubleValidator(0, 100, 2, this));
    ui->lineEdit_TimeCredit->setValidator(new QIntValidator(1, 10000, this));
    ui->tableWidget->hide();
}

creditcalc::~creditcalc()
{
    delete ui;
}

void creditcalc::on_pushButton_calculate_clicked()
{
    bool infCheck = false;
    double loanAmount = ui->lineEdit_SumCredit->text().toDouble();
    double annualInterestRate = ui->lineEdit_Procent->text().toDouble();
    int loanTermMonths = ui->lineEdit_TimeCredit->text().toInt();

    if(loanAmount == 0 || annualInterestRate == 0|| loanTermMonths == 0) {
        infCheck = true;
        QMessageBox::critical(nullptr, "Ошибка", "Есть не заполненные поля!");
    }

    if(!infCheck) {
        if(ui->radioButton_annuity->isChecked()){
            ui->tableWidget->hide();
            window()->adjustSize();
            double result[3] = {0};

            s21_calculateAnnuityPayment(loanAmount, annualInterestRate, loanTermMonths, result);

            ui->label_monthlyPayment->setText(QString::number(result[0]));
            ui->label_totalPayment->setText(QString::number(result[1]));
            ui->label_overpayment->setText(QString::number(result[2]));

        }else if (ui->radioButton_differentiated->isChecked()) {
            ui->tableWidget->show();
            int rowCount =  0;
            rowCount = ui->lineEdit_TimeCredit->text().toInt();
            if(rowCount != 0) {
            int columnCount = 2;
            ui->tableWidget->setRowCount(rowCount);


            // Заполняем таблицу начальными данными с нумерацией в первой колонке
            for (int row = 0; row < rowCount; ++row) {
                // Создаем элемент для нумерации
                QTableWidgetItem *numberItem = new QTableWidgetItem(QString::number(row + 1));
                // Устанавливаем элемент в первую колонку
                ui->tableWidget->setItem(row, 0, numberItem);
            }
            double resTotal[2] = {0};
            double resMonthly[(int)rowCount];
            for(int i = 0; i < rowCount; i++) resMonthly[i] = 0;

            s21_calculateDifferentiatedPayment(loanAmount, annualInterestRate, loanTermMonths, resTotal, resMonthly);

            // Заполняем остальные колонки данными
            for (int row = 0; row < rowCount; ++row) {

                QTableWidgetItem *item = new QTableWidgetItem(QString::number(resMonthly[row]));
                ui->tableWidget->setItem(row, (columnCount - 1), item);
            }
            QTableWidgetItem *itemFirst = ui->tableWidget->item(0, 1);
            QTableWidgetItem *itemLast = ui->tableWidget->item((rowCount - 1), 1);

            ui->label_monthlyPayment->setText(itemFirst->text() + " ... " +itemLast->text());
            ui->label_totalPayment->setText(QString::number(resTotal[0]));
            ui->label_overpayment->setText(QString::number(resTotal[1]));

            window()->adjustSize();

        }

    }else {
            QMessageBox::critical(nullptr, "Поле не выбрано", "Выбирете тип ежемесечных платежей!");
        }
    }
}

