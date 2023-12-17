#pragma once

typedef struct s21_stack {
    double number;
    char *sign;
    int priority;

    struct s21_stack *next;
} s21_stack;

typedef enum {
    Daily,
    Weekly,
    Monthly,
    SemiAnnually,
    Annually,
    Err
} Periodicity;

typedef struct {
    // double initialAmount;
    // int depositTermMonths;
    // double annualInterestRate;
    // double taxRate;

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

    double totalDeposit;
    double totalInterest;
    double totalTax;
} DepositResult;