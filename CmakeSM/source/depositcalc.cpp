#include "depositcalc.h"
#include "../ui_depositcalc.h"
#include <QMessageBox>
#include <cmath>
#include <QVector>
#include <QValidator>
#include <QDebug>
#ifdef __cplusplus
extern "C" {
#endif
#include "../SmartCalc/s21_smartCalc.h"

#ifdef __cplusplus
}
#endif


depositcalc::depositcalc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::depositcalc)
{
    ui->setupUi(this);

    ui->lineEdit_amount->setValidator( new QDoubleValidator(0, 100, 10, this));
    ui->lineEdit_taxRate->setValidator( new QDoubleValidator(0, 100, 10, this));
    ui->lineEdit_interestRate->setValidator( new QDoubleValidator(0, 100, 10, this));
    ui->lineEdit_term->setValidator(new QIntValidator(1, INT_MAX, this));


    ui->listWidget_periodOfPayments->addItem("Раз в месяц");
    ui->listWidget_periodOfPayments->addItem("Раз в год");

}

depositcalc::~depositcalc()
{
    delete ui;
}

void setArray(QTableWidget *table, double *&arr, int &count) {
    if (!table) {
        qDebug() << "Неверный указатель на QTableWidget.";
        return;
    }

    count = table->rowCount();
    arr = new double[count];

    for (int i = 0; i < count; i++) {
        // Получаем указатель на QLineEdit из ячейки
        QWidget *widget = table->cellWidget(i, 0);

        if (widget) {
            QLineEdit *lineEdit = qobject_cast<QLineEdit*>(widget);
            if (lineEdit) {
                double value = lineEdit->text().toDouble();
                arr[i] = value;
            } else {
                qDebug() << "Ошибка приведения типа. Объект в ячейке не является QLineEdit.";
            }
        } else {
            qDebug() << "В ячейке (" << i << ", 0) нет QLineEdit.";
        }
    }
}



bool checkCorrect(QString str){
return str.size() != 0? true : false;
}


int getperiod(QString str) {
    int pr = -1;
    if(str == "Раз в месяц")
        pr = 1;
    if(str == "Раз в год")
        pr = 2;
    return pr;
}


            // initialAmount == сумма вклада
            // depositTermMonths == срок вклада 
            // annualInterestRate == процентная ставка
            // taxRate == налог
            // payoutPeriodicity == выплаты (частота)
            // interestCapitalization == капитализация 
            // deposits == масив вкладов
            // withdrawals == массив снятий
            // depositCount == количество вкладов
            // withdrawalCount == количество снятий
