#pragma once
#include "../struct.h" 

// MAIN
s21_stack *s21_push(s21_stack *top, double number, const char *sign,
                    int priority);
s21_stack *s21_pop(s21_stack *top);
void s21_clearStack(s21_stack *top);
s21_stack *s21_reverseStack(s21_stack *top);
s21_stack *s21_copyStack(const s21_stack *original_top);
// HELPERS
void s21_setValueStack(const double number, const char *sign,
                       const int priority, s21_stack *st);
void s21_printStack(s21_stack *top);