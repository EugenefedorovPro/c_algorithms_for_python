#include "declarations.h"
#include <string.h>

int main() {
  /* char str1[] = "ABC"; */ 
  /* char str2[] = "ACD"; */ 

  char str1[] = "AGGTAB"; 
  char str2[] = "GXTXAYB"; 
  // 4


  int size1 = strlen(str1); 
  int size2 = strlen(str2);
  int result = lcs(str1, size1, str2, size2);

  printf("\nlongest common subsequence for '%s' and '%s' = %d\n", str1, str2, result);
  return 0;
}
