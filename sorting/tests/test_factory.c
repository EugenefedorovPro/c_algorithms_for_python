#include "../declarations.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_factory() {

  size_t size = 5;
  int arr[] = {5, 1, 3, 4, 2};
  int expected[] = {1, 2, 3, 4, 5};

  // case #1 - bubble
  int *factory_sorted = factory("bubble", arr, size);

  printf("\ncase #1 - bubble\n");
  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size; i++) {
    printf(" %d ", factory_sorted[i]);
    CU_ASSERT(factory_sorted[i] == expected[i]);
  }
  printf("\n--------------------\n");

  // case #2 - selection

  int *selection_sorted = factory("selection", arr, size);
  printf("\ncase #2 - selection\n");
  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size; i++) {
    printf(" %d ", selection_sorted[i]);
    CU_ASSERT(selection_sorted[i] == expected[i]);
  }
  printf("\n--------------------\n");

  // case #3 - insertion
  printf("\ncase #3 - insertion\n");
  int *insertion_sorted = factory("insertion", arr, size);
  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size; i++) {
    printf(" %d ", insertion_sorted[i]);
    CU_ASSERT(insertion_sorted[i] == expected[i]);
  }
  printf("\n--------------------\n");

  // case #4 - merge
  printf("\ncase #4 - merge\n");
  int *merge_sorted = factory("merge", arr, size);
  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size; i++) {
    printf(" %d ", merge_sorted[i]);
    CU_ASSERT(merge_sorted[i] == expected[i]);
  }
  printf("\n--------------------\n");

  // case #4 - quick
  printf("\ncase #4 - quick\n");
  int *quick_sorted = factory("quick", arr, size);
  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size; i++) {
    printf(" %d ", quick_sorted[i]);
    CU_ASSERT(quick_sorted[i] == expected[i]);
  }
  printf("\n--------------------\n");
  
  // case #5 - merge_inplace
  printf("\ncase #4 - merge_inplace\n");
  int *merge_inplace_sorted = factory("merge_inplace", arr, size);
  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size; i++) {
    printf(" %d ", merge_inplace_sorted[i]);
    CU_ASSERT(merge_inplace_sorted[i] == expected[i]);
  }
  printf("\n--------------------\n");
};

int main() {
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("Sorting Suite", NULL, NULL);
  CU_add_test(suite, "test of factory()", test_factory);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}
