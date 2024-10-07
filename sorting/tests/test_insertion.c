#include "../declarations.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_insertion() {
  size_t size = 5;
  int arr[] = {64, 25, 12, 22, 11};
  int expected[] = {11, 12, 22, 25, 64};

  // function call
  int *sorted_arr = insertion(arr, size);

  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size; i++) {
    printf(" %d ", sorted_arr[i]);
    CU_ASSERT(sorted_arr[i] == expected[i]);
  }
  printf("\n--------------------\n");

  // case #1 - 1 element in range
  size_t size1 = 1;
  int arr1[] = {5};
  int expected1[] = {5};

  int *insertion_sorted1 = insertion(arr1, size1);

  printf("\n--------------------\n");
  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size1; i++) {
    printf(" %d ", insertion_sorted1[i]);
    CU_ASSERT(insertion_sorted1[i] == expected1[i]);
  }
  printf("\n--------------------\n");

  // case #2 - duped elements in range
  size_t size2 = 4;
  int arr2[] = {5, 1, 2, 1};
  int expected2[] = {1, 1, 2, 5};

  int *insertion_sorted2 = insertion(arr2, size2);

  printf("\n--------------------\n");
  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size2; i++) {
    printf(" %d ", insertion_sorted2[i]);
    CU_ASSERT(insertion_sorted2[i] == expected2[i]);
  }
  printf("\n--------------------\n");
}

int main() {
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("Sorting Suite", NULL, NULL);
  CU_add_test(suite, "test of insertion()", test_insertion);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}
