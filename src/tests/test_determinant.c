#include "matrix_test.h"

START_TEST(determinant_test_1) {
  int size = 5;
  matrix_t A = {0};

  create_matrix(size, size, &A);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = j;
    }
  }

  double result = 0.0;

  ck_assert_int_eq(determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, 0.0, ACCURACY);

  remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_2) {
  int rows = 3, columns = 4;
  matrix_t A = {0};

  create_matrix(rows, columns, &A);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = i + j;
    }
  }

  double result = 0.0;

  ck_assert_int_eq(determinant(&A, &result), CALCULATION_ERROR);

  remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_3) {
  int size = 1;

  matrix_t A = {0};
  create_matrix(size, size, &A);
  A.matrix[0][0] = 7.0;

  double check = 7.0;
  double result = 0.0;

  ck_assert_int_eq(determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, check, ACCURACY);

  remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_4) {
  matrix_t A = {0};
  double result = 0.0;

  ck_assert_int_eq(determinant(&A, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(determinant_test_5) {
  int size = 2;

  matrix_t A = {0};
  create_matrix(size, size, &A);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 3;

  double check = -2.0;
  double result = 0.0;

  ck_assert_int_eq(determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, check, ACCURACY);

  remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_6) {
  int size = 2;

  matrix_t A = {0};
  create_matrix(size, size, &A);
  A.matrix[0][0] = 4;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 1;

  double check = 0.0;
  double result = 0.0;

  ck_assert_int_eq(determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, check, ACCURACY);

  remove_matrix(&A);
}
END_TEST

Suite *determinant_suite() {
  Suite *s;
  s = suite_create("\033[33mdeterminant_tests\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("determinant_suite");

  tcase_add_test(tc_core, determinant_test_1);
  tcase_add_test(tc_core, determinant_test_2);
  tcase_add_test(tc_core, determinant_test_3);
  tcase_add_test(tc_core, determinant_test_4);
  tcase_add_test(tc_core, determinant_test_5);
  tcase_add_test(tc_core, determinant_test_6);

  suite_add_tcase(s, tc_core);

  return s;
}