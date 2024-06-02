#include "matrix_test.h"

START_TEST(eq_matrix_test_1) {
  int rows = 10, columns = 10;
  matrix_t A = {0}, B = {0};

  create_matrix(rows, columns, &A);
  create_matrix(rows, columns, &B);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double value = get_random_value(MIN_VALUE, MAX_VALUE);
      A.matrix[i][j] = value;
      B.matrix[i][j] = value;
    }
  }

  ck_assert_int_eq(eq_matrix(&A, &B), SUCCESS);

  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_2) {
  int rows = 10, columns = 10;
  matrix_t A = {0}, B = {0};

  create_matrix(rows, columns, &A);
  create_matrix(rows, columns, &B);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = get_random_value(MIN_VALUE, MAX_VALUE);
      B.matrix[i][j] = get_random_value(MIN_VALUE, MAX_VALUE);
    }
  }

  ck_assert_int_eq(eq_matrix(&A, &B), FAILURE);

  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_3) {
  int rows_1 = 10, columns_1 = 5;
  int rows_2 = 5, columns_2 = 10;
  matrix_t A = {0}, B = {0};

  create_matrix(rows_1, columns_1, &A);
  for (int i = 0; i < rows_1; i++) {
    for (int j = 0; j < columns_1; j++) {
      A.matrix[i][j] = get_random_value(MIN_VALUE, MAX_VALUE);
    }
  }

  create_matrix(rows_2, columns_2, &B);
  for (int i = 0; i < rows_2; i++) {
    for (int j = 0; j < columns_2; j++) {
      B.matrix[i][j] = get_random_value(MIN_VALUE, MAX_VALUE);
    }
  }

  ck_assert_int_eq(eq_matrix(&A, &B), FAILURE);

  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_4) {
  int rows_1 = 3, columns_1 = 3;
  int rows_2 = -3, columns_2 = -3;
  matrix_t A = {0}, B = {0};

  create_matrix(rows_1, columns_1, &A);
  create_matrix(rows_2, columns_2, &B);

  ck_assert_int_eq(eq_matrix(&A, &B), FAILURE);

  remove_matrix(&A);
}
END_TEST

START_TEST(eq_matrix_test_6) {
  matrix_t A = {0}, B = {0};

  create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.00000000234;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3.05;
  A.matrix[1][1] = 4;

  create_matrix(2, 2, &B);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3.05;
  B.matrix[1][1] = 4;

  ck_assert_int_eq(eq_matrix(&A, &B), SUCCESS);

  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_7) {
  matrix_t A = {0}, B = {0};

  create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0001;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3.05;
  A.matrix[1][1] = 4;

  create_matrix(2, 2, &B);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3.05;
  B.matrix[1][1] = 4;

  ck_assert_int_eq(eq_matrix(&A, &B), FAILURE);

  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

Suite *eq_matrix_suite() {
  Suite *s;
  s = suite_create("\033[33meq_matrix_tests\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("eq_matrix_core");
  tcase_add_test(tc_core, eq_matrix_test_1);
  tcase_add_test(tc_core, eq_matrix_test_2);
  tcase_add_test(tc_core, eq_matrix_test_3);
  tcase_add_test(tc_core, eq_matrix_test_4);
  tcase_add_test(tc_core, eq_matrix_test_6);
  tcase_add_test(tc_core, eq_matrix_test_7);

  suite_add_tcase(s, tc_core);

  return s;
}
