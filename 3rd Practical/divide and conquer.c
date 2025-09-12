#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Allocate a square 2D array (size x size)
int **initialize_array(int size) {
    int **X = (int **)malloc(sizeof(int *) * size);
    if (!X) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        X[i] = (int *)malloc(sizeof(int) * size);
        if (!X[i]) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
    return X;
}

// Fill with random integers
void randomMatrix(int **arr, int rows, int cols) {
    int MaxValue = 10;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = rand() % MaxValue;
        }
    }
}

// Recursive matrix multiplication (divide & conquer)
void multiply(int **A, int **B, int **C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int new_size = size / 2;

    // Sub-matrices
    int **A11 = initialize_array(new_size);
    int **A12 = initialize_array(new_size);
    int **A21 = initialize_array(new_size);
    int **A22 = initialize_array(new_size);
    int **B11 = initialize_array(new_size);
    int **B12 = initialize_array(new_size);
    int **B21 = initialize_array(new_size);
    int **B22 = initialize_array(new_size);

    // Temporary matrices for results
    int **M1 = initialize_array(new_size);
    int **M2 = initialize_array(new_size);

    // Split matrices A and B into sub-blocks
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + new_size];
            A21[i][j] = A[i + new_size][j];
            A22[i][j] = A[i + new_size][j + new_size];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + new_size];
            B21[i][j] = B[i + new_size][j];
            B22[i][j] = B[i + new_size][j + new_size];
        }
    }

    // C11 = A11*B11 + A12*B21
    multiply(A11, B11, M1, new_size);
    multiply(A12, B21, M2, new_size);
    for (int i = 0; i < new_size; i++)
        for (int j = 0; j < new_size; j++)
            C[i][j] = M1[i][j] + M2[i][j];

    // C12 = A11*B12 + A12*B22
    multiply(A11, B12, M1, new_size);
    multiply(A12, B22, M2, new_size);
    for (int i = 0; i < new_size; i++)
        for (int j = 0; j < new_size; j++)
            C[i][j + new_size] = M1[i][j] + M2[i][j];

    // C21 = A21*B11 + A22*B21
    multiply(A21, B11, M1, new_size);
    multiply(A22, B21, M2, new_size);
    for (int i = 0; i < new_size; i++)
        for (int j = 0; j < new_size; j++)
            C[i + new_size][j] = M1[i][j] + M2[i][j];

    // C22 = A21*B12 + A22*B22
    multiply(A21, B12, M1, new_size);
    multiply(A22, B22, M2, new_size);
    for (int i = 0; i < new_size; i++)
        for (int j = 0; j < new_size; j++)
            C[i + new_size][j + new_size] = M1[i][j] + M2[i][j];


    for (int i = 0; i < new_size; i++) {
        free(A11[i]); free(A12[i]); free(A21[i]); free(A22[i]);
        free(B11[i]); free(B12[i]); free(B21[i]); free(B22[i]);
        free(M1[i]); free(M2[i]);
    }
    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(M1); free(M2);
}

int main() {
    srand(time(NULL));

    int size_matrix[7] = {2, 4, 8, 16, 32,64,128}; 
    FILE *f = fopen("results.txt", "w");
    if (!f) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Matrix Size\tTime (seconds)\n");
    printf("-------------------------------\n");
    fprintf(f, "ArraySize Time\n");

    for (int t = 0; t < 7; t++) {
        int size = size_matrix[t];

        int **A = initialize_array(size);
        int **B = initialize_array(size);
        int **C = initialize_array(size);

        // Zero initialize C
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                C[i][j] = 0;

        double difference = 0;

        for (int k = 0; k < 100; k++) {
            randomMatrix(A, size, size);
            randomMatrix(B, size, size);

            clock_t start = clock();
            multiply(A, B, C, size);
            clock_t end = clock();

            difference += (double)(end - start);
        }

        double time = difference / CLOCKS_PER_SEC;

        printf("%d\t\t%f\n", size, time);
        fprintf(f, "%d %f\n", size, time);

        // free A, B, C
        for (int i = 0; i < size; i++) {
            free(A[i]); free(B[i]); free(C[i]);
        }
        free(A); free(B); free(C);
    }

    fclose(f);
    return 0;
}
