#include "../declarations.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <math.h>
#include <string.h>
#define EPSILON 0.01

void test_rename() {

  // case #3 - with fractions
  size_t n_rows = 3;
  size_t n_cols = 2;
  int *value_weight = malloc(sizeof(int) * n_rows * n_cols);
  if (value_weight == NULL) {
    fprintf(stderr, "ERROR: memory allocation failed for value_weight");
  };
  value_weight[0 * n_cols + 0] = 120; // 0
  value_weight[0 * n_cols + 1] = 30; // 1
  value_weight[1 * n_cols + 0] = 100; // 2
  value_weight[1 * n_cols + 1] = 20; // 3
  value_weight[2 * n_cols + 0] = 60; // 4
  value_weight[2 * n_cols + 1] = 10; // 5
  int CAPACITY = 50;
  float result = f_knapsack(value_weight, n_rows, n_cols, CAPACITY);
  CU_ASSERT(result == 240.0);
  printf("\nmax total profit = %f\n", result);
  free(value_weight);

  // case #3.1
  size_t n_rows1 = 1;
  size_t n_cols1 = 2;
  int *value_weight1 = malloc(sizeof(int) * n_rows1 * n_cols1);
  value_weight1[0 * n_cols1 + 0] = 500; // 0
  value_weight1[0 * n_cols1 + 1] = 30;  // 1
  int CAPACITY1 = 10;
  float result1 = f_knapsack(value_weight1, n_rows1, n_cols1, CAPACITY1);
  CU_ASSERT(fabs(result1 - 166.667) < EPSILON);
  printf("\nmax total profit = %f\n", result1);
  free(value_weight);
  
  // case #2 - no fractions
  size_t n_rows2 = 1;
  size_t n_cols2 = 2;
  int *value_weight2 = malloc(sizeof(int) * n_rows1 * n_cols1);
  value_weight2[0 * n_cols2 + 0] = 100; // 0
  value_weight2[0 * n_cols2 + 1] = 30;  // 1
  int CAPACITY2 = 60;
  float result2 = f_knapsack(value_weight2, n_rows2, n_cols2, CAPACITY2);
  CU_ASSERT(fabs(result2 - 200) < EPSILON);
  printf("\nmax total profit = %f\n", result2);
  free(value_weight);
}

int main() {
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("Rename Suite", NULL, NULL);
  CU_add_test(suite, "test of rename()", test_rename);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}
