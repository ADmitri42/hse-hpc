#include <stdlib.h>
#include <stdio.h>

void fill_matrix(int M, int N, double *matrix)
{
    for (size_t i = 0; i < M * N; i++) {
        matrix[i] = -1+2*((float)rand())/RAND_MAX;
    }
}

double* create_matrix(int M, int N, bool empty)
{
    double *matrix = (double*)calloc(M * N, sizeof(double));
    if (!empty) {
        fill_matrix(M, N, matrix);
    }
    return matrix;
}

void show_matrix(int m, int n, double* matrix)
{
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            printf("%.2f\t", matrix[j * m + i]);
        }
        printf("\n");
    }
}