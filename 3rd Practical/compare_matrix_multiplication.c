#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int** allocate_matrix(int n) {
    int** mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        mat[i] = (int*)calloc(n, sizeof(int));
    return mat;
}

void free_matrix(int** mat, int n) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

void random_matrix(int** mat, int n) {
    int MaxValue = 10;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = rand() % MaxValue;
}

void zero_matrix(int** mat, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = 0;
}

void multiply_iterative(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

void multiply_recursive(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int** A11 = allocate_matrix(k); int** A12 = allocate_matrix(k);
    int** A21 = allocate_matrix(k); int** A22 = allocate_matrix(k);
    int** B11 = allocate_matrix(k); int** B12 = allocate_matrix(k);
    int** B21 = allocate_matrix(k); int** B22 = allocate_matrix(k);
    int** C11 = allocate_matrix(k); int** C12 = allocate_matrix(k);
    int** C21 = allocate_matrix(k); int** C22 = allocate_matrix(k);
    int** M1 = allocate_matrix(k); int** M2 = allocate_matrix(k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];          A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];      A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];          B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];      B22[i][j] = B[i + k][j + k];
        }
    }

    // C11 = A11*B11 + A12*B21
    multiply_recursive(A11, B11, M1, k);
    multiply_recursive(A12, B21, M2, k);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C11[i][j] = M1[i][j] + M2[i][j];

    // C12 = A11*B12 + A12*B22
    multiply_recursive(A11, B12, M1, k);
    multiply_recursive(A12, B22, M2, k);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C12[i][j] = M1[i][j] + M2[i][j];

    // C21 = A21*B11 + A22*B21
    multiply_recursive(A21, B11, M1, k);
    multiply_recursive(A22, B21, M2, k);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C21[i][j] = M1[i][j] + M2[i][j];

    // C22 = A21*B12 + A22*B22
    multiply_recursive(A21, B12, M1, k);
    multiply_recursive(A22, B22, M2, k);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C22[i][j] = M1[i][j] + M2[i][j];

    // Combine
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];              C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];          C[i + k][j + k] = C22[i][j];
        }
    }

    free_matrix(A11, k); free_matrix(A12, k); free_matrix(A21, k); free_matrix(A22, k);
    free_matrix(B11, k); free_matrix(B12, k); free_matrix(B21, k); free_matrix(B22, k);
    free_matrix(C11, k); free_matrix(C12, k); free_matrix(C21, k); free_matrix(C22, k);
    free_matrix(M1, k);  free_matrix(M2, k);
}

void add_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    int** A11 = allocate_matrix(k); int** A12 = allocate_matrix(k);
    int** A21 = allocate_matrix(k); int** A22 = allocate_matrix(k);
    int** B11 = allocate_matrix(k); int** B12 = allocate_matrix(k);
    int** B21 = allocate_matrix(k); int** B22 = allocate_matrix(k);
    int** C11 = allocate_matrix(k); int** C12 = allocate_matrix(k);
    int** C21 = allocate_matrix(k); int** C22 = allocate_matrix(k);
    int** M1 = allocate_matrix(k); int** M2 = allocate_matrix(k);
    int** M3 = allocate_matrix(k); int** M4 = allocate_matrix(k);
    int** M5 = allocate_matrix(k); int** M6 = allocate_matrix(k);
    int** M7 = allocate_matrix(k);
    int** T1 = allocate_matrix(k); int** T2 = allocate_matrix(k);

    // Divide
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];          A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];      A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];          B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];      B22[i][j] = B[i + k][j + k];
        }

    // M1 = (A11+A22)*(B11+B22)
    add_matrix(A11, A22, T1, k); add_matrix(B11, B22, T2, k);
    strassen(T1, T2, M1, k);
    // M2 = (A21+A22)*B11
    add_matrix(A21, A22, T1, k); strassen(T1, B11, M2, k);
    // M3 = A11*(B12-B22)
    sub_matrix(B12, B22, T2, k); strassen(A11, T2, M3, k);
    // M4 = A22*(B21-B11)
    sub_matrix(B21, B11, T2, k); strassen(A22, T2, M4, k);
    // M5 = (A11+A12)*B22
    add_matrix(A11, A12, T1, k); strassen(T1, B22, M5, k);
    // M6 = (A21-A11)*(B11+B12)
    sub_matrix(A21, A11, T1, k); add_matrix(B11, B12, T2, k); strassen(T1, T2, M6, k);
    // M7 = (A12-A22)*(B21+B22)
    sub_matrix(A12, A22, T1, k); add_matrix(B21, B22, T2, k); strassen(T1, T2, M7, k);

    // C11 = M1+M4-M5+M7
    add_matrix(M1, M4, T1, k); sub_matrix(T1, M5, T2, k); add_matrix(T2, M7, C11, k);
    // C12 = M3+M5
    add_matrix(M3, M5, C12, k);
    // C21 = M2+M4
    add_matrix(M2, M4, C21, k);
    // C22 = M1-M2+M3+M6
    sub_matrix(M1, M2, T1, k); add_matrix(T1, M3, T2, k); add_matrix(T2, M6, C22, k);

    // Combine
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];        C[i + k][j + k] = C22[i][j];
        }

    free_matrix(A11, k); free_matrix(A12, k); free_matrix(A21, k); free_matrix(A22, k);
    free_matrix(B11, k); free_matrix(B12, k); free_matrix(B21, k); free_matrix(B22, k);
    free_matrix(C11, k); free_matrix(C12, k); free_matrix(C21, k); free_matrix(C22, k);
    free_matrix(M1, k); free_matrix(M2, k); free_matrix(M3, k); free_matrix(M4, k);
    free_matrix(M5, k); free_matrix(M6, k); free_matrix(M7, k);
    free_matrix(T1, k); free_matrix(T2, k);
}

void benchmark(void (*func)(int**,int**,int**,int), const char* name,
               int sizes[], int num_sizes, FILE* f) {
    for (int t = 0; t < num_sizes; t++) {
        int n = sizes[t];
        int** A = allocate_matrix(n);
        int** B = allocate_matrix(n);
        int** C = allocate_matrix(n);

        double diff = 0;
        for (int k = 0; k < 10; k++) {  // repeat 5 for averaging
            random_matrix(A, n);
            random_matrix(B, n);
            zero_matrix(C, n);

            clock_t start = clock();
            func(A, B, C, n);
            clock_t end = clock();
            diff += (double)(end - start);
        }

        double time = diff / CLOCKS_PER_SEC;
        printf("%s\tSize=%4d\tTime=%10.6f sec\n", name, n, time);
        fprintf(f, "%s %d %f\n", name, n, time);

        free_matrix(A, n); free_matrix(B, n); free_matrix(C, n);
    }
}

int main() {
    srand(time(NULL));
    int sizes[] = {1,2,4,8,16,32,64,128,256};
    int num_sizes = sizeof(sizes)/sizeof(sizes[0]);

    FILE* f = fopen("results.txt", "w");
    if (!f) { printf("File error!\n"); return 1; }
    fprintf(f, "Algorithm Size Time\n");

    benchmark(multiply_iterative, "Iterative", sizes, num_sizes, f);
    benchmark(multiply_recursive, "Recursive", sizes, num_sizes, f);
    benchmark(strassen,           "Strassen",  sizes, num_sizes, f);

    fclose(f);
    return 0;
}
