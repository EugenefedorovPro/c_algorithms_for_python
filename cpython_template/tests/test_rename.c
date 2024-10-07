#include "../declarations.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <string.h>

void test_rename() {

  CU_ASSERT(0 == 0);
  
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
