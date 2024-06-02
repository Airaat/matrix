#include "matrix_test.h"

START_TEST(matrix_remove_test_1) {
  matrix_t A = {0};

  create_matrix(3, 3, &A);
  remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(matrix_remove_test_2) {
  matrix_t A = {0};

  remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
}
END_TEST

Suite *remove_matrix_suite() {
  Suite *s;
  s = suite_create("\033[33mremove_matrix_tests\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("matrix_remove_core");
  tcase_add_test(tc_core, matrix_remove_test_1);
  tcase_add_test(tc_core, matrix_remove_test_2);

  suite_add_tcase(s, tc_core);

  return s;
}