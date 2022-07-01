#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 122131332

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

    double t_init = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        {
            b[i] = 1;
            c[i] = 1;
        }
    }

    printf("Parallel: \n");
    time_stats(omp_get_wtime() - t_init);

    t_init = omp_get_wtime();

    #pragma omp task
    for (int i = 0; i < SIZE; i++) {
        {
            b[i] = 1;
            c[i] = 1;
        }
    }

    printf("Task: \n");
    time_stats(omp_get_wtime() - t_init);

    return 0;
}