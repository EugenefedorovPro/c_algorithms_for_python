#include <stdio.h>
#include <stdlib.h>

int fac_recur(int n) {
    if (n == 1) {
        return 1;
    }
    return n * fac_recur(n - 1);
}

int tail(int result_so_far, int n) {
    if (n == 0) {
        return result_so_far;
    }
    return tail(result_so_far * n, n - 1);
}

int fac_recur_tail(int n) {
    return tail(1, n);
}

int main() {
    int n = 5;
    int result_fac_recur = fac_recur(n);
    int result_fac_recur_tail = fac_recur_tail(n);

    printf("\nresult_fac_recur = %d\n", result_fac_recur);
    printf("\nresult_fac_recur_tail = %d\n", result_fac_recur_tail);

    return 0;
}
