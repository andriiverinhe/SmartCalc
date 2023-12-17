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
    double totalDeposit;
    double totalInterest;
    double totalTax;
} DepositResult;