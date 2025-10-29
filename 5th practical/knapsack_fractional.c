#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Item {
    int weight;
    int value;
};

void swap(struct Item *a, struct Item *b) {
    struct Item temp = *a;
    *a = *b;
    *b = temp;
}

void sortItems(struct Item arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            double r1 = (double)arr[i].value / arr[i].weight;
            double r2 = (double)arr[j].value / arr[j].weight;
            if (r1 < r2) swap(&arr[i], &arr[j]);
        }
    }
}

double fractionalKnapsack(struct Item items[], int n, int capacity) {
    sortItems(items, n);
    double totalValue = 0.0;

    for (int i = 0; i < n; i++) {
        if (capacity >= items[i].weight) {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        } else {
            totalValue += items[i].value * ((double)capacity / items[i].weight);
            break;
        }
    }
    return totalValue;
}

int main() {
    int n_values[10] = {10, 50, 100, 200, 300, 400, 500, 750, 1000, 1500};
    int capacity = 1000;
    FILE *f = fopen("knapsack_results.txt", "w");
    if (!f) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("N\tTime (seconds)\n");
    printf("------------------------\n");
    fprintf(f, "N Time\n");

    for (int i = 0; i < 10; i++) {
        int n = n_values[i];
        double total_time = 0.0;

        struct Item *items = malloc(sizeof(struct Item) * n);
        if (!items) {
            printf("Memory allocation failed\n");
            fclose(f);
            return 1;
        }

        // Fill random test data
        for (int j = 0; j < n; j++) {
            items[j].weight = rand() % 100 + 1;
            items[j].value = rand() % 200 + 1;
        }

        for (int k = 0; k < 50; k++) {
            clock_t start = clock();
            fractionalKnapsack(items, n, capacity);
            clock_t end = clock();
            total_time += (double)(end - start);
        }

        double avg_time = (total_time ) / CLOCKS_PER_SEC;
        printf("%d\t%f\n", n, avg_time);
        fprintf(f, "%d %f\n", n, avg_time);

        free(items);
    }

    fclose(f);
    return 0;
}
