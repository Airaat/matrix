#include "matrix_test.h"

START_TEST(mult_number_test_1) {
  int rows = 10, columns = 10;
  matrix_t A = {0}, check = {0};
  double num = get_random_value(MIN_VALUE, MAX_VALUE);

  create_matrix(rows, columns, &A);
  create_matrix(rows, columns, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = get_random_value(MIN_VALUE, MAX_VALUE);
      check.matrix[i][j] = A.matrix[i][j] * num;
    }
  }

  matrix_t result = {0};

  ck_assert_int_eq(mult_number(&A, num, &result), OK);
  ck_assert_int_eq(eq_matrix(&check, &result), SUCCESS);

  remove_matrix(&A);
  remove_matrix(&check);
  remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_test_2) {
  int rows = -3, columns = -3;
  matrix_t A = {0}, check = {0};
  double num = get_random_value(MIN_VALUE, MAX_VALUE);

  create_matrix(rows, columns, &A);
  create_matrix(rows, columns, &check);

  matrix_t result = {0};

  ck_assert_int_eq(mult_number(&A, num, &result), INCORRECT_MATRIX);
}
END_TEST

Suite *mult_number_tests() {
  Suite *s;
  s = suite_create("\033[33mmult_number_tests\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("mult_number_core");
  tcase_add_test(tc_core, mult_number_test_1);
  tcase_add_test(tc_core, mult_number_test_2);

  suite_add_tcase(s, tc_core);

  return s;
}
