#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

using namespace std;

void time_stats(double seconds) {
    printf("Execution times:\n");
    printf("    * %.0f μs \n", seconds * 1000 * 1000);
    printf("    * %.2f ms \n", seconds * 1000);
    printf("    * %.2f s \n", seconds);
    printf("\n");
}

int main(int argo, char* argv[]) {
    //! Lo metti la e non si muove più
    setenv("OMP_PLACES", "cores", 1);
    //! Thread ovvero in corrispondenza del thread hardware
    //! Cores ovvero in corrispondenza del core
    //! Socket ovvero in corrispondenza del singolo core fisico (se MT)

    double t_init = omp_get_wtime();

    double* A = (double*)malloc(SIZE * sizeof(double));

    for (int i = 0; i < SIZE; i++) {
        A[i] = 1.0;
    }

    for (int i = 0; i < SIZE; i++) {
        A[i] = A[i] * 5;
    }

    printf("Sequential: \n");
    time_stats(omp_get_wtime() - t_init);

    t_init = omp_get_wtime();

    #pragma omp parallel for schedule(static, 1)
    for (int i = 0; i < SIZE; i++) {
        A[i] = 1.0;
    }

    #pragma omp parallel for schedule(dynamic, 1)
    for (int i = 0; i < SIZE; i++) {
        A[i] = A[i] * 5;
    }

    printf("Not optimized: \n");
    time_stats(omp_get_wtime() - t_init);

    t_init = omp_get_wtime();

    #pragma omp parallel for schedule(static, SIZE/4)
    for (int i = 0; i < SIZE; i++) {
        A[i] = 1.0;
    }
    #pragma omp nowait

    #pragma omp parallel for schedule(static, SIZE/4)
    for (int i = 0; i < SIZE; i++) {
        A[i] = A[i] * 5;
    }
    #pragma omp nowait

    printf("Optimized I: \n");
    time_stats(omp_get_wtime() - t_init);

    t_init = omp_get_wtime();

    #pragma omp parallel for schedule(static, SIZE / 4)
    for (int i = 0; i < SIZE; i++) {
        A[i] = 1.0;
        A[i] = A[i] * 5;
    }
    #pragma omp nowait

    printf("Optimized II: \n");
    time_stats(omp_get_wtime() - t_init);
}