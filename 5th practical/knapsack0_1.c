#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack01(int W, int wt[], int val[], int n) {
    int **dp = malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++)
        dp[i] = malloc((W + 1) * sizeof(int));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    int result = dp[n][W];
    for (int i = 0; i <= n; i++)
        free(dp[i]);
    free(dp);
    return result;
}

int main() {
    int n_values[10] = {10, 50, 100, 200, 300, 400, 500, 750, 1000, 1500};
    int capacity = 1000;
    FILE *f = fopen("knapsack01_results.txt", "w");
    if (!f) {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(NULL));

    printf("N\tTime (seconds)\n");
    printf("------------------------\n");
    fprintf(f, "N Time\n");

    for (int i = 0; i < 10; i++) {
        int n = n_values[i];
        double total_time = 0.0;

        int *wt = malloc(sizeof(int) * n);
        int *val = malloc(sizeof(int) * n);
        if (!wt || !val) {
            printf("Memory allocation failed\n");
            fclose(f);
            return 1;
        }

        for (int j = 0; j < n; j++) {
            wt[j] = rand() % 100 + 1;
            val[j] = rand() % 200 + 1;
        }

        for (int k = 0; k < 50; k++) {
            clock_t start = clock();
            knapsack01(capacity, wt, val, n);
            clock_t end = clock();
            total_time += (double)(end - start);
        }

        double avg_time = total_time / CLOCKS_PER_SEC;
        printf("%d\t%f\n", n, avg_time);
        fprintf(f, "%d %f\n", n, avg_time);

        free(wt);
        free(val);
    }

    fclose(f);
    return 0;
}
