#include "calc.h"

// int main (int argc, char **argv) {
//     int error_mark = 0;
//     if (argc > 1) {
//         error_mark = check_string(argv[1]);
//     }
//     printf("ERRROR %d\n", error_mark);
//     if (!error_mark) {
//         double res = 0;
//         element *stack = {0};
//         element *result = {0};
//         parser(argv[1], &stack);
//         // printf("%s\n", argv[1]);
//         // printf("AAAAA%f\n", stack->value);
//         reverse_stack(&stack, &result);
//         // printf("AAAAA%f\n", result->value);
//         res = r_polish_notation(&result);
//         printf("RESULT %lf\n", res);
//         // while (result != NULL) {
//         //     printf("STACK value %lf\nPRIORITY %d\nTYPE %d\n\n",
//         // result->value, result->priority, result->type);
//         //     remove_element(&result);
//         // }
//     }
//     // free(stack);
//     return 0;
// }

// element *parcer_plus_reverse_stack(char **argv) {
//     element *result = {0};
//     element *stack = {0};
//     parser(argv[1], &stack);
//     reverse_stack(&stack, &result);
//     return result;
// }

double r_polish_notation(element **stack) {
  double result = 0;
  element *numbers = {0};
  element *support = {0};
  while ((*stack) != NULL) {
    if ((*stack)->priority == 0) {
      push(&numbers, (*stack)->value, (*stack)->priority, (*stack)->type);
    } else if ((*stack)->type != 19 && support == NULL) {
      push(&support, (*stack)->value, (*stack)->priority, (*stack)->type);
    } else if ((*stack)->type != 19 &&
               ((*stack)->priority > support->priority ||
                support->type == 18)) {
      push(&support, (*stack)->value, (*stack)->priority, (*stack)->type);
    } else if ((*stack)->type != 19 &&
               (*stack)->priority <= support->priority && support->type != 18) {
      while ((*stack)->priority <= support->priority && support->type != 18) {
        push(&numbers, support->value, support->priority, support->type);
        remove_element(&support);
        if (support == NULL || (*stack == NULL)) {
          break;
        }
      }
      push(&support, (*stack)->value, (*stack)->priority, (*stack)->type);
    } else if ((*stack)->type == 19) {
      while (support->type != 18) {
        push(&numbers, support->value, support->priority, support->type);
        remove_element(&support);
      }
      remove_element(&support);
    }
    remove_element(stack);
  }
  while (support != NULL) {
    push(&numbers, support->value, support->priority, support->type);
    remove_element(&support);
  }
  reverse_stack(&numbers, stack);
  result = calculate(stack);
  // printf("AAA");
  // while (numbers != NULL) {
  //             printf("STACK value %lf\nPRIORITY %d\nTYPE %d\n\n",
  //             numbers->value, numbers->priority, numbers->type);
  //             remove_element(&numbers);
  //         }
  // printf("_______________________\n");
  // while (support != NULL) {
  //     printf("STACK value %lf\nPRIORITY %d\nTYPE %d\n\n", support->value,
  //     support->priority, support->type); remove_element(&support);
  // }
  // reverse_stack(&numbers, stack);
  return result;
}

double calculate(element **stack) {
  double result = 0.0;
  element *support = {0};
  while (*(stack) != 0) {
    while ((*stack)->priority == 0) {
      push(&support, (*stack)->value, (*stack)->priority, (*stack)->type);
      remove_element(stack);
    }
    if ((*stack)->type == X) {
      push(&support, (*stack)->value, (*stack)->type, (*stack)->priority);
      double tmp;
      tmp = support->value;
      remove_element(&support);
      support->value += tmp;
    } else if ((*stack)->type == PLUS) {
      double tmp;
      tmp = support->value;
      remove_element(&support);
      support->value += tmp;
    } else if ((*stack)->type == MINUS) {
      double tmp;
      tmp = support->value;
      remove_element(&support);
      support->value -= tmp;
    } else if ((*stack)->type == MUL) {
      double tmp;
      tmp = support->value;
      remove_element(&support);
      support->value *= tmp;
    } else if ((*stack)->type == DIV) {
      double tmp;
      tmp = support->value;
      remove_element(&support);
      support->value /= tmp;
    } else if ((*stack)->type == MOD) {
      double tmp;
      tmp = support->value;
      remove_element(&support);
      support->value = fmod(support->value, tmp);
    } else if ((*stack)->type == EXP) {
      double tmp;
      tmp = support->value;
      remove_element(&support);
      support->value = pow(support->value, tmp);
    } else if ((*stack)->type == COS) {
      support->value = cos(support->value);
    } else if ((*stack)->type == SIN) {
      support->value = sin(support->value);
    } else if ((*stack)->type == TAN) {
      support->value = tan(support->value);
    } else if ((*stack)->type == ACOS) {
      support->value = acos(support->value);
    } else if ((*stack)->type == ASIN) {
      support->value = asin(support->value);
    } else if ((*stack)->type == ATAN) {
      support->value = atan(support->value);
    } else if ((*stack)->type == SQRT) {
      support->value = sqrt(support->value);
    } else if ((*stack)->type == LN) {
      support->value = log(support->value);
    } else if ((*stack)->type == LOG) {
      support->value = log10(support->value);
    }
    result = support->value;
    if (*stack != NULL) {
      remove_element(stack);
    }
  }
  remove_element(&support);
  return result;
}

