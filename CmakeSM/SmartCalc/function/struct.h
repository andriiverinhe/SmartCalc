#pragma once
#include <stdbool.h>

typedef struct s21_stack {
    double number;
    char *sign;
    int priority;

    struct s21_stack *next;
} s21_stack;

typedef enum {
    Monthly,
    Annually,
    Err
} Periodicity;


typedef struct {
    double initialAmount;
    int depositTermMonths;
    double annualInterestRate;
    double taxRate;
    int payoutPeriodicity;
    bool interestCapitalization;
    double deposits;
    double withdrawals;

    double totalDeposit;
    double totalInterest;
    double totalTax;
} DepositResult;

// initialAmount == сумма вклада
// depositTermMonths == срок вклада 
// annualInterestRate == процентная ставка
// taxRate == налог
// payoutPeriodicity == выплаты (частота выплат ежедневно , еженедельно, раз в месяц, раз в пол года, раз в год)
// interestCapitalization == капитализация 
// deposits == сумма вкладов
// withdrawals == сумма снятий
            