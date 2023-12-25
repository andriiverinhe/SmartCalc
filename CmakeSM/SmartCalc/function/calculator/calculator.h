#pragma once

#include "../struct.h" // Включение общего заголовка

// Объявления функций и структур, связанных с модулем calculator

#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
  NUMBER = 0,
  SUBSUM = 1,
  MULDIV = 2,
  SINCOS = 4,
  POWER = 3,
  BRACKET = 5,
} CodePriority;

typedef enum {
  PLUS = 0,
  MINUS = 1,

  MUL = 2,
  DIV = 3,
  MOD = 4,

  POW = 5,

  SIN = 6,
  COS = 7,
  TAN = 8,

  ASIN = 9,
  ACOS = 10,
  ATAN = 11,

  LOG = 12,
  LN = 13,

  SQRT = 14,

  UNARYMINUS = 15,
} lexema;

// CALCULATORS
double s21_calc(char *input, const int inputX);
double s21_calcGraph(char *input, double *coordinate, const int size);
void s21_calculateDifferentiatedPayment(double loanAmount, double annualInterestRate, int loanTermMonths, double *resTotal, double *resMonthly);
void s21_calculateAnnuityPayment(double loanAmount, double annualInterestRate, int loanTermMonths, double *result);

long double get_tax_amount(long double total_amount, long double tax_rate);
long double get_total_amount(long double deposit_amount,
                             long double earned_money, long double tax_amount);
long double get_total_earned(DepositResult *deposit, int MODE);
// HELPERS
double s21_NewCalculator(s21_stack *st);
void s21_getNumber(const char *input, char *num);
void s21_getSign(const char *input, char *sign);
s21_stack *s21_getStackFromStr(const char *input, s21_stack *main);
int s21_getPriority(char *sign);
s21_stack *s21_getStackOnPolishNotation(s21_stack *main);
double s21_sumArray(double *arr, int count);

// void s21_printStrFromStack(s21_stack *st);
// PARESER
int s21_validator(char *str);
// Replace X
int s21_checkX(s21_stack *st);
void s21_replacingXforValue(s21_stack *main, const double value);