void set_x_value(double value, element *final) {
  element *lexeme_buffer = final;

  while (lexeme_buffer) {
    if (lexeme_buffer->type == X) {
      lexeme_buffer->value = value;
    }
    lexeme_buffer = lexeme_buffer->next;
  }
}

void parser(char *argv, element **stack) {
  char number_string[] = "1234567890.";
  char function_string[] = "sctalxp(";
  int length = strlen(argv);
  int length_buffer = 257;  // buffer
  // printf("CCCCCCC%s\n", argv);
  for (int i = 0; i < length; i++) {
    // printf("AAAAA%c\n", argv[i]);
    if ((strchr(number_string, argv[i]) && argv[i] != '\0')) {
      int cnt = 0;
      char buffer[length_buffer];
      while (strchr(number_string, argv[i]) && argv[i] != '\0') {
        buffer[cnt] = argv[i];
        cnt++;
        i++;
      }
      buffer[cnt] = '\0';
      // printf("BBBB%s\n", buffer);
      push(stack, atof(buffer), 0, NUM);
      buffer[0] = '\0';
      if (strchr(function_string, argv[i]) && argv[i] != '\0') {
        push(stack, 0.0, 2, MUL);
      }
    }
    if (argv[i] == 'x') {
      push(stack, 0.0, 0, X);
    } else if (argv[i] == 'p') {
      push(stack, 3.14, 0, PI);
    } else if (argv[i] == '(') {
      push(stack, 0.0, 5, BRACK_O);
      if (argv[i + 1] == '-' || argv[i + 1] == '+') {
        push(stack, 0.0, 0, NUM);
      }
    } else if (argv[i] == ')') {
      push(stack, 0.0, 5, BRACK_C);
      if (strchr(function_string, argv[i + 1]) && argv[i + 1] != '\0') {
        push(stack, 0.0, 2, MUL);
      }
    } else if (argv[i] == '+') {
      if (!i) {
        push(stack, 0.0, 0, NUM);
      }
      push(stack, 0.0, 1, PLUS);
    } else if (argv[i] == '-') {
      if (!i) {
        push(stack, 0.0, 0, NUM);
      }
      push(stack, 0.0, 1, MINUS);
    } else if (argv[i] == '*') {
      push(stack, 0.0, 2, MUL);
    } else if (argv[i] == '/') {
      push(stack, 0.0, 2, DIV);
    } else if (argv[i] == 'm') {
      push(stack, 0.0, 2, MOD);
      i += 2;
    } else if (argv[i] == '^') {
      push(stack, 0.0, 3, EXP);
    } else if (argv[i] == 's') {
      if (argv[i + 1] == 'i') {
        push(stack, 0.0, 4, SIN);
        i += 2;
      }
      if (argv[i + 1] == 'q') {
        push(stack, 0.0, 4, SQRT);
        i += 3;
      }
    } else if (argv[i] == 'c') {
      push(stack, 0.0, 4, COS);
      i += 2;
    } else if (argv[i] == 't') {
      push(stack, 0.0, 4, TAN);
      i += 2;
    } else if (argv[i] == 'a') {
      if (argv[i + 1] == 's') {
        push(stack, 0.0, 4, ASIN);
      }
      if (argv[i + 1] == 'c') {
        push(stack, 0.0, 4, ACOS);
      }
      if (argv[i + 1] == 't') {
        push(stack, 0.0, 4, ATAN);
      }
      i += 3;
    } else if (argv[i] == 'l') {
      if (argv[i + 1] == 'o') {
        push(stack, 0.0, 4, LOG);
        i += 2;
      }
      if (argv[i + 1] == 'n') {
        push(stack, 0.0, 4, LN);
        i++;
      }
    }
  }
}

void push(element **head, double value, int priority, type_t type) {
  element *tmp = (element *)malloc(sizeof(element));
  tmp->value = value;
  tmp->priority = priority;
  tmp->type = type;
  tmp->next = *head;
  *head = tmp;
}

