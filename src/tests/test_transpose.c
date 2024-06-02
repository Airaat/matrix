#include "matrix_test.h"

START_TEST(transpose_test_1) {
  int rows = 3, columns = 3;
  matrix_t A = {0}, check = {0};

  create_matrix(rows, columns, &A);
  create_matrix(columns, rows, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = i + j;
      check.matrix[j][i] = i + j;
    }
  }

  matrix_t result = {0};

  ck_assert_int_eq(transpose(&A, &result), 0);
  ck_assert_int_eq(eq_matrix(&check, &result), 1);

  remove_matrix(&A);
  remove_matrix(&result);
  remove_matrix(&check);
}
END_TEST

START_TEST(transpose_test_2) {
  int rows = 3, columns = -3;
  matrix_t A = {0};

  create_matrix(rows, columns, &A);

  matrix_t result = {0};

  ck_assert_int_eq(transpose(&A, &result), INCORRECT_MATRIX);
}
END_TEST

Suite *transpose_suite(void) {
  Suite *s;
  s = suite_create("\033[33mtranspose_tests\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("transpose_suite");

  tcase_add_test(tc_core, transpose_test_1);
  tcase_add_test(tc_core, transpose_test_2);

  suite_add_tcase(s, tc_core);

  return s;
}