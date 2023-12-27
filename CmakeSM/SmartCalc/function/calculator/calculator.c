#include "calculator.h"
#include "../struct.h" // Этот путь включает заголовочный файл smart_calc.h
#include "../stack/stack.h"

double s21_calc(char *input, const int inputX) {
  int code = 1;
  double result = 0;

  if (!input || strlen(input) == 0 || !s21_validator(input))
    code = -1;
  else {
    s21_stack *main = NULL;
    main = s21_getStackFromStr(input, main);
    if (s21_checkX(main)) {
      s21_replacingXforValue(main, inputX);
    }
    // s21_printStack(main);
    main = s21_getStackOnPolishNotation(main);
    // s21_printStack(main);
    result = s21_NewCalculator(main);

    // if (main)
      s21_clearStack(main);
  }
  return code == 1 ? result : NAN;
}