void remove_element(element **head) {
  element *prev = NULL;
  if (head != NULL) {
    prev = *head;
    *head = (*head)->next;
    free(prev);
  }
}

void reverse_stack(element **stack, element **result) {
  while ((*stack) != NULL) {
    // printf("AAAAA%f\n", (*stack)->value);
    push(result, (*stack)->value, (*stack)->priority, (*stack)->type);
    remove_element(stack);
  }
}

int check_string(char *argv) {
  int error_mark = 0;
  int length = strlen(argv);
  char number_string[] = "1234567890x.";
  char sign_string[] = "+-*/^";
  char x[] = "x";
  char function_string[] = "sctalmp";
  char check_legal[] = "odins)(";
  for (int i = 0; i < length - 1; i++) {
    if (!strchr(number_string, argv[i]) && !strchr(sign_string, argv[i]) &&
        !strchr(x, argv[i]) && !strchr(function_string, argv[i]) &&
        !strchr(check_legal, argv[i])) {  // check for non-legal simbol
      error_mark = 1;
    }
  }
  for (int i = 0; i < length; i++) {
    if (argv[i] == '(') {
      error_mark = brackets_check(argv);
      break;
    }
  }
  if (strchr(sign_string, argv[length - 1])) {
    error_mark = 1;
  } else {
    for (int i = 0; i < length; i++) {
      if (strchr(sign_string, argv[i]) &&
          (strchr(sign_string, argv[i + 1]) || argv[i + 1] == '.')) {
        error_mark = 1;
      }
      if (argv[i] == '.' &&
          (!strchr(number_string, argv[i + 1]) || argv[i + 1] == '.' ||
           argv[i + 1] == 'x' || argv[i + 1] == '\0')) {
        error_mark = 1;
      }
      if (argv[i] == 'x' && strchr(number_string, argv[i + 1]) &&
          argv[i + 1] != '\0') {
        error_mark = 1;
      }
      // if(!strchr(number_string, argv[i])
      //     && !strchr(sign_string, argv[i]) && !strchr(x, argv[i])
      //     && !strchr(function_string, argv[i])) {  // check for non-legal
      //     simbol error_mark = 1;
      // }
    }
  }
  if (!error_mark) {
    for (int i = 0; i < length; i++) {
      if (strchr(number_string, argv[i]) == NULL &&
          strchr(sign_string, argv[i]) == NULL && argv[i] != ')' &&
          argv[i] != '(' && strchr(function_string, argv[i])) {
        error_mark = function_check(argv, &i);
        if (error_mark) {
          break;
        }
      }
    }
  }
  if (!error_mark) {
    for (int i = 0; i < length; i++) {
      if (strchr(x, argv[i])) {
        error_mark = 2;
        break;
      }
    }
  }
  return error_mark;
}

int function_check(char *argv, int *index) {
  int error_mark = 0;
  int length = strlen(argv);
  int sinus_mark = 0;
  int sqrt_mark = 0;
  int asinus_mark = 0;
  int acosinus_mark = 0;
  int atan_mark = 0;
  int log_mark = 0;
  int start_index = *index;
  if (argv[start_index] == 's' && start_index < length) {
    if (argv[start_index + 1] == 'i') {
      sinus_mark = sinus_check(argv, start_index + 2);
      if (!sinus_mark) {
        *index = start_index + 3;
      }
    } else if (argv[*index + 1] == 'q') {
      sqrt_mark = sqrt_check(argv, start_index + 2);
      if (!sqrt_mark) {
        *index = start_index + 4;
      }
    } else {
      error_mark = 1;
    }
    if (!error_mark && (sinus_mark ^ sqrt_mark)) {
      error_mark = 1;
    }
  } else if (argv[start_index] == 'c' && start_index < length) {
    error_mark = cosinus_check(argv, start_index + 1);
    if (!error_mark) {
      *index = start_index + 3;
    }
  } else if (argv[start_index] == 't' && start_index < length) {
    error_mark = tan_check(argv, start_index + 1);
    if (!error_mark) {
      *index = start_index + 3;
    }
  } else if (argv[start_index] == 'a' && start_index < length) {
    if (argv[start_index + 1] == 's' && argv[start_index + 2] == 'i') {
      asinus_mark = sinus_check(argv, start_index + 3);
      if (!asinus_mark) {
        *index = start_index + 4;
      }
    } else if (argv[start_index + 1] == 'c') {
      acosinus_mark = cosinus_check(argv, start_index + 2);
      if (!acosinus_mark) {
        *index = start_index + 4;
      }
    } else if (argv[start_index + 1] == 't') {
      atan_mark = tan_check(argv, start_index + 2);
      if (!atan_mark) {
        *index = start_index + 4;
      }
    } else {
      error_mark = 1;
    }
    if (!error_mark && (asinus_mark ^ acosinus_mark ^ atan_mark)) {
      error_mark = 1;
    }
  } else if (argv[start_index] == 'l' && start_index < length) {
    if (argv[start_index + 1] == 'o') {
      log_mark = log_check(argv, start_index + 2);
      if (!log_mark) {
        *index = start_index + 3;
      }
    } else if (argv[*index + 1] == 'n') {
      *index = start_index + 2;
      error_mark = in_brackets_check(argv, *index);
    } else {
      error_mark = 1;
    }
  } else if (argv[start_index] == 'm' && start_index < length) {
    error_mark = mod_check(argv, start_index + 1);
    if (!error_mark) {
      *index = start_index + 3;
    }
  } else if (argv[start_index] == 'p' && start_index < length) {
    if (argv[start_index + 1] != 'i') {
      error_mark = 1;
    }
    if (!error_mark) {
      *index = start_index + 2;
    }
  } else {
    error_mark = 1;
  }
  return error_mark;
}

