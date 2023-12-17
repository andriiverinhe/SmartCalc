#include "calculator.h"

// Функция для вычисления ежемесячного платежа по аннуитетному плану
void s21_calculateAnnuityPayment(double loanAmount, double annualInterestRate, int loanTermMonths, double *result) {
    double monthlyInterestRate = annualInterestRate / 12 / 100;
    double numerator = loanAmount * monthlyInterestRate;
    double denominator = 1 - pow(1 + monthlyInterestRate, -loanTermMonths);
    double monthlyPayment = numerator / denominator;
    double totalPayment = monthlyPayment * loanTermMonths;
    double overpayment = totalPayment - loanAmount;

    result[0] = monthlyPayment;
    result[1] = totalPayment;
    result[2] = overpayment;
}

// Функция для вычисления дифференцированного ежемесячного платежа
double s21_calculateDiff(double loanAmount, double annualInterestRate, int loanTermMonths, int currentMonth) {
    double monthlyInterestRate = annualInterestRate / 12 / 100;
    return (loanAmount / loanTermMonths) + (loanAmount - (loanAmount / loanTermMonths) * currentMonth) * monthlyInterestRate;
}

void s21_calculateDifferentiatedPayment(double loanAmount, double annualInterestRate, int loanTermMonths, double *resTotal, double *resMonthly) {
    double totalPayment = 0;
        // Вывод ежемесячных платежей и накопленной суммы
        for (int month = 0; month < loanTermMonths; ++month) {
            double monthlyPayment = s21_calculateDiff(loanAmount, annualInterestRate, loanTermMonths, month);
            totalPayment += monthlyPayment;
            resMonthly[month] = monthlyPayment;
        }
        double overpayment = totalPayment - loanAmount;

        resTotal[0] = totalPayment;
        resTotal[1] = overpayment;
}

DepositResult s21_calculateDeposit(double initialAmount, int depositTermMonths, double annualInterestRate,
                               double taxRate, Periodicity payoutPeriodicity, int interestCapitalization,
                               const double* deposits, const double* withdrawals, int depositCount, int withdrawalCount) {
    double principal = initialAmount;
    double totalInterest = 0.0;
    double totalTax = 0.0;

    int payoutFrequency = 1; // Once per term by default
    switch (payoutPeriodicity) {
        case Daily:
            payoutFrequency = 365;
            break;
        case Weekly:
            payoutFrequency = 52;
            break;
        case Monthly:
            payoutFrequency = 12;
            break;
        case SemiAnnually:
            payoutFrequency = 2;
            break;
        case Annually:
            payoutFrequency = 1;
            break;
        case Err:
            // Handle error
            break;
    }

    int totalPeriods = payoutFrequency * depositTermMonths;
    double monthlyInterestRate = annualInterestRate / payoutFrequency / 100.0;

    // Сначала добавляем суммы вкладов
    double totalDeposits = 0.0;
    for (int i = 0; i < depositCount; ++i) {
        totalDeposits += deposits[i];
    }

    // Затем добавляем их к основной сумме
    principal += totalDeposits;

    for (int period = 1; period <= totalPeriods; ++period) {
        if (interestCapitalization) {
            principal *= (1 + monthlyInterestRate);
        }

        if (period % payoutFrequency == 0) {
            // Calculate interest and apply tax
            double interest = principal * monthlyInterestRate * payoutFrequency;
            double taxedInterest = interest * (1 - taxRate);
            totalInterest += taxedInterest;
            totalTax += interest - taxedInterest;
        }
    }
    // В конце вычитаем сумму снятий
    double totalWithdrawals = 0.0;
    for (int i = 0; i < withdrawalCount; ++i) {
        totalWithdrawals += withdrawals[i];
    }

    principal -= totalWithdrawals;

    DepositResult result;
    result.totalDeposit = principal + totalInterest;
    result.totalInterest = totalInterest;
    result.totalTax = totalTax;

    return result;
}
