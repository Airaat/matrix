#include "matrix_test.h"

START_TEST(create_matrix_test_1) {
  matrix_t A = {0};

  ck_assert_int_eq(OK, create_matrix(3, 3, &A));
  remove_matrix(&A);

  ck_assert_int_eq(OK, create_matrix(1, 1, &A));
  remove_matrix(&A);

  ck_assert_int_eq(OK, create_matrix(10, 10, &A));
  remove_matrix(&A);

  ck_assert_int_eq(OK, create_matrix(100, 100, &A));
  remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_test_2) {
  matrix_t A = {0};

  ck_assert_int_eq(INCORRECT_MATRIX, create_matrix(0, 0, &A));
  ck_assert_int_eq(INCORRECT_MATRIX, create_matrix(-3, -3, &A));
  ck_assert_int_eq(INCORRECT_MATRIX, create_matrix(6, -3, &A));
  ck_assert_int_eq(INCORRECT_MATRIX, create_matrix(-3, 6, &A));
}
END_TEST

START_TEST(create_matrix_test_3) {
  matrix_t *A = NULL;

  ck_assert_int_eq(INCORRECT_MATRIX, create_matrix(3, 3, A));
}

Suite *create_matrix_suite() {
  Suite *s;
  s = suite_create("\033[33mcreate_matrix_tests\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("matrix_create_core");
  tcase_add_test(tc_core, create_matrix_test_1);
  tcase_add_test(tc_core, create_matrix_test_2);
  tcase_add_test(tc_core, create_matrix_test_3);

  suite_add_tcase(s, tc_core);

  return s;
}