int brackets_check(char *argv) {
  int error_mark = 0;
  int cnt1 = 0;
  int cnt2 = 0;
  char sign_string[] = "+-*/^";
  int length = strlen(argv);
  for (int i = 0; i < length; i++) {
    if (argv[i] == '(') {
      cnt1++;
      if (cnt2 > cnt1) {
        error_mark = 1;
      }
    }
    if (argv[i] == ')') {
      cnt2++;
      if (i > 0) {
        if (strchr(sign_string, argv[i - 1])) {
          error_mark = 1;
        }
      }
    }
  }
  if (cnt1 != cnt2) {
    error_mark = 1;
  }
  return error_mark;
}

int in_brackets_check(char *argv, int index) {
  int error_mark = 0;
  char number_string[] = "1234567890x.";
  char sign_string[] = "+-*/^";
  char function_string[] = "sctalm";
  if (argv[index] != '(') {
    error_mark = 1;
  }
  if (!error_mark) {
    if (index != '\0') {
      index++;
    }
    if (strchr(number_string, argv[index]) ||
        strchr(sign_string, argv[index]) ||
        strchr(function_string, argv[index]) || argv[index] == '(') {
      while (strchr(number_string, argv[index]) ||
             strchr(sign_string, argv[index]) ||
             strchr(function_string, argv[index]) || argv[index] == '(') {
        if (strchr(function_string, argv[index])) {
          error_mark = function_check(argv, &index);
        } else {
          index++;
        }
      }
    } else {
      error_mark = 1;
    }
    if (strchr(sign_string, argv[index - 1])) {
      error_mark = 1;
    }
    if (argv[index] != ')') {
      error_mark = 1;
    }
    if (argv[index] == '\0') {
      error_mark = 1;
    }
  }
  return error_mark;
}

int sinus_check(char *argv, int index) {
  int error_mark = 0;
  if (argv[index] != 'n') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  error_mark = in_brackets_check(argv, index);
  return error_mark;
}

int sqrt_check(char *argv, int index) {
  int error_mark = 0;
  if (argv[index] != 'r') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  if (argv[index] != 't') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  error_mark = in_brackets_check(argv, index);
  return error_mark;
}

int cosinus_check(char *argv, int index) {
  int error_mark = 0;
  if (argv[index] != 'o') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  if (argv[index] != 's') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  if (!error_mark) {
    error_mark = in_brackets_check(argv, index);
  }
  return error_mark;
}

int tan_check(char *argv, int index) {
  int error_mark = 0;
  if (argv[index] != 'a') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  if (argv[index] != 'n') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  error_mark = in_brackets_check(argv, index);
  return error_mark;
}

int log_check(char *argv, int index) {
  int error_mark = 0;
  if (argv[index] != 'g') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  error_mark = in_brackets_check(argv, index);
  return error_mark;
}

int mod_check(char *argv, int index) {
  int error_mark = 0;
  char sign_string[] = "+-*/^.";
  if (index == 1) {
    error_mark = 1;
  } else if (strchr(sign_string, argv[index - 2])) {
    error_mark = 1;
  }
  if (argv[index] != 'o') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  if (argv[index] != 'd') {
    error_mark = 1;
  }
  if (index != '\0') {
    index++;
  }
  if (strchr(sign_string, argv[index])) {
    error_mark = 1;
  }
  return error_mark;
}

