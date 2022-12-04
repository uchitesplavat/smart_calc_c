#include <check.h>

#include "calc.h"

#ifdef NAN
/* NAN is supported */
#endif
#ifdef INFINITY
/* INFINITY is supported */
#endif

// START_TEST(set_number_test) {
//     element *head = NULL;
//     char *buffer = "123.304303";
//     set_number(&buffer, &head);

//     printf("%lf\n", head->value);
//     printf("%d\n", head->type);
//     printf("%d\n", head->priority);

//     free_stack(head);
// }

// END_TEST

START_TEST(check_expression_test) {
  ck_assert_int_eq(check_string("123\30430b3"), 1);
  ck_assert_int_eq(check_string("x+1"), 2);
  ck_assert_int_eq(check_string("123.123+1-24"), 0);
  ck_assert_int_eq(check_string("sin(5+1*(-4))+atan(-1/7.25^(-3))"), 0);
  ck_assert_int_eq(check_string("sin(5+1*(-4))+acos(-1/7.25^(-3))"), 0);
  ck_assert_int_eq(
      check_string(
          "sin(2)*cos(5)+tan(67^2)/sin(128)-atan(sqrt(9))-(4mod2)*log(5)"),
      0);
}

END_TEST

// START_TEST(parse_test) {
//     element *final = NULL;
//     element *buffer = NULL;

//     parse_string("-5.0+2.0/10.0", &final, &buffer);

//     print_stack(final);

//     print_stack(buffer);

//     free_stack(final);
//     free_stack(buffer);

//     printf("\n");
// }

// END_TEST

// START_TEST(parse_test2) {
//     element *final = NULL;
//     element *buffer = NULL;
//     parse_string("3+4*2/(1-5)^2", &final, &buffer);

//     print_stack(final);

//     print_stack(buffer);

//     free_stack(final);
//     free_stack(buffer);
// }

// END_TEST

START_TEST(calc_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("3+4*2/(1-5)^2", &stack);
  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);

  ck_assert_double_eq(result, 3.5);

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc2_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("3+(-3)", &stack);
  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);

  ck_assert_double_eq(result, 0);

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc3_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("3mod5", &stack);
  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);

  ck_assert_double_eq(result, fmod(3, 5));

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc4_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("ln(-4+5)+5", &stack);
  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);

  ck_assert_double_eq(result, log10(-4 + 5) + 5);

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc5_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("sin(5+1*(-4))", &stack);
  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);

  ck_assert_double_eq(result, sin(5 + 1 * (-4)));

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc6_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("sin(5+1*(-4))+atan(-1/7.25^(-3))", &stack);
  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);

  ck_assert_double_eq(result, sin(5 + 1 * (-4)) + atan(-1 / pow(7.25, -3)));

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc7_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("sin(5+1*(-4))+4*(-1/(7.25^(-3)))", &stack);
  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);

  ck_assert_double_eq(result, sin(5 + 1 * (-4)) + 4 * (-1 / pow(7.25, -3)));
  // printf("result 7 === %f", result);
  // printf("result comp === %f", sin(5 + 1 * (-4)) + 4 * (-1 / pow(7.25, -3)));
  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc8_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("sin(2)*cos(5)+tan(67^2)/sin(128)-atan(sqrt(9))-(4mod2)*log(5)",
         &stack);
  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);

  ck_assert_double_eq(result, sin(2) * cos(5) + tan(67 * 67) / sin(128) -
                                  atan(sqrt(9)) - 0 * log(5));

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc9_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("asin(0.6)", &stack);
  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);

  ck_assert_double_eq(result, asin(0.6));

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc10_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("acos(0.6)", &stack);
  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);

  ck_assert_double_eq(result, acos(0.6));

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc11_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("acos(0)-sin(30)*tan(67)/sin(128)-atan(sqrt(9))-(4mod2)*log(5)+(54-7)",
         &stack);
  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);

  ck_assert_double_eq(result, acos(0) - sin(30) * tan(67) / sin(128) -
                                  atan(sqrt(9)) - 0 * log(5) + (54 - 7));

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc12_test_nan) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("acos(1.2)-sin(30)*tan(67)/sin(128)-atan(sqrt(9))-(4mod2)*log(5)",
         &stack);
  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);
  double a = NAN;
  ck_assert_double_eq(isnan(a), isnan(acos(1.2) - sin(30) * tan(67) / sin(128) -
                                      atan(sqrt(9)) - 0 * log(5)));
  ck_assert_double_eq(isnan(result), isnan(a));

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc13_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("10+8.91*7-9/3+4-98", &stack);

  reverse_stack(&stack, &resultat);

  double result = r_polish_notation(&resultat);
  ck_assert_double_eq(result, 10.0 + 8.91 * 7.0 - 9.0 / 3.0 + 4.0 - 98.0);

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc14_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("21*3*(8+(45/12)+1/2+(-21))-4/7", &stack);

  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);
  ck_assert_double_eq(
      result,
      21.0 * 3.0 * (8.0 + (45.0 / 12.0) + 1.0 / 2.0 + (-21.0)) - 4.0 / 7.0);

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc15_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("13/(2+(3*4)/7)", &stack);

  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);
  ck_assert_double_eq(result, 13.0 / (2.0 + (3.0 * 4.0) / 7.0));

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc16_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("2.5+(3.4*4.3)/7.2", &stack);

  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);
  ck_assert_double_eq(result, 2.5 + (3.4 * 4.3) / 7.2);

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc17_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("sin(5+1*(-4)) + tan(-1/7.25^(-3))", &stack);

  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);
  ck_assert_double_eq(result, sin(5 + 1 * (-4)) + tan(-1 / pow(7.25, -3)));

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(calc18_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("(21*3*(8+(45/12)+1/2+(-21))-4/7)(sin(5+1*(-4)) + tan(-1/7.25^(-3)))",
         &stack);

  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);
  ck_assert_double_eq(
      result,
      (21.0 * 3.0 * (8.0 + (45.0 / 12.0) + 1.0 / 2.0 + (-21.0)) - 4.0 / 7.0) *
          (sin(5 + 1 * (-4)) + tan(-1 / pow(7.25, -3))));

  free(stack);
  free(resultat);
}

