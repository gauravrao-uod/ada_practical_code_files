#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Memoized Fibonacci utility function
long long fibutil(int n, long long memo[]) {
    if (memo[n] != -1) return memo[n];
    memo[n] = fibutil(n - 1, memo) + fibutil(n - 2, memo);
    return memo[n];
}

// Memoized Fibonacci function
long long fib(int n) {
    long long *memo = (long long *)malloc((n + 1) * sizeof(long long));
    if (!memo) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i <= n; i++) memo[i] = -1;
    memo[0] = 0;
    memo[1] = 1;

    long long result = fibutil(n, memo);
    free(memo);
    return result;
}

int main() {
    int n_values[9] = {1, 5, 10, 15, 20, 25, 30, 35, 40};
    FILE *f = fopen("fib_memo_results.txt", "w");
    if (!f) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("N\tTime (seconds)\n");
    printf("------------------------\n");
    fprintf(f, "N Time\n");  // header for Python

    for (int i = 0; i < 9; i++) {
        int n = n_values[i] * 1000;  // scale up like iterative version
        double total_time = 0;

        for (int k = 0; k < 100; k++) {
            clock_t start = clock();
            fib(n);
            clock_t end = clock();
            total_time += (double)(end - start);
        }

        double avg_time = total_time / CLOCKS_PER_SEC / 100.0;  // average over 100 runs
        printf("%d\t%f\n", n, avg_time);
        fprintf(f, "%d %f\n", n, avg_time);
    }

    fclose(f);
    return 0;
}
