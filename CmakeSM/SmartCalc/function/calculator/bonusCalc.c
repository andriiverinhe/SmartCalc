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

long double get_tax_amount(long double total_amount, long double tax_rate) {
  return total_amount * tax_rate / 100;
}

long double get_total_amount(long double deposit_amount,
                             long double earned_money, long double tax_amount) {
  return deposit_amount + earned_money - tax_amount;
}

long double get_total_earned(DepositResult *deposit, int MODE) {
  long double earned_money_amount = 0;
  int period = MODE == 1 ? 12 : 1;
//   replenishments = MODE == 1 ? replenishments : replenishments * 12;
//   withdraws = MODE == 1 ? withdraws : withdraws * 12;

  for (int i = 0; (double)i < deposit->depositTermMonths; i++) {
    long double cumulative_earnings = 0;
    if (MODE == 1) {
      cumulative_earnings = deposit->initialAmount * deposit->annualInterestRate / 100 / period;
    }
    if (MODE == 2) {
      if (i % 11 == 0 && i != 0) {
        cumulative_earnings = deposit->initialAmount * deposit->annualInterestRate / 100 / period;
      }
    }
    deposit->initialAmount += deposit->deposits;
    deposit->initialAmount -= deposit->withdrawals;
    if (deposit->interestCapitalization) {
      deposit->initialAmount += cumulative_earnings;
    }
    earned_money_amount += cumulative_earnings;
  }

  return earned_money_amount;
}