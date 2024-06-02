#include "matrix_test.h"

START_TEST(sum_matrix_test_1) {
  int rows = 10, columns = 10;
  matrix_t A = {0}, B = {0}, check = {0};

  create_matrix(rows, columns, &A);
  create_matrix(rows, columns, &B);
  create_matrix(rows, columns, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = get_random_value(MIN_VALUE, MAX_VALUE);
      B.matrix[i][j] = get_random_value(MIN_VALUE, MAX_VALUE);
      check.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
    }
  }

  matrix_t result = {0};

  ck_assert_int_eq(sum_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(eq_matrix(&check, &result), SUCCESS);

  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&check);
  remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_test_2) {
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

  ck_assert_int_eq(sum_matrix(&A, &B, &result), CALCULATION_ERROR);

  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_test_3) {
  int rows = -3, columns = -3;
  matrix_t A = {0}, B = {0}, result = {0};

  create_matrix(rows, columns, &A);
  create_matrix(rows, columns, &B);

  ck_assert_int_eq(sum_matrix(&A, &B, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(sum_matrix_test_4) {
  int rows = 4, columns = 2;
  matrix_t A = {0}, B = {0}, expected = {0};

  create_matrix(rows, columns, &A);
  A.matrix[0][0] = 3;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;
  A.matrix[2][0] = 5.5;
  A.matrix[2][1] = 7;
  A.matrix[3][0] = 11;
  A.matrix[3][1] = 0.3;

  create_matrix(rows, columns, &B);
  B.matrix[0][0] = -9;
  B.matrix[0][1] = 0;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 3;
  B.matrix[2][0] = 3.5;
  B.matrix[2][1] = 1;
  B.matrix[3][0] = 4.9;
  B.matrix[3][1] = 0.123;

  create_matrix(rows, columns, &expected);
  expected.matrix[0][0] = -6;
  expected.matrix[0][1] = 4;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = 5;
  expected.matrix[2][0] = 9;
  expected.matrix[2][1] = 8;
  expected.matrix[3][0] = 15.9;
  expected.matrix[3][1] = 0.423;

  matrix_t result = {0};

  ck_assert_int_eq(sum_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(eq_matrix(&expected, &result), SUCCESS);

  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

Suite *sum_matrix_suite() {
  Suite *s;
  s = suite_create("\033[33msum_matrix_tests\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("sum_matrix_core");
  tcase_add_test(tc_core, sum_matrix_test_1);
  tcase_add_test(tc_core, sum_matrix_test_2);
  tcase_add_test(tc_core, sum_matrix_test_3);
  tcase_add_test(tc_core, sum_matrix_test_4);

  suite_add_tcase(s, tc_core);

  return s;
}