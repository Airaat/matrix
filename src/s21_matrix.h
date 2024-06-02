#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#define SUCCESS 1
#define FAILURE 0
#define ACCURACY 1e-8

typedef struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

typedef enum { OK, INCORRECT_MATRIX, CALCULATION_ERROR } status;

int create_matrix(int rows, int columns, matrix_t *result);
void remove_matrix(matrix_t *A);
int eq_matrix(matrix_t *A, matrix_t *B);
int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int mult_number(matrix_t *A, double number, matrix_t *result);
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int transpose(matrix_t *A, matrix_t *result);
int calc_complements(matrix_t *A, matrix_t *result);
int determinant(matrix_t *A, double *result);
int inverse_matrix(matrix_t *A, matrix_t *result);

// Helpers
int incorrect_size(int rows, int columns);
int check_dimensions(matrix_t *A, matrix_t *B);
int contains_inf_nan(matrix_t *A);
void get_minor(matrix_t *src, matrix_t *dst, int p, int q);
double calculate_determinant(matrix_t *A);
#endif