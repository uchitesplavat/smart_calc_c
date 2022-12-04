#ifndef CALC_CALC_H
#define CALC_CALC_H
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum type_t {
  NUM = 1,
  X = 2,
  PLUS = 3,
  MINUS = 4,
  MUL = 5,
  DIV = 6,
  MOD = 7,
  EXP = 8,
  COS = 9,
  SIN = 10,
  TAN = 11,
  ACOS = 12,
  ASIN = 13,
  ATAN = 14,
  SQRT = 15,
  LN = 16,
  LOG = 17,
  BRACK_O = 18,
  BRACK_C = 19,
  PI = 20
} type_t;

typedef struct element {
  double value;
  int priority;
  struct element *next;
  type_t type;
} element;

// credit

typedef struct result {
  long monthly_payment_max;
  long monthly_payment_min;
  long overpayment;
  long all_payment;
} result;

// deposit

typedef struct deposit_input {
  double amount;
  double term_in_months;
  double interest_rate;
  double tax_rate;
  int add_day;
  int add_month;
  int add_quater;
  int with_every_n_month;
  int is_capitalization;
} deposit_input;

typedef struct deposit_output {
  double accrued_interest;
  double tax_amount;
  double end_deposit;
} deposit_output;

/******CHECK_STRING*********/
int check_string(char *argv);
int function_check(char *argv, int *index);
int brackets_check(char *argv);
int in_brackets_check(char *argv, int index);
int sinus_check(char *argv, int index);
int sqrt_check(char *argv, int index);
int cosinus_check(char *argv, int index);
int tan_check(char *argv, int index);
int log_check(char *argv, int index);
int mod_check(char *argv, int index);

/********PARSER***********/
void parser(char *argv, element **stack);
void push(element **head, double value, int priority, type_t type);
void reverse_stack(element **stack, element **result);
void remove_element(element **head);

/********POLISH_NOTATION***********/
double r_polish_notation(element **stack);
double calculate(element **stack);

/********GRAPH********/
void graph(double x, double y, element **stack);
void set_x_value(double value, element *final);

/********CREDIT********/
result credit_res(double sum, int time, double percent, int mode);
/********DEPOSIT********/
deposit_output calc_deposit(deposit_input deposit_input);

/********HELP********/
size_t s21_strlcpy(char *dst, const char *src, size_t maxlen);
void free_stack(element *pHead);

#endif  // CALC_CALC_H_
