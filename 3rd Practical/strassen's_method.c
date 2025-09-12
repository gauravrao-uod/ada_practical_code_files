#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Allocate memory for a matrix
int** allocate_matrix(int n) {
    int** mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        mat[i] = (int*)calloc(n, sizeof(int)); // initialized with 0
    return mat;
}

// Free memory for a matrix
void free_matrix(int** mat, int n) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

// Add two matrices: C = A + B
void add_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Subtract two matrices: C = A - B
void sub_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen’s Algorithm
void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    // Allocate submatrices
    int** A11 = allocate_matrix(k);
    int** A12 = allocate_matrix(k);
    int** A21 = allocate_matrix(k);
    int** A22 = allocate_matrix(k);
    int** B11 = allocate_matrix(k);
    int** B12 = allocate_matrix(k);
    int** B21 = allocate_matrix(k);
    int** B22 = allocate_matrix(k);
    int** C11 = allocate_matrix(k);
    int** C12 = allocate_matrix(k);
    int** C21 = allocate_matrix(k);
    int** C22 = allocate_matrix(k);

    int** M1 = allocate_matrix(k);
    int** M2 = allocate_matrix(k);
    int** M3 = allocate_matrix(k);
    int** M4 = allocate_matrix(k);
    int** M5 = allocate_matrix(k);
    int** M6 = allocate_matrix(k);
    int** M7 = allocate_matrix(k);

    int** temp1 = allocate_matrix(k);
    int** temp2 = allocate_matrix(k);

    // Divide matrices into 4 submatrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    add_matrix(A11, A22, temp1, k);
    add_matrix(B11, B22, temp2, k);
    strassen(temp1, temp2, M1, k);

    // M2 = (A21 + A22) * B11
    add_matrix(A21, A22, temp1, k);
    strassen(temp1, B11, M2, k);

    // M3 = A11 * (B12 - B22)
    sub_matrix(B12, B22, temp2, k);
    strassen(A11, temp2, M3, k);

    // M4 = A22 * (B21 - B11)
    sub_matrix(B21, B11, temp2, k);
    strassen(A22, temp2, M4, k);

    // M5 = (A11 + A12) * B22
    add_matrix(A11, A12, temp1, k);
    strassen(temp1, B22, M5, k);

    // M6 = (A21 - A11) * (B11 + B12)
    sub_matrix(A21, A11, temp1, k);
    add_matrix(B11, B12, temp2, k);
    strassen(temp1, temp2, M6, k);

    // M7 = (A12 - A22) * (B21 + B22)
    sub_matrix(A12, A22, temp1, k);
    add_matrix(B21, B22, temp2, k);
    strassen(temp1, temp2, M7, k);

    // C11 = M1 + M4 - M5 + M7
    add_matrix(M1, M4, temp1, k);
    sub_matrix(temp1, M5, temp2, k);
    add_matrix(temp2, M7, C11, k);

    // C12 = M3 + M5
    add_matrix(M3, M5, C12, k);

    // C21 = M2 + M4
    add_matrix(M2, M4, C21, k);

    // C22 = M1 - M2 + M3 + M6
    sub_matrix(M1, M2, temp1, k);
    add_matrix(temp1, M3, temp2, k);
    add_matrix(temp2, M6, C22, k);

    // Combine submatrices into result C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    // Free all allocated matrices
    free_matrix(A11, k); free_matrix(A12, k); free_matrix(A21, k); free_matrix(A22, k);
    free_matrix(B11, k); free_matrix(B12, k); free_matrix(B21, k); free_matrix(B22, k);
    free_matrix(C11, k); free_matrix(C12, k); free_matrix(C21, k); free_matrix(C22, k);
    free_matrix(M1, k);  free_matrix(M2, k);  free_matrix(M3, k);  free_matrix(M4, k);
    free_matrix(M5, k);  free_matrix(M6, k);  free_matrix(M7, k);
    free_matrix(temp1, k); free_matrix(temp2, k);
}

// Fill matrix with random numbers
void random_matrix(int** mat, int n) {
    int MaxValue = 10;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = rand() % MaxValue;
}

int main() {
    srand(time(NULL));

    int size_matrix[7] = {2, 4, 8, 16, 32,64,128 }; // test sizes (powers of 2 only)
    FILE* f = fopen("results.txt", "w");
    if (!f) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Matrix Size\tTime (seconds)\n");
    printf("-------------------------------\n");
    fprintf(f, "ArraySize Time\n");

    for (int t = 0; t < 7; t++) {
        int n = size_matrix[t];

        int** A = allocate_matrix(n);
        int** B = allocate_matrix(n);
        int** C = allocate_matrix(n);

        double difference = 0;

        for (int k = 0; k < 100; k++) { // repeat for averaging
            random_matrix(A, n);
            random_matrix(B, n);

            clock_t start = clock();
            strassen(A, B, C, n);
            clock_t end = clock();

            difference += (double)(end - start);
        }

        double time = difference / CLOCKS_PER_SEC;

        printf("%d\t\t%f\n", n, time);
        fprintf(f, "%d %f\n", n, time);

        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
    }

    fclose(f);
    return 0;
}
