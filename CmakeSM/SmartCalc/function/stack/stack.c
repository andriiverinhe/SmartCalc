#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"
#include "../struct.h"

s21_stack *s21_push(s21_stack *top, double number, const char *sign,
                    int priority) {
  s21_stack *new_node =
      (s21_stack *)malloc(sizeof(s21_stack)); // Выделение памяти под новый узел

  // if (new_node == NULL) {
  //   // Обработка ошибки: не удалось выделить память
  //   // Можно выбрасывать исключение или вернуть NULL
  //   return NULL;
  // }
  s21_setValueStack(number, sign, priority, new_node);
  new_node->next = top; // Новый узел указывает на предыдущий top
  return new_node; // Возвращаем указатель на новый узел как новую вершину стека
}

s21_stack *s21_pop(s21_stack *top) {
  // if (top == NULL) {
  //   fprintf(stderr, "Стек пуст, невозможно выполнить операцию pop.\n");
  //   return NULL;
  // }
  s21_stack *temp = top;
  top = top->next; // Обновляем top на предыдущий элемент
  if (temp) {
    if (temp->sign)
      free(temp->sign); // Освобождаем память, выделенную под строку
    free(temp); // Освобождаем память, выделенную под узел
  }

  return top; // Возвращаем обновленную вершину стека
}

void s21_clearStack(s21_stack *top) {
  while (top != NULL) {
    top = s21_pop(top);
  }
}

s21_stack *s21_reverseStack(s21_stack *top) {
  s21_stack *reversedTop =
      NULL; // Создаем новый стек для перевернутых элементов

  while (top != NULL) {
    s21_stack *temp = top;
    top = top->next; // Удаляем верхний элемент из исходного стека
    temp->next = reversedTop; // Добавляем этот элемент в перевернутый стек
    reversedTop = temp; // Обновляем вершину перевернутого стека
  }

  return reversedTop; // Возвращаем перевернутый стек
}


s21_stack *s21_copyStack(const s21_stack *original_top) {
    s21_stack *copied_top = NULL;  // Инициализируем новый стек

    // Итерируемся по исходному стеку и добавляем элементы в новый стек
    const s21_stack *current_original = original_top;
    while (current_original != NULL) {
        // Создаем новый элемент для нового стека
        s21_stack *new_node = (s21_stack *)malloc(sizeof(s21_stack));

        // if (new_node == NULL) {
        //     // Обработка ошибки: не удалось выделить память
        //     s21_clearStack(copied_top);  // Очищаем уже скопированные элементы
        //     return NULL;
        // }

        // Копируем значения из текущего элемента исходного стека в новый элемент
        new_node->number = current_original->number;
        if (current_original->sign != NULL) {

            new_node->sign = malloc(strlen(current_original->sign) + 1);
            strcpy(new_node->sign, current_original->sign);
            // new_node->sign = strdup(current_original->sign);
            // if (new_node->sign == NULL) {
            //     // Обработка ошибки: не удалось выделить память для строки
            //     free(new_node);
            //     s21_clearStack(copied_top);  // Очищаем уже скопированные элементы
            //     return NULL;
            // }
        } else {
            new_node->sign = NULL;
        }
        new_node->priority = current_original->priority;

        // Добавляем новый элемент в вершину нового стека
        new_node->next = copied_top;
        copied_top = new_node;

        // Переходим к следующему элементу исходного стека
        current_original = current_original->next;
    }

    // Переворачиваем новый стек, чтобы порядок элементов был таким же, как в исходном стеке
    copied_top = s21_reverseStack(copied_top);

    return copied_top;
}
