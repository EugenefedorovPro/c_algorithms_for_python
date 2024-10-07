#include "../declarations.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_merge() {

  // case #0 - dif elements in range
  size_t size = 5;
  int arr[] = {5, 1, 3, 4, 2};
  int expected[] = {1, 2, 3, 4, 5};

  // case #1 - bubble
  int *merge_sorted = merge(arr, size);

  printf("\n--------------------\n");
  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size; i++) {
    printf(" %d ", merge_sorted[i]);
    CU_ASSERT(merge_sorted[i] == expected[i]);
  }
  printf("\n--------------------\n");

  // case #1 - 1 element in range
  size_t size1 = 1;
  int arr1[] = {5};
  int expected1[] = {5};

  int *merge_sorted1 = merge(arr1, size1);

  printf("\n--------------------\n");
  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size1; i++) {
    printf(" %d ", merge_sorted1[i]);
    CU_ASSERT(merge_sorted1[i] == expected1[i]);
  }
  printf("\n--------------------\n");

  // case #2 - duped elements in range
  size_t size2 = 4;
  int arr2[] = {5, 1, 2, 1};
  int expected2[] = {1, 1, 2, 5};

  int *merge_sorted2 = merge(arr2, size2);

  printf("\n--------------------\n");
  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size2; i++) {
    printf(" %d ", merge_sorted2[i]);
    CU_ASSERT(merge_sorted2[i] == expected2[i]);
  }
  printf("\n--------------------\n");


  // case #3 - negative element in a range
  size_t size3 = 4;
  int arr3[] = {5, 1, -2, 1};
  int expected3[] = {-2,1, 1,  5};

  int *merge_sorted3 = merge(arr3, size3);

  printf("\n--------------------\n");
  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size3; i++) {
    printf(" %d ", merge_sorted3[i]);
    CU_ASSERT(merge_sorted3[i] == expected3[i]);
  }
  printf("\n--------------------\n");


}

int main() {
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("Sorting Suite", NULL, NULL);
  CU_add_test(suite, "test of merge()", test_merge);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}
