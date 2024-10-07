#include "../declarations.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../declarations.h"

void test_selection() {
  size_t size = 5;
  int *arr = malloc(sizeof(int) * size);
  if (arr == NULL) {
    fprintf(stderr,
            "ERROR: memory allocation failed for arr in test_selection");
  }
  arr[0] = 5;
  arr[1] = 3;
  arr[2] = 4;
  arr[3] = 1;
  arr[4] = 2;

  // expected results
  int *expected = malloc(sizeof(int) * size);
  if (expected == NULL) {
    fprintf(stderr, "ERROR: memory allocation failed for arr in test_expected");
  }
  expected[0] = 1;
  expected[1] = 2;
  expected[2] = 3;
  expected[3] = 4;
  expected[4] = 5;

  // function call
  int *sorted_arr = selection(arr, size);

  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size; i++) {
    printf(" %d ", sorted_arr[i]);
    CU_ASSERT(sorted_arr[i] == expected[i]);
  }
  printf("\n--------------------\n");
}

int main() {
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("Sorting Suite", NULL, NULL);
  CU_add_test(suite, "test of selection()", test_selection);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}
