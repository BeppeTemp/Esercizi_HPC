#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 120000

using namespace std;

void time_stats(double seconds) {
    printf("Execution times:\n");
    printf("    * %.0f μs \n", seconds * 1000 * 1000);
    printf("    * %.2f ms \n", seconds * 1000);
    printf("    * %.2f s \n", seconds);
    printf("\n");
}

int main(int argo, char* argv[]) {
    int* a = (int*)malloc(sizeof(int) * SIZE);
    int* b = (int*)malloc(sizeof(int) * SIZE);
    int* c = (int*)malloc(sizeof(int) * SIZE);

    double t_init = omp_get_wtime();

    // In pratica ritorna sequenziale
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
    #pragma omp critical
        {
            a[i] = 0;
            b[i] = i;
            c[i] = i;
        }
    }
    printf("With Critical: \n");
    time_stats(omp_get_wtime() - t_init);

    t_init = omp_get_wtime();

    // Parallelo
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        a[i] = 0;
        b[i] = i;
        c[i] = i;
    }

    printf("No Critical: \n");
    time_stats(omp_get_wtime() - t_init);

    return 0;
}