void depositcalc::on_pushButton_calculate_clicked()
{

    bool infCheck = false;
    QString initialAmountStr = ui->lineEdit_amount->text();
    QString depositTermMonthsStr = ui->lineEdit_term->text();
    QString annualInterestRateStr = ui->lineEdit_interestRate->text();
    QString taxRateStr = ui->lineEdit_taxRate->text();
    QString payoutPeriodicityStr;
    if(ui->listWidget_periodOfPayments->currentItem())
       payoutPeriodicityStr = ui->listWidget_periodOfPayments->currentItem()->text();
    bool interestCapitalization = ui->checkBox->isChecked();

    double* deposits = nullptr;
    double* withdrawals = nullptr;
    int depositCount = ui->tableWidget->rowCount();
    int withdrawalCount = ui->tableWidget_Withdrawals->rowCount();

    if (ui->checkBox_listPays->isChecked() && (depositCount != 0)) {
        deposits = new double[depositCount];
        setArray(ui->tableWidget, deposits, depositCount);
    } else depositCount = 0;


    if (ui->checkBox_Withdrawals->isChecked() && (withdrawalCount != 0)) {
        withdrawals = new double[withdrawalCount];
        setArray(ui->tableWidget_Withdrawals, withdrawals, withdrawalCount);
    } else withdrawalCount = 0;


    if(checkCorrect(initialAmountStr) && checkCorrect(depositTermMonthsStr)
            && checkCorrect(annualInterestRateStr) && checkCorrect(taxRateStr)
            && checkCorrect(payoutPeriodicityStr)) {
        DepositResult result = {0};        

        result.initialAmount = initialAmountStr.toDouble();
        result.depositTermMonths = depositTermMonthsStr.toDouble();
        result.annualInterestRate = annualInterestRateStr.toDouble();
        result.taxRate = taxRateStr.toDouble();
        result.payoutPeriodicity = getperiod(payoutPeriodicityStr);
        result.interestCapitalization  = interestCapitalization;

        if(result.payoutPeriodicity != -1) {
            double initAmount = result.initialAmount;
        
            if(deposits)
                result.deposits = s21_sumArray(deposits, depositCount);
            if(withdrawals)
                result.withdrawals = s21_sumArray(withdrawals, withdrawalCount);

             long double total_earned = get_total_earned(&result, result.payoutPeriodicity);
             long double tax_amount = get_tax_amount(total_earned, result.taxRate);
             long double total_amount = get_total_amount(initAmount, total_earned, tax_amount);

            ui->label_totalDeposit->setText(QString::number(total_amount, 'g', 7));
            ui->label_totalInterest->setText(QString::number(total_earned, 'g', 7));
            ui->label_totalTax->setText(QString::number(tax_amount, 'g', 7));
        }
        delete[] deposits;
        delete[] withdrawals;

    } else {
        QMessageBox::critical(nullptr, "Ошибка", "Не правильно заполнены поля!");
        ui->label_totalDeposit->setText("");
        ui->label_totalInterest->setText("");
        ui->label_totalTax->setText("");
    }
}


void depositcalc::on_pushButton_addPays_clicked()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    QDoubleValidator* validator = new QDoubleValidator(0.0, std::numeric_limits<double>::max(), 6, this);

    // Создаем QLineEdit для ячейки ввода и устанавливаем валидатор
    QLineEdit* lineEdit = new QLineEdit();
    lineEdit->setValidator(validator);

    // Устанавливаем QLineEdit в ячейку таблицы
    ui->tableWidget->setCellWidget(row, 0, lineEdit);
}


void depositcalc::on_pushButton_addWithdrawals_clicked()
{
    int row = ui->tableWidget_Withdrawals->rowCount();
    ui->tableWidget_Withdrawals->insertRow(row);

    QDoubleValidator *validator = new QDoubleValidator(0.0, std::numeric_limits<double>::max(), 6, this);

    // Создаем QLineEdit для ячейки ввода и устанавливаем валидатор
    QLineEdit* lineEdit = new QLineEdit();
    lineEdit->setValidator(validator);

    // Устанавливаем QLineEdit в ячейку таблицы
    ui->tableWidget_Withdrawals->setCellWidget(row, 0, lineEdit);
}


void depositcalc::on_checkBox_listPays_clicked()
{
    if(ui->checkBox_listPays->isChecked()) {
        ui->tableWidget->setEnabled(true);
        ui->pushButton_addPays->setEnabled(true);
        ui->pushButton_removePays->setEnabled(true);
    } else {
        ui->pushButton_addPays->setEnabled(false);
        ui->tableWidget->setEnabled(false);
        ui->pushButton_removePays->setEnabled(false);
    }
}


void depositcalc::on_checkBox_Withdrawals_clicked()
{
    if(ui->checkBox_Withdrawals->isChecked()) {
        ui->tableWidget_Withdrawals->setEnabled(true);
        ui->pushButton_addWithdrawals->setEnabled(true);
        ui->pushButton_removeWithdrawals->setEnabled(true);
    } else {
        ui->tableWidget_Withdrawals->setEnabled(false);
        ui->pushButton_addWithdrawals->setEnabled(false);
        ui->pushButton_removeWithdrawals->setEnabled(false);
    }
}


void depositcalc::on_pushButton_removePays_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->rowCount() - 1);
}


void depositcalc::on_pushButton_removeWithdrawals_clicked()
{
    ui->tableWidget_Withdrawals->removeRow(ui->tableWidget_Withdrawals->rowCount() - 1);
}

