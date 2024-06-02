#include "matrix_test.h"

START_TEST(inverse_matrix_test_1) {
  int size = 3;
  matrix_t A = {0}, expected = {0};

  create_matrix(size, size, &A);
  create_matrix(size, size, &expected);

  A.matrix[0][0] = 2.8;
  A.matrix[0][1] = 1.3;
  A.matrix[0][2] = 7.01;
  A.matrix[1][0] = -1.03;
  A.matrix[1][1] = -2.3;
  A.matrix[1][2] = 3.01;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = -3;
  A.matrix[2][2] = 2;

  expected.matrix[0][0] = 44300.0 / 367429.0;
  expected.matrix[0][1] = -236300.0 / 367429.0;
  expected.matrix[0][2] = 200360.0 / 367429.0;
  expected.matrix[1][0] = 20600.0 / 367429.0;
  expected.matrix[1][1] = 56000.0 / 367429.0;
  expected.matrix[1][2] = -156483.0 / 367429.0;
  expected.matrix[2][0] = 30900.0 / 367429.0;
  expected.matrix[2][1] = 84000.0 / 367429.0;
  expected.matrix[2][2] = -51010.0 / 367429.0;

  matrix_t result = {0};

  ck_assert_int_eq(inverse_matrix(&A, &result), OK);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected.matrix[i][j],
                              ACCURACY);
    }
  }

  remove_matrix(&A);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_test_2) {
  int rows = 3, columns = 1;
  matrix_t A = {0};

  create_matrix(rows, columns, &A);

  matrix_t result = {0};

  ck_assert_int_eq(inverse_matrix(&A, &result), CALCULATION_ERROR);

  remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_test_3) {
  int rows = -2, columns = 2;
  matrix_t A = {0}, result = {0};

  create_matrix(rows, columns, &A);

  ck_assert_int_eq(inverse_matrix(&A, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(null_determinant_test) {
  int size = 3;
  matrix_t A = {0};
  create_matrix(size, size, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  double det_result = 0.0, det_expected = 0.0;
  matrix_t result = {0};

  ck_assert_double_eq_tol(determinant(&A, &det_result), det_expected, ACCURACY);
  ck_assert_int_eq(inverse_matrix(&A, &result), CALCULATION_ERROR);

  remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_test_4) {
  int size = 2;
  matrix_t A = {0}, expected = {0};

  create_matrix(size, size, &A);
  create_matrix(size, size, &expected);

  A.matrix[0][0] = 35.896;
  A.matrix[0][1] = -2.359;
  A.matrix[1][0] = 56;
  A.matrix[1][1] = 12.35;

  expected.matrix[0][0] = 30875.0 / 1438549.0;
  expected.matrix[0][1] = 1685.0 / 411014.0;
  expected.matrix[1][0] = -20000.0 / 205507.0;
  expected.matrix[1][1] = 12820.0 / 205507.0;

  matrix_t result = {0};

  ck_assert_int_eq(inverse_matrix(&A, &result), OK);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected.matrix[i][j],
                              ACCURACY);
    }
  }

  remove_matrix(&A);
  remove_matrix(&expected);
  remove_matrix(&result);
}
END_TEST

Suite *inverse_matrix_suite() {
  Suite *s;
  s = suite_create("\033[33minverse_matrix_tests\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("inverse_matrix_suite");

  tcase_add_test(tc_core, inverse_matrix_test_1);
  tcase_add_test(tc_core, inverse_matrix_test_2);
  tcase_add_test(tc_core, inverse_matrix_test_3);
  tcase_add_test(tc_core, inverse_matrix_test_4);
  tcase_add_test(tc_core, null_determinant_test);

  suite_add_tcase(s, tc_core);

  return s;
}
