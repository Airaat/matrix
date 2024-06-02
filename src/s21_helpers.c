#include "s21_matrix.h"

int incorrect_size(int rows, int columns) {
  return (rows <= 0 || columns <= 0);
}

int check_dimensions(matrix_t* A, matrix_t* B) {
  status code = OK;
  int size_incorrect = 0;
  int dimensions_mismatch = 0;

  size_incorrect |= incorrect_size(A->rows, A->columns);
  size_incorrect |= incorrect_size(B->rows, B->columns);

  dimensions_mismatch |= (A->rows != B->rows);
  dimensions_mismatch |= (A->columns != B->columns);

  if (size_incorrect)
    code = INCORRECT_MATRIX;
  else if (dimensions_mismatch)
    code = CALCULATION_ERROR;

  return code;
}

int contains_inf_nan(matrix_t* A) {
  int code = OK;

  for (int i = 0; i < A->rows && code == OK; i++) {
    for (int j = 0; j < A->columns && code == OK; j++) {
      double val = A->matrix[i][j];
      if (isnan(val) || isinf(val)) code = CALCULATION_ERROR;
    }
  }

  return code;
}

void get_minor(matrix_t* src, matrix_t* dst, int p, int q) {
  int row = 0, col = 0;
  for (int i = 0; i < src->rows; i++) {
    if (i == p) continue;
    col = 0;
    for (int j = 0; j < src->columns; j++) {
      if (j == q) continue;
      dst->matrix[row][col] = src->matrix[i][j];
      col++;
    }
    row++;
  }
}

double calculate_determinant(matrix_t* A) {
  double result = 0.0;
  int size = A->rows;

  if (size == 1)
    result = A->matrix[0][0];
  else if (size == 2)
    result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  else {
    int sign = 1;
    matrix_t submatrix = {0};
    create_matrix(size - 1, size - 1, &submatrix);

    for (int i = 0; i < size; i++) {
      get_minor(A, &submatrix, 0, i);
      result += sign * A->matrix[0][i] * calculate_determinant(&submatrix);
      sign *= -1;
    }

    remove_matrix(&submatrix);
  }

  return result;
}