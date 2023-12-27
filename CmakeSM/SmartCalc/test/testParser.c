#include "../s21_smartCalc.h"
#include "maintest.h"
#include <check.h>
#include <unistd.h>

START_TEST (test_1) {
    char *str = "()2)";
    int code = s21_validator(str);
    ck_assert_int_eq(code, 0);
}
END_TEST
START_TEST (test_2) {
    char *str = "())()";
    int code = s21_validator(str);
    ck_assert_int_eq(code, 0);
}
END_TEST
START_TEST (test_3) {
    char *str = "1+-2";
    int code = s21_validator(str);
    ck_assert_int_eq(code, 0);
}
END_TEST
START_TEST (test_4) {
    char *str = "con(1)";
    int code = s21_validator(str);
    ck_assert_int_eq(code, 0);
}
END_TEST
START_TEST (test_5) {
    char *str = "(*2)";
    int code = s21_validator(str);
    ck_assert_int_eq(code, 0);
}
END_TEST
START_TEST (test_6) {
    char *str = "k";
    int code = s21_validator(str);
    ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST (test_7) {
    char *str = "(-5)";
    int code = s21_validator(str);
    ck_assert_int_eq(code, 1);
}
END_TEST


Suite *s21_testParser(void) {
    Suite *s = suite_create("TEST PARSER");
    TCase *tc = tcase_create("Case PARSER");
    
    tcase_add_test(tc, test_1);
    tcase_add_test(tc, test_2);
    tcase_add_test(tc, test_3);
    tcase_add_test(tc, test_4);
    tcase_add_test(tc, test_5);
    tcase_add_test(tc, test_6);
    tcase_add_test(tc, test_7);
    suite_add_tcase(s, tc);
    return s;
}