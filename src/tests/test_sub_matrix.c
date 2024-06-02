#include "matrix_test.h"

START_TEST(sub_matrix_test_1) {
  int rows = 10;
  int columns = 10;
  matrix_t A = {0}, B = {0}, check = {0};

  create_matrix(rows, columns, &A);
  create_matrix(rows, columns, &B);
  create_matrix(rows, columns, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = get_random_value(MIN_VALUE, MAX_VALUE);
      B.matrix[i][j] = get_random_value(MIN_VALUE, MAX_VALUE);
      check.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
    }
  }

  matrix_t result = {0};

  ck_assert_int_eq(sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(eq_matrix(&check, &result), SUCCESS);

  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&check);
  remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_test_2) {
  int rows_1 = 10, columns_1 = 5;
  int rows_2 = 5, columns_2 = 10;

  matrix_t A = {0};
  create_matrix(rows_1, columns_1, &A);
  for (int i = 0; i < rows_1; i++) {
    for (int j = 0; j < columns_1; j++) {
      A.matrix[i][j] = get_random_value(MIN_VALUE, MAX_VALUE);
    }
  }

  matrix_t B = {0};
  create_matrix(rows_2, columns_2, &B);
  for (int i = 0; i < rows_2; i++) {
    for (int j = 0; j < columns_2; j++) {
      B.matrix[i][j] = get_random_value(MIN_VALUE, MAX_VALUE);
    }
  }

  matrix_t result = {0};

  ck_assert_int_eq(sub_matrix(&A, &B, &result), CALCULATION_ERROR);

  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_test_3) {
  int rows = -3, columns = -3;
  matrix_t A = {0}, B = {0}, result = {0};

  create_matrix(rows, columns, &A);
  create_matrix(rows, columns, &B);

  ck_assert_int_eq(sub_matrix(&A, &B, &result), INCORRECT_MATRIX);
}
END_TEST

Suite *sub_matrix_suite() {
  Suite *s;
  s = suite_create("\033[33msub_matrix_tests\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("sub_matrix_core");
  tcase_add_test(tc_core, sub_matrix_test_1);
  tcase_add_test(tc_core, sub_matrix_test_2);
  tcase_add_test(tc_core, sub_matrix_test_3);

  suite_add_tcase(s, tc_core);

  return s;
}