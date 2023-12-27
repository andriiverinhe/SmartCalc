#pragma once
#define ACCURECY 0.0000001

#include <check.h>

void run_tests();
void run_test_case(Suite *ptr_test);
Suite *s21_testCalc(void);
Suite *s21_testBonusCalc(void);
Suite *s21_testParser(void);