END_TEST

START_TEST(prepare_graph_test) {
  element *stack = NULL;
  element *resultat = NULL;

  parser("x+1", &stack);
  set_x_value(12.1, stack);
  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);
  set_x_value(12.1, stack);

  ck_assert_double_eq(result, 13.1);

  parser("x+1", &stack);
  set_x_value(13.1, stack);
  reverse_stack(&stack, &resultat);
  result = r_polish_notation(&resultat);

  ck_assert_double_eq(result, 14.1);

  double i = 0;
  while (i < 100000) {
    parser("3*(x+1)+x", &stack);
    set_x_value(i, stack);
    reverse_stack(&stack, &resultat);
    result = r_polish_notation(&resultat);
    ck_assert_double_eq(result, 3 * (i + 1) + i);
    i += 0.379;
  }

  i = 0;
  while (i < 100000) {
    parser("(21*3*(8+(45/12)+1/x+(-21))-4/7)(sin(5+1*(x)) + tan(-1/7.25^(x)))",
           &stack);
    set_x_value(i, stack);
    reverse_stack(&stack, &resultat);
    result = r_polish_notation(&resultat);
    ck_assert_double_eq(
        result,
        (21.0 * 3.0 * (8.0 + (45.0 / 12.0) + 1.0 / i + (-21.0)) - 4.0 / 7.0) *
            (sin(5 + 1 * (i)) + tan(-1 / pow(7.25, i))));
    i += 0.379;
  }

  i = -3;
  while (i > -100000) {
    // printf("i = %f\n", i);
    parser("(21*3*(8+(x/12)+1/x+(-21))-4/7)(sin(5+1*(x)) + tan(-1/7.25^(-3)))",
           &stack);
    set_x_value(i, stack);
    reverse_stack(&stack, &resultat);
    result = r_polish_notation(&resultat);
    ck_assert_double_eq(
        result,
        (21.0 * 3.0 * (8.0 + (i / 12.0) + 1.0 / i + (-21.0)) - 4.0 / 7.0) *
            (sin(5.0 + 1.0 * (i)) + tan(-1 / pow(7.25, -3))));
    i -= 0.379768;
  }

  i = -90000.9876;
  while (i < 100000) {
    // printf("i = %f\n", i);
    parser("(21*3*(8+(x/12)+1/x+(-21))-4/7)(sin(5+1*(x)) + tan(-1/7.25^(-3)))",
           &stack);
    set_x_value(i, stack);
    reverse_stack(&stack, &resultat);
    result = r_polish_notation(&resultat);
    ck_assert_double_eq(
        result,
        (21.0 * 3.0 * (8.0 + (i / 12.0) + 1.0 / i + (-21.0)) - 4.0 / 7.0) *
            (sin(5.0 + 1.0 * (i)) + tan(-1 / pow(7.25, -3))));
    i += 0.379768;
  }
}

