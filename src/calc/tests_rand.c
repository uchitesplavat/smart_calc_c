#include <check.h>

#include "calc.h"

START_TEST(prepare_graph_test_rand) {
  element *stack = NULL;
  element *resultat = NULL;
  int d = (int)&d;
  printf("d = %d\n", d);
  parser("(21*3*(8+(x/12)+1/x+(-21))-4/7)(sin(5+1*(x)) + tan(-1/7.25^(-3)))",
         &stack);
  set_x_value(d, stack);
  reverse_stack(&stack, &resultat);
  double result = r_polish_notation(&resultat);
  ck_assert_double_eq(
      result,
      (21.0 * 3.0 * (8.0 + (d / 12.0) + 1.0 / d + (-21.0)) - 4.0 / 7.0) *
          (sin(5.0 + 1.0 * (d)) + tan(-1 / pow(7.25, -3))));
  free(stack);
  free(resultat);
}

END_TEST

int main() {
  Suite *s1 = suite_create("s21_SmartCalc: ");
  TCase *tc1_1 = tcase_create("s21_SmartCalc: ");
  SRunner *sr = srunner_create(s1);
  int result;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, prepare_graph_test_rand);

  // tcase_add_test(tc1_1, deposit_test_month_without_cap);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result == 0 ? 0 : 1;
}