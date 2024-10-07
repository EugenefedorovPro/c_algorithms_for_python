#include "../declarations.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <string.h>

void test_lcs() {

  // case #1 strings of dif length
  char str1[] = "AGGTAB";
  char str2[] = "GXTXAYB";

  int size1 = strlen(str1);
  int size2 = strlen(str2);
  int result = lcs(str1, size1, str2, size2);
  CU_ASSERT(result == 4);

  printf("\nlongest common subsequence for '%s' and '%s' = %d\n", str1, str2,
         result);

  // case #2 - the same length
  char str3[] = "ABC";
  char str4[] = "ACD";

  int size3 = strlen(str3);
  int size4 = strlen(str4);
  int result2 = lcs(str3, size3, str4, size4);
  CU_ASSERT(result2 == 2);

  printf("\nlongest common subsequence for '%s' and '%s' = %d\n", str3, str4,
         result2);
  
  // case #3 - one letter 
  char str5[] = "A";
  char str6[] = "C";

  int size5 = strlen(str5);
  int size6 = strlen(str6);
  int result3 = lcs(str5, size5, str6, size6);
  CU_ASSERT(result3 == 0);

  printf("\nlongest common subsequence for '%s' and '%s' = %d\n", str3, str4,
         result2);
  

}

int main() {
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("Hash table Suite", NULL, NULL);
  CU_add_test(suite, "test of longest_common_subsequence()", test_lcs);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}
