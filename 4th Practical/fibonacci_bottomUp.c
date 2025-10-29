#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int fib(int n) {
    if (n < 0) return -1; 
    if (n == 0) return 0;
    if (n == 1) return 1;

    int *arr = malloc((n + 1) * sizeof(int));
    if (!arr) return -1; 

    arr[0] = 0;
    arr[1] = 1;
    for (int j = 2; j <= n; j++) {
        arr[j] = arr[j - 1] + arr[j - 2];
    }
    int result = arr[n];
    free(arr);
    return result;
}

int main() {
    int n_values[11] = {1, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
    FILE *f = fopen("fib_results_bottomup.txt", "w");
    if (!f) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("N\tTime (seconds)\n");
    printf("------------------------\n");
    fprintf(f, "N Time\n");  // header for Python

    for (int i = 0; i < 11; i++) {
        int n = n_values[i] * 100000;
        double total_time = 0;

        for (int k = 0; k < 100; k++) {
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
