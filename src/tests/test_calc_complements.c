#include "matrix_test.h"

START_TEST(calc_complements_test_1) {
  int size = 3;
  matrix_t A = {0}, result = {0}, expected = {0};

  create_matrix(size, size, &A);
  create_matrix(size, size, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  ck_assert_int_eq(calc_complements(&A, &result), OK);

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

START_TEST(calc_complements_test_2) {
  matrix_t A = {0}, result = {0};
  create_matrix(1, 1, &A);

  A.matrix[0][0] = 3;

  ck_assert_int_eq(calc_complements(&A, &result), CALCULATION_ERROR);

  remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_test_3) {
  matrix_t A = {0}, result = {0};
  create_matrix(3, 4, &A);

  ck_assert_int_eq(calc_complements(&A, &result), CALCULATION_ERROR);

  remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_test_4) {
  matrix_t A = {0}, result = {0};
  create_matrix(-3, -3, &A);

  ck_assert_int_eq(calc_complements(&A, &result), INCORRECT_MATRIX);
}
END_TEST

Suite *calc_complements_suite() {
  Suite *s;
  s = suite_create("\033[33mcalc_complements_tests\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("calc_complements_suite");

  tcase_add_test(tc_core, calc_complements_test_1);
  tcase_add_test(tc_core, calc_complements_test_2);
  tcase_add_test(tc_core, calc_complements_test_3);
  tcase_add_test(tc_core, calc_complements_test_4);

  suite_add_tcase(s, tc_core);

  return s;
}
