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

    double t_init = omp_get_wtime();

    #pragma omp parallel for schedule(static, SIZE / omp_get_max_threads())
    for (int i = 0; i < SIZE; i++) {
        a[i] = i;
    }

    printf("Static: \n");
    time_stats(omp_get_wtime() - t_init);

    return 0;
}