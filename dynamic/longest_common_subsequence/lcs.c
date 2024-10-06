#include <stdlib.h>

#include "declarations.h"

int recurs(char *str1, size_t size1, char *str2, size_t size2, int **matrix) {

  if (size1 == 0 || size2 == 0) {
    return 0;
  }

  char last1 = str1[size1 - 1];
  char last2 = str2[size2 - 1];

  // check status in matrix
  if (matrix[size1 - 1][size2 - 1] != -1) {
    return matrix[size1 - 1][size2 - 1];
  };

  if (last1 == last2) {
    matrix[size1 - 1][size2 - 1] =
        1 + recurs(str1, size1 - 1, str2, size2 - 1, matrix);
    return 1 + recurs(str1, size1 - 1, str2, size2 - 1, matrix);

  } else {
    int recurs1 = recurs(str1, size1 - 1, str2, size2, matrix);
    int recurs2 = recurs(str1, size1, str2, size2 - 1, matrix);
    return (recurs1 > recurs2) ? recurs1 : recurs2;
  }
  return matrix[size1][size2];
};

int lcs(char *str1, size_t size1, char *str2, size_t size2) {
  // allocate memory for 2D matrix
  int **matrix = malloc(sizeof(int *) * (size1 + 1));
  for (int i = 0; i < size1; i++) {
    matrix[i] = malloc(sizeof(int) * (size2 + 1));
  }

  for (int i = 0; i < size1; i++) {
    for (int j = 0; j < size2; j++) {
      matrix[i][j] = -1;
    }
  }

  int result = recurs(str1, size1, str2, size2, matrix);

  /* // print matrix */
  /* for (int i = 0; i < size1; i++) { */
  /*   for (int j = 0; j < size2; j++) { */
  /*     printf("\nmatrix[%d][%d] = %d\n", i, j, matrix[i][j]); */
  /*   } */
  /* } */
  free(matrix);
  return result;
}