END_TEST

// START_TEST(prepare_graph_test_rand) {
//   element *stack = NULL;
//   element *resultat = NULL;
//   int d = (int)&d;
//   printf("d = %d\n", d);
//   parser("(21*3*(8+(x/12)+1/x+(-21))-4/7)(sin(5+1*(x)) + tan(-1/7.25^(-3)))",
//   &stack); set_x_value(d, stack); reverse_stack(&stack, &resultat); double
//   result = r_polish_notation(&resultat); ck_assert_double_eq(result,
//   (21.0*3.0*(8.0+(d/12.0)+1.0/d+(-21.0))-4.0/7.0)*(sin(5.0+1.0*(d)) +
//   tan(-1/pow(7.25,-3)))); free(stack); free(resultat);

// }

// END_TEST

START_TEST(credit_test_annuity) {
  result res = {0};
  double sum = 1000000;
  int time = 3;
  double percent = 15;
  int mode = 0;

  res = credit_res(sum, time, percent, mode);

  ck_assert_int_eq(res.monthly_payment_max, 34665);
  ck_assert_int_eq(res.monthly_payment_min, 0);
  ck_assert_int_eq(res.overpayment, 247951);
  ck_assert_int_eq(res.all_payment, 1247951);
}

END_TEST

START_TEST(credit_test_diff) {
  result res = {0};
  double sum = 1000000;
  int time = 3;
  double percent = 15;
  int mode = 1;

  res = credit_res(sum, time, percent, mode);

  ck_assert_int_eq(res.monthly_payment_max, 40277);
  ck_assert_int_eq(res.monthly_payment_min, 28125);
  ck_assert_int_eq(res.overpayment, 231250);
  ck_assert_int_eq(res.all_payment, 1231250);
}

END_TEST

// START_TEST(deposit_test_month_without_cap) {
//     deposit_output res = {0};
//     deposit_input input = {0};
//     input.amount = 1500000;
//     input.term_in_months = 3;
//     input.interest_rate = 15;
//     input.tax_rate = 13;
//     input.add_day = 1;
//     input.add_month = 0;
//     input.add_quater = 1;
//     input.is_capitalization = 1;
//     res = calc_deposit(input);

//     ck_assert_double_eq(res.accrued_interest, 589220);
//     ck_assert_double_eq(res.tax_amount, 76598.62054);
//     ck_assert_double_eq(res.end_deposit, 2089220.158);

// }

// END_TEST

int main() {
  Suite *s1 = suite_create("s21_SmartCalc: ");
  TCase *tc1_1 = tcase_create("s21_SmartCalc: ");
  SRunner *sr = srunner_create(s1);
  int result;
  suite_add_tcase(s1, tc1_1);

  // tcase_add_test(tc1_1, set_number_test);
  tcase_add_test(tc1_1, check_expression_test);

  // tcase_add_test(tc1_1, parse_test);
  // tcase_add_test(tc1_1, parse_test2);
  tcase_add_test(tc1_1, calc_test);
  tcase_add_test(tc1_1, calc2_test);
  tcase_add_test(tc1_1, calc3_test);
  tcase_add_test(tc1_1, calc4_test);
  tcase_add_test(tc1_1, calc5_test);
  tcase_add_test(tc1_1, calc6_test);
  tcase_add_test(tc1_1, calc7_test);
  tcase_add_test(tc1_1, calc8_test);
  tcase_add_test(tc1_1, calc9_test);
  tcase_add_test(tc1_1, calc10_test);
  tcase_add_test(tc1_1, calc11_test);
  tcase_add_test(tc1_1, calc12_test_nan);
  tcase_add_test(tc1_1, calc13_test);
  tcase_add_test(tc1_1, calc14_test);
  tcase_add_test(tc1_1, calc15_test);
  tcase_add_test(tc1_1, calc16_test);
  tcase_add_test(tc1_1, calc17_test);
  tcase_add_test(tc1_1, calc18_test);
  tcase_add_test(tc1_1, prepare_graph_test);
  tcase_add_test(tc1_1, credit_test_annuity);
  tcase_add_test(tc1_1, credit_test_diff);
  // for (int i = 0; i < 100000; i++) {
  // tcase_add_test(tc1_1, prepare_graph_test_rand);
  // }

  // tcase_add_test(tc1_1, deposit_test_month_without_cap);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result == 0 ? 0 : 1;
}