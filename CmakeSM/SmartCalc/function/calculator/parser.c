#include "calculator.h"

int s21_isBalanced(char *str) {
  int stack_size = 0;
  int str_len = strlen(str);
  char stack[str_len];

  for (int i = 0; i < str_len; i++) {
    if (str[i] == '(') {
      stack[stack_size] = '(';
      stack_size++;
    } else if (str[i] == ')') {
      if (stack_size == 0 || stack[stack_size - 1] != '(') {
        return 0; // Нарушен порядок
      }
      stack_size--;
    }
  }

  return stack_size == 0; // Если стек пуст, то скобки сбалансированы
}

int s21_checkDigit(char *str, int *index) {
  int codeDOT = 0;
  int code = 1;
  size_t i = 0;
  for (; (i < strlen(str)) && (isdigit(str[i]) || str[i] == '.') && code == 1;
       i++) {
    if (str[i] == '.' && codeDOT == 0)
      codeDOT = 1;
    else if (str[i] == '.' && codeDOT == 1)
      code = 0;
  }
  if(i == 0) {
      if (str[i] == 'x') {
        code = 1;
        i++;
      }
  }

  *index += --i;
  return code;
}

int s21_checkSing(char *str, int *index) {
  const char *sign = "+-*/^%%";
  int code = 1;
  int codeSIGN = 0;
  size_t i = 0;

  for (; i < strlen(str); i++) {
    for (int j = 0; j < 6; j++) {
      if (str[i] == sign[j])
        codeSIGN++;
    }
    if ( str[i] == 'c' || str[i] == 's' || str[i] == 'a' ||
        str[i] == 't' || str[i] == '(' || str[i] == 'l' || str[i] == 'x' ||
        isdigit(str[i]))
      break;
    if(str[i] == '^' &&(str[i+1] == '-' || str[i+1] == '+')) {
      code = -1;
      i++;
      // printf("12\n");
      break;
    }
  }
  if (codeSIGN != 1 && code != -1)
    code = 0;
  *(index) += --i;
  return code;
}

int s21_checkFunc(char *str, int *index) {
  const char *func[] = {"sin",  "cos", "tan", "asin", "acos",
                        "atan", "log", "ln", "sqrt"};
  // const char *sign = "+-*/^";
  int code = 1;
  int codeFUNC = 0;

  char buff[256] = "\0";
  strcpy(buff, str);
  size_t j = 0;
  for (; j < strlen(buff); j++) {
    if (buff[j] == ' ' || buff[j] == '(' || isdigit(buff[j])) {
      buff[j] = '\0';
      break;
    };
  }

  for (int i = 0; i < 9 && codeFUNC == 0; i++) {
    if (strcmp(buff, func[i]) == 0)
      codeFUNC = 1;
  }
  if (!codeFUNC)
    code = 0;
  *index += (strlen(buff)) - 1;
  return code;
}

int s21_validator(char *str) {
  int code = 1, codeFUNC = 0, codeSIGN = 0, codeDIG = 0;
  int codeBracketL = 0, codeBracketR = 0;
  if (!s21_isBalanced(str))
    code = 0;
  for (int i = 0; i < (int)strlen(str) && code; i++) {
    // printf("string: %s\n", str+i);
    if (str[i] == ' ')
      continue;

    if ((isdigit(str[i]) || str[i] == 'x') && !codeDIG && !codeBracketR) {
      codeDIG = s21_checkDigit((str + i), &i);

      codeSIGN = 0;
      codeFUNC = 0;
      codeBracketL = 0;
      // printf("code DIG: %d\n", codeDIG);
    } else if (((!codeSIGN && (str[i] == '+' || str[i] == '-' || str[i] == '*' ||
                             str[i] == '/' || str[i] == '^' || str[i] == '%')) || codeSIGN == -1) && (i != 0 || ((i == 0 && str[i] == '+' )||(i == 0 && str[i] == '-')))) {


      if (codeBracketL && (str[i] != '+' && str[i] != '-'))
        code = 0;
      else {
        codeSIGN = s21_checkSing((str + i), &i);
        codeDIG = 0;
        codeFUNC = 0;
        codeBracketR = 0;
      }
      // printf("code SIGN: %d\n", codeSIGN);
    } else if (!codeBracketR && !codeFUNC && !codeDIG &&
               (str[i] == 's' || str[i] == 'c' || str[i] == 't' ||
                str[i] == 'a' || str[i] == 'l' ||
                str[i] == 's')) {
      codeFUNC = s21_checkFunc((str + i), &i);
      codeDIG = 0;
      codeSIGN = 0;
      codeBracketL = 0;
      // printf("code FUNC: %d\n", codeFUNC);

    } else if (str[i] == '(' &&
               ((codeFUNC || codeSIGN || codeBracketL) ||
                (codeFUNC == 0 || codeSIGN == 0 || codeDIG == 0))) {
      codeBracketL = 1;
      codeFUNC = 0;
      codeSIGN = 0;
      // printf("code BRACKET LEFT: %d\n", codeBracketL);

    } else if (str[i] == ')' && (codeDIG || codeBracketR)) {
      codeBracketR = 1;
      codeDIG = 0;
      // printf("code BRACKET RIGHT: %d\n", codeBracketR);
    } else
      code = 0;

    if (codeSIGN == 0 && codeFUNC == 0 && codeDIG == 0 && codeBracketL == 0 &&
        codeBracketR == 0)
      code = 0;
    // printf("code i: %d\n", i);
  }
  if(codeFUNC || codeSIGN || codeBracketL) code = 0;
  return code;
}
