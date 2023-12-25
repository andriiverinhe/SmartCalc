#include "../s21_smartCalc.h"
#include "maintest.h"
#include <check.h>
#include <unistd.h>
START_TEST(test_1) {
    double loanAmount = 0.0;
    double annualInterestRate = 0.0;
    int loanTermMonths = 0.0;
    double result[3] = {0};
    s21_calculateAnnuityPayment(loanAmount, annualInterestRate, loanTermMonths, result);
    ck_assert_double_eq_tol(result[0], 0.0, ACCURECY);
    ck_assert_double_eq_tol(result[1], 0.0, ACCURECY);
    ck_assert_double_eq_tol(result[2], 0.0, ACCURECY);
}
END_TEST
START_TEST(test_2) {
    double loanAmount = 1.0;
    double annualInterestRate = 1.0;
    int loanTermMonths = 1.0;
    double result[3] = {0};
    s21_calculateAnnuityPayment(loanAmount, annualInterestRate, loanTermMonths, result);
    ck_assert_double_eq_tol(result[0], 1.0008333333334405, ACCURECY);
    ck_assert_double_eq_tol(result[1], 1.0008333333334405, ACCURECY);
    ck_assert_double_eq_tol(result[2], 0.0008333333334405, ACCURECY);
}
END_TEST

START_TEST(test_3) {
    double loanAmount = 0.0;
    double annualInterestRate = 0.0;
    int loanTermMonths = 0.0;
    int currentMonth = 0.0;

    double res = s21_calculateDiff(loanAmount, annualInterestRate, loanTermMonths, currentMonth);
    ck_assert_double_nan(res);
}
END_TEST

START_TEST(test_4) {
    double loanAmount = 1.0;
    double annualInterestRate = 1.0;
    int loanTermMonths = 1.0;
    int currentMonth = 1.0;

    double res = s21_calculateDiff(loanAmount, annualInterestRate, loanTermMonths, currentMonth);
    ck_assert_double_eq_tol(res, 1.0, ACCURECY);
}
END_TEST

START_TEST(test_5) {
    double loanAmount = 1.0;
    double annualInterestRate= 1.0;
    int loanTermMonths = 1;
    double resTotal[2]= {0};
    double resMonthly[1] = {0};
    s21_calculateDifferentiatedPayment(loanAmount, annualInterestRate,loanTermMonths, resTotal, resMonthly);
    ck_assert_double_eq_tol(resMonthly[0], 1.0008333333334405, ACCURECY);
    ck_assert_double_eq_tol(resTotal[0], 1.0008333333334405, ACCURECY);
    ck_assert_double_eq_tol(resTotal[1], 0.0008333333334405, ACCURECY);
}
END_TEST
START_TEST(test_6) {
    long double total_amount = 1;
    long double tax_rate = 1;
    long double deposit_amount = 1;
    long double earned_money = 1;

    long double tax_amount = get_tax_amount(total_amount, tax_rate);

    long double res2 = get_total_amount(deposit_amount, earned_money, tax_amount);
    ck_assert_double_eq_tol(tax_amount, 0.01, ACCURECY);
    ck_assert_double_eq_tol(res2, 1.99, ACCURECY);
}
END_TEST
START_TEST(test_7) {
    DepositResult result = {0};
    result.initialAmount = 1;
    result.depositTermMonths = 1;
    result.annualInterestRate = 1;
    result.taxRate = 0;
    result.payoutPeriodicity = 1;
    result.interestCapitalization = 1;
    
    long double res1 = get_total_earned(&result, 1);
    ck_assert_double_eq_tol(res1, 0.0008333333333333, ACCURECY);
}
END_TEST

START_TEST(test_8) {
    DepositResult result = {0};
    result.initialAmount = 1000;
    result.depositTermMonths = 50;
    result.annualInterestRate = 20;
    result.taxRate = 0;
    result.payoutPeriodicity = 2;
    result.interestCapitalization = 0;
    
    long double res1 = get_total_earned(&result, 2);
    ck_assert_double_eq_tol(res1, 0.0, ACCURECY);
}
END_TEST

Suite *s21_testBonusCalc(void) {
    Suite *s = suite_create("TEST Bonus");
    TCase *tc = tcase_create("Case Bonus");

    tcase_add_test(tc, test_1);
    tcase_add_test(tc, test_2);
    tcase_add_test(tc, test_3);
    tcase_add_test(tc, test_4);
    tcase_add_test(tc, test_5);
    tcase_add_test(tc, test_6);
    tcase_add_test(tc, test_7);
    tcase_add_test(tc, test_8);

    suite_add_tcase(s, tc);
    return s;
}