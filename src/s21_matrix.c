#include "s21_matrix.h"

int create_matrix(int rows, int columns, matrix_t *result) {
  status code = OK;
  if (!result || incorrect_size(rows, columns)) {
    code = INCORRECT_MATRIX;
  } else {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++)
      result->matrix[i] = (double *)calloc(columns, sizeof(double));

    result->rows = rows;
    result->columns = columns;
  }

  return code;
}

void remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) free(A->matrix[i]);

  free(A->matrix);
  A->matrix = NULL;
}

int eq_matrix(matrix_t *A, matrix_t *B) {
  int status = SUCCESS;
  if (check_dimensions(A, B) || !A || !B) status = FAILURE;

  for (int i = 0; i < A->rows && status == SUCCESS; i++) {
    for (int j = 0; j < A->columns && status == SUCCESS; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > ACCURACY) status = FAILURE;
    }
  }

  return status;
}

int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  status code = (!A || !B || !result);
  if (!code) code = check_dimensions(A, B);

  if (!code) {
    int rows = A->rows;
    int columns = A->columns;
    code = create_matrix(rows, columns, result);
    for (int row = 0; row < rows && code == OK; row++) {
      for (int col = 0; col < columns && code == OK; col++) {
        result->matrix[row][col] = A->matrix[row][col] + B->matrix[row][col];
      }
    }
  }

  return code;
}

int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  status code = (!A || !B || !result);
  if (!code) code = check_dimensions(A, B);

  if (!code) {
    int rows = A->rows;
    int columns = A->columns;
    code = create_matrix(rows, columns, result);
    for (int row = 0; row < rows && code == OK; row++) {
      for (int col = 0; col < columns && code == OK; col++) {
        result->matrix[row][col] = A->matrix[row][col] - B->matrix[row][col];
      }
    }
  }

  return code;
}

int mult_number(matrix_t *A, double number, matrix_t *result) {
  status code = OK;
  code += (!A || !result);

  if (code == OK) {
    int rows = A->rows;
    int columns = A->columns;

    code = create_matrix(rows, columns, result);
    for (int row = 0; row < rows && code == OK; row++) {
      for (int col = 0; col < columns && code == OK; col++) {
        result->matrix[row][col] = A->matrix[row][col] * number;
      }
    }
  }

  return code;
}

int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  status code = (!result || !A || !B);
  if (!code && A->columns != B->rows) code = CALCULATION_ERROR;

  if (code == OK) {
    int rows = A->rows;
    int columns = B->columns;
    int k = A->columns;
    code = create_matrix(rows, columns, result);

    for (int row = 0; row < rows && code == OK; row++) {
      for (int col = 0; col < columns; col++) {
        for (int i = 0; i < k; i++) {
          result->matrix[row][col] += A->matrix[row][i] * B->matrix[i][col];
        }
      }
    }
  }

  return code;
}

int transpose(matrix_t *A, matrix_t *result) {
  status code = OK;
  code += (!A || !result);

  if (code == OK) {
    int rows = A->rows;
    int columns = A->columns;

    code = create_matrix(columns, rows, result);
    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < columns; col++) {
        result->matrix[col][row] = A->matrix[row][col];
      }
    }
  }

  return code;
}

int calc_complements(matrix_t *A, matrix_t *result) {
  status code = OK;
  int size = A->columns;
  if (!A || !result || incorrect_size(A->rows, A->columns))
    code = INCORRECT_MATRIX;
  else if (size < 2 || size != A->rows || contains_inf_nan(A))
    code = CALCULATION_ERROR;
  else
    code = create_matrix(size, size, result);

  if (code == OK) {
    matrix_t minor = {0};
    create_matrix(size - 1, size - 1, &minor);

    for (int row = 0; row < size; row++) {
      for (int col = 0; col < size; col++) {
        get_minor(A, &minor, row, col);

        double val = 0.0;
        determinant(&minor, &val);

        if ((row + col) % 2) val *= -1;

        result->matrix[row][col] = val;
      }
    }

    remove_matrix(&minor);
  }

  return code;
}

int determinant(matrix_t *A, double *result) {
  status code = OK;
  int size = A->columns;
  if (!A || !result || incorrect_size(A->rows, A->columns))
    code = INCORRECT_MATRIX;
  else if (size != A->rows || contains_inf_nan(A))
    code = CALCULATION_ERROR;

  if (code == OK) {
    *result = calculate_determinant(A);
  }

  return code;
}

int inverse_matrix(matrix_t *A, matrix_t *result) {
  status code = (!A || !result);
  double det = 0.0;
  if (code == OK) code = determinant(A, &det);
  if (!code && det == 0.0) code = CALCULATION_ERROR;

  if (code == OK) {
    matrix_t complements = {0};
    matrix_t transposed = {0};
    calc_complements(A, &complements);
    transpose(&complements, &transposed);
    mult_number(&transposed, 1.0 / det, result);

    remove_matrix(&complements);
    remove_matrix(&transposed);
  }

  return code;
}