// result credit_res(double sum, int time, double percent, int mode) {
//   result res = {0};
//   double i = percent / 12 / 100;
//   if (!mode) {
//     double k = i / (pow(1 + i, time) - 1);
//     res.monthly_payment_max = sum * (i + k);
//     res.all_payment = res.monthly_payment_max * 12 * time;
//     res.overpayment = res.all_payment - sum;
//     //res.monthly_payment_max = sum * (k * time - 1);
//   } else {
//     double main = sum / time;
//     res.monthly_payment_max = main + sum * i;
//     res.monthly_payment_min = main + main * i;
//     res.overpayment = i * sum * (time + 1) / 2.;
//     res.all_payment = res.overpayment + sum;
//   }
//   return res;
// }

result credit_res(double sum, int time, double percent, int mode) {
  result res = {0};
  double i = percent / 12 / 100;
  time *= 12;
  // printf("i = %f\n", i);
  if (!mode) {
    double k = i / (1 - pow(1 + i, -time));
    // double g = pow(1 + i, time);
    // printf("g = %f\n", g);
    // double v = g - 1;
    // printf("v = %f\n", v);
    // double k = i / v;
    // printf("k = %f\n", k);
    res.monthly_payment_max = k * sum;
    res.all_payment = k * sum * time;
    res.overpayment = sum * (k * time - 1);
    // res.monthly_payment_max = sum * (k * time - 1);
  } else {
    double main = sum / time;
    res.monthly_payment_max = main + sum * i;
    res.monthly_payment_min = main + main * i;
    res.overpayment = i * sum * (time + 1) / 2.;
    res.all_payment = res.overpayment + sum;
  }
  return res;
}

deposit_output calc_deposit(deposit_input deposit_input) {
  deposit_output res = {0};
  deposit_input.term_in_months *= 12;
  double time_day = deposit_input.term_in_months * 30;
  double time_quater = deposit_input.term_in_months / 4;
  double percent = deposit_input.interest_rate / 100;
  // double end_deposit;
  if (!deposit_input.is_capitalization) {
    if (!deposit_input.add_day) {
      // long double tmp = 1 + percent / 365;
      res.end_deposit = deposit_input.amount * pow(1 + percent / 365, time_day);
      // res.end_deposit = 1 + 2 * (-4);
      res.accrued_interest = res.end_deposit - deposit_input.amount;
      res.tax_amount = res.accrued_interest *
                       (deposit_input.tax_rate - deposit_input.tax_rate / 2) /
                       100;
      // int time = 0;
      // while(time != time_day) {
      //     if (time_day >= 365)  {
      //         int tmp_time = 365;
      //         res.end_deposit += deposit_input.amount * pow(1 + percent/365,
      //         tmp_time); res.tax_amount += (res.end_deposit -
      //         deposit_input.amount - 80000) * 0.13; time_day -= 365;
      //     } else {
      //         res.end_deposit += deposit_input.amount * pow(1 + percent/365,
      //         time_day); res.tax_amount += (res.end_deposit -
      //         deposit_input.amount - 80000) * 0.13;
      //     }
      // }
    }
    if (!deposit_input.add_month) {
      double tmp = percent / 12;
      res.end_deposit =
          deposit_input.amount * (pow(1 + tmp, deposit_input.term_in_months));
      // printf("res dep = %f\n", res.end_deposit);
      res.accrued_interest = res.end_deposit - deposit_input.amount;
      res.tax_amount = res.accrued_interest * (deposit_input.tax_rate / 100);
    }
    if (!deposit_input.add_quater) {
      res.end_deposit =
          deposit_input.amount * pow(1 + percent / 4, time_quater);
      res.accrued_interest = res.end_deposit - deposit_input.amount;
      res.tax_amount = res.accrued_interest * (deposit_input.tax_rate / 100);
    }
  } else {
    res.end_deposit = (deposit_input.amount * percent * (time_day / 365));
    res.accrued_interest = res.end_deposit - deposit_input.amount;
    res.tax_amount = res.accrued_interest * (deposit_input.tax_rate / 100);
  }
  return res;
}

void free_stack(element *pHead) {
  element *pNode = pHead, *pNext;

  while (NULL != pNode) {
    pNext = pNode->next;
    free(pNode);
    pNode = pNext;
  }
}

size_t s21_strlcpy(char *dst, const char *src, size_t maxlen) {
  const size_t srclen = strlen(src);
  if (srclen + 1 < maxlen) {
    memcpy(dst, src, srclen + 1);
  } else if (maxlen != 0) {
    memcpy(dst, src, maxlen - 1);
    dst[maxlen - 1] = '\0';
  }
  return srclen;
}