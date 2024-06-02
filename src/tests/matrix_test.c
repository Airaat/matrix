#include "matrix_test.h"

#include <stdio.h>
#include <stdlib.h>
#define TEST_AMOUNT 40

int main() {
  int failed_tests = 0;
  Suite *matrix_tests[] = {
      create_matrix_suite(),    remove_matrix_suite(),  sum_matrix_suite(),
      sub_matrix_suite(),       eq_matrix_suite(),      mult_number_tests(),
      mult_matrix_suite(),      transpose_suite(),      determinant_suite(),
      calc_complements_suite(), inverse_matrix_suite(), NULL};

  for (int i = 0; matrix_tests[i] != NULL; i++) {
    SRunner *sr = srunner_create(matrix_tests[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed_tests += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("\n=========== \033[32mPASSED\033[0m: %d =============\n",
         TEST_AMOUNT - failed_tests);
  printf("\n=========== \033[31mFAILED\033[0m: %d ==============\n\n",
         failed_tests);

  return failed_tests == 0 ? 0 : 1;
}