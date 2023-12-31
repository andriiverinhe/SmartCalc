#include "../s21_smartCalc.h"
#include "maintest.h"
#include <check.h>
#include <unistd.h>

START_TEST (test_1) {
    char * input = "1 + 2";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, 3.0, ACCURECY);
}
END_TEST
START_TEST (test_2) {
    char * input = "1 - 2";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, -1.0, ACCURECY);
}
END_TEST
START_TEST (test_3) {
    char * input = "1 * 2";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, 2.0, ACCURECY);
}
END_TEST
START_TEST (test_4) {
    char * input = "2/1";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, 2.0, ACCURECY);
}
END_TEST
START_TEST (test_5) {
    char * input = "1 ^ 2";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, 1.0, ACCURECY);
}
END_TEST
START_TEST (test_6) {
    char * input = "sin(1)";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, sin(1), ACCURECY);
}
END_TEST
START_TEST (test_7) {
    char * input = "cos(1)";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, cos(1), ACCURECY);
}
END_TEST
START_TEST (test_8) {
    char * input = "tan(1)";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, tan(1), ACCURECY);
}
END_TEST
START_TEST (test_9) {
    char * input = "asin(1)";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, asin(1), ACCURECY);
}
END_TEST
START_TEST (test_10) {
    char * input = "acos(1)";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res,acos(1), ACCURECY);
}
END_TEST
START_TEST (test_11) {
    char * input = "atan(1)";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res,atan(1), ACCURECY);
}
END_TEST
START_TEST (test_12) {
    char * input = "ln(1)";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res,log(1), ACCURECY);
}
END_TEST
START_TEST (test_13) {
    char * input = "log(1)";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, log10(1), ACCURECY);
}
END_TEST
START_TEST (test_14) {
    char * input = "sqrt(1)";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res,sqrt(1), ACCURECY);
}
END_TEST
START_TEST (test_15) {
    char * input = "1%2";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, fmod(1, 2), ACCURECY);
}
END_TEST
START_TEST (test_16) {
    char * input = "-1";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, -1.0, ACCURECY);
}
END_TEST
START_TEST (test_17) {
    char * input = "1+2-(-1+2)+3-4*5";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res,1+2-(-1+2)+3-4*5, ACCURECY);
}
END_TEST

START_TEST (test_18) {
    char * input = "-1^2";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, -1, ACCURECY);
}
START_TEST (test_19) {
    char * input = "+1-(+1)";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, +1-(+1), ACCURECY);
}
START_TEST (test_20) {
    char * input = "1+x";
    double x = 1;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, 2, ACCURECY);
}
START_TEST (test_21) {
    char * input = "1^(-2)";
    double x = 1;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, pow(1,-2), ACCURECY);
}
START_TEST (test_22) {
    char * input = "1^(+2)";
    double x = 1;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, pow(1,-2), ACCURECY);
}
END_TEST

START_TEST (test_23) {
    ck_assert_double_eq_tol(s21_operations(2,2,-1), 0.0, ACCURECY);
}

END_TEST
START_TEST (test_24) {
    char * input = "1+2.2";
    double x = 1;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, 1+2.2, ACCURECY);
}
END_TEST
START_TEST (test_25) {
    char * input = "1+2.2.2";
    double x = 1;
    double res = s21_calc(input, x);
    ck_assert_double_nan(res);
}
END_TEST
START_TEST (test_26) {
    char * input = "cos(1)";
    double x = 0;
    double res = s21_calc(input, x);
    ck_assert_double_eq_tol(res, cos(1), ACCURECY);
}
END_TEST
START_TEST (test_27) {
    s21_stack *main = NULL;
    main = s21_push(main, 10, "", 0);
    s21_stack *cp = s21_copyStack(main);

    ck_assert_double_eq_tol(main->number, cp->number, ACCURECY);


    s21_clearStack(main);
    s21_clearStack(cp);
}
END_TEST
START_TEST (test_28) {
    s21_stack *main = NULL;
    main = s21_push(main, 0 , "", 0);
    ck_assert_ptr_nonnull(main->sign);

    s21_clearStack(main);
}
END_TEST

START_TEST (test_29) {
    double arr[5] = {1.0,2.0,3.0,4.0,5.0};
    ck_assert_double_eq_tol(s21_sumArray(arr, 5), 15.0, ACCURECY);

}
END_TEST

START_TEST (test_30) {
    s21_stack *main = NULL;
    main = s21_push(main, 0 , "", 0);
    s21_stack *cp = s21_copyStack(main); 
    ck_assert_ptr_nonnull(cp->sign);


    s21_clearStack(cp);
    s21_clearStack(main);
}
END_TEST
START_TEST (test_31) {
    double res = s21_calc(NULL, 0);
    ck_assert_double_nan(res);
    res = s21_calc("", 0);
    ck_assert_double_nan(res);

}
END_TEST



Suite *s21_testCalc(void) {
    Suite *s = suite_create("TEST SMART CALC");
    TCase *tc = tcase_create("Case Smart Calc");

    tcase_add_test(tc, test_1);
    tcase_add_test(tc, test_2);
    tcase_add_test(tc, test_3);
    tcase_add_test(tc, test_4);
    tcase_add_test(tc, test_5);
    tcase_add_test(tc, test_6);
    tcase_add_test(tc, test_7);
    tcase_add_test(tc, test_8);
    tcase_add_test(tc, test_9);
    tcase_add_test(tc, test_10);
    tcase_add_test(tc, test_11);
    tcase_add_test(tc, test_12);
    tcase_add_test(tc, test_13);
    tcase_add_test(tc, test_14);
    tcase_add_test(tc, test_15);
    tcase_add_test(tc, test_16);
    tcase_add_test(tc, test_17);
    tcase_add_test(tc, test_18);
    tcase_add_test(tc, test_19);
    tcase_add_test(tc, test_20);
    tcase_add_test(tc, test_21);
    tcase_add_test(tc, test_22);
    tcase_add_test(tc, test_23);
    tcase_add_test(tc, test_24);
    tcase_add_test(tc, test_25);
    tcase_add_test(tc, test_26);
    tcase_add_test(tc, test_27);
    tcase_add_test(tc, test_28);
    tcase_add_test(tc, test_29);
    tcase_add_test(tc, test_30);
    tcase_add_test(tc, test_31);
    

    suite_add_tcase(s, tc);
    return s;
}