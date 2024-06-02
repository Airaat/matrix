#include "matrix_test.h"

double get_random_value(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  val = min + val * (max - min);

  return val;
}