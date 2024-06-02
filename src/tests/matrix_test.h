#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H

#include <check.h>

#include "../s21_matrix.h"

#define MIN_VALUE -3E10
#define MAX_VALUE 3E10

double get_random_value(double min, double max);

Suite *create_matrix_suite();
Suite *remove_matrix_suite();
Suite *sum_matrix_suite();
Suite *sub_matrix_suite();
Suite *eq_matrix_suite();
Suite *mult_number_tests();
Suite *mult_matrix_suite();
Suite *transpose_suite();
Suite *determinant_suite();
Suite *calc_complements_suite();
Suite *inverse_matrix_suite();

#endif