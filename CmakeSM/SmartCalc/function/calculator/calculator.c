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

    if (main)
      s21_clearStack(main);
  }
  return code == 1 ? result : NAN;
}

// 1 - OK
// 0 - NE OK


double s21_calcGraph(char *input, double *coordinate, const int size) {
  int code = 1;
  
  int count = 0;

  if (!input || strlen(input) == 0 || !s21_validator(input))
    code = -1;
  else {
    s21_stack *main = NULL;
    main = s21_getStackFromStr(input, main);
    
    main = s21_getStackOnPolishNotation(main);
    double i = -100;
//    int size = ((200 / 0.1) * 2);
    for(int k = 0; k < (size / 2); i+=0.1, k++) {
    s21_stack *copy = s21_copyStack(main);
    if (s21_checkX(copy)) {
      s21_replacingXforValue(copy, i);
    }
    coordinate[count++] = i;
    coordinate[count++] = s21_NewCalculator(copy);

    if (copy)
      s21_clearStack(copy);
    }
    if (main)
      s21_clearStack(main);
  }
  // for(int i = 0; i < 40;i++) {
  //   printf("%f\n", coordinate[i]);
  // }

  return code == 1 ? (double)code : NAN;
}
