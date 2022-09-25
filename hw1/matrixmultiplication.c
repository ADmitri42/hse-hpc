#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include "helpers.h"
#include "matrix_helpers.h"


void dgmm(int M, int N, int K, double *A, double *B, double *C)
{
    #pragma omp parallel for
    for (size_t j = 0; j < K; j++) {            // over columns of B
        for (size_t k = 0; k < N; k++) {        // over columns of A and rows of B
            for (size_t i = 0; i < M; i++) {    // over rows of A
                C[j * M + i] += A[k * M + i] * B[j * N + k];
            }
        }
    }
}

int main(int argc, char *argv[])
{ 
    Config config;
    if(parse_args(argc, argv, &config)) {
        return 1;
    }
    printf("n_thrd:\t%d\n", omp_get_max_threads());
    print_config(&config);

    clock_t start, end;
    double *A = create_matrix(config.M, config.N, false);
    double *B = create_matrix(config.N, config.K, false);
    double *C = create_matrix(config.M, config.K, true);

    double itime, ftime, exec_time;
    for (size_t run = 0; run < config.n_runs; run++) {
        itime = omp_get_wtime();
        dgmm(config.M, config.N, config.K, A, B, C);
        ftime = omp_get_wtime();
        printf("%f\n", (double)(ftime-itime));
    }
    if (config.show) {
        printf("A\n");
        show_matrix(config.M, config.N, A);
        printf("B\n");
        show_matrix(config.N, config.K, B);
        printf("C\n");
        show_matrix(config.M, config.K, C);
   }
   free(A);
   free(B);
   free(C);
   return 0;
}