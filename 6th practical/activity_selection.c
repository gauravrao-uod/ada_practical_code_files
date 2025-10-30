#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int start;
    int end;
} elem;

void swap(elem* a, elem* b) {
    elem temp = *a;
    *a = *b;
    *b = temp;
}

int partition(elem* arr, int low, int high) {
    int pivot = arr[high].end;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].end < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort_elem(elem* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort_elem(arr, low, pi - 1);
        quicksort_elem(arr, pi + 1, high);
    }
}

elem* activity_selection(elem* arr, int size,  int* final_size) {
    quicksort_elem(arr, 0, size - 1);

    elem* arr2 = (elem*)malloc(sizeof(elem) * size);
    int i = 0, j = 0;

    while (i < size) {
        if (j == 0 || arr2[j - 1].end <= arr[i].start) {
            arr2[j] = arr[i];
            j++;
        }
        i++;
    }
    *final_size=j;
    printf("\nTotal selected activities: %d\n", j);
    return arr2;
}

int main() {
    int size = 15;
    elem* arr = (elem*)malloc(sizeof(elem) * size);

    srand(time(NULL));  // for different random values each run
    for (int i = 0; i < size; i++) {
        arr[i].start = rand() % 25;
        arr[i].end = arr[i].start + rand() % 20;
    }

    printf("Original Activities:\n");
    for (int i = 0; i < size; i++) {
        printf("%2d. %2d to %2d\n", i+1, arr[i].start, arr[i].end);
    }
    int final_size;
    elem* arr2 = activity_selection(arr, size, &final_size);


    printf("\nSelected Activities:\n");
    for (int i = 0; i < final_size; i++) {
        printf("%2d. %2d to %2d\n", i+1, arr2[i].start, arr2[i].end);
    }

    free(arr);
    free(arr2);

    return 0;
}
