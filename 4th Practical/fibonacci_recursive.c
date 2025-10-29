#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Recursive Fibonacci function
long long fib(int n) {
    if (n < 0) return -1; // invalid input
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    int n_values[11] = {1, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
    FILE *f = fopen("fib_recursive_results.txt", "w");
    if (!f) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("N\tTime (seconds)\n");
    printf("------------------------\n");
    fprintf(f, "N Time\n");  // header for Python

    for (int i = 0; i < 11; i++) {
        int n = n_values[i];  // recursive version is very slow, so use small n
        double total_time = 0;

        for (int k = 0; k < 1; k++) {  // running once is enough
            clock_t start = clock();
            fib(n);
            clock_t end = clock();
            total_time += (double)(end - start);
        }

        double avg_time = total_time / CLOCKS_PER_SEC;
        printf("%d\t%f\n", n, avg_time);
        fprintf(f, "%d %f\n", n, avg_time);
    }

    fclose(f);
    return 0;
}
