#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000
#define OMP_NUM_THREADS 2

using namespace std;

void time_stats(double seconds) {
    printf("Execution times:\n");
    printf("    * %.0f μs \n", seconds * 1000 * 1000);
    printf("    * %.2f ms \n", seconds * 1000);
    printf("    * %.2f s \n", seconds);
    printf("\n");
}

int main(int argo, char* argv[]) {
    int* b = (int*)malloc(sizeof(int) * SIZE);
    int* c = (int*)malloc(sizeof(int) * SIZE);

    // double t_init = omp_get_wtime();

    // for (int i = 0; i < SIZE; i++)
    //     for (int j = 0; j < SIZE; j++)
    //         for (int k = 0; k < SIZE; k++) {
    //             b[i] = 1;
    //             c[i] = 1;
    //         }

    // printf("Sequential: \n");
    // time_stats(omp_get_wtime() - t_init);

    double t_init = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for (int k = 0; k < SIZE; k++) {
                b[i] = 1;
                c[i] = 1;
            }

    printf("Not Collapsed: \n");
    time_stats(omp_get_wtime() - t_init);

    t_init = omp_get_wtime();

    //! Collassa ma non c'è questo grande miglioramento
    #pragma omp parallel for collapse(3)
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for (int k = 0; k < SIZE; k++) {
                b[i] = 1;
                c[i] = 1;
            }

    printf("Collapsed: \n");
    time_stats(omp_get_wtime() - t_init);

    return 0;
}