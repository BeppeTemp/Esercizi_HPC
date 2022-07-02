#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 120000
#define DYNAMIC_GUIDED_CHUNK 200

using namespace std;

void time_stats(double seconds) {
    printf("Execution times:\n");
    printf("    * %.0f μs \n", seconds * 1000 * 1000);
    printf("    * %.2f ms \n", seconds * 1000);
    printf("    * %.2f s \n", seconds);
    printf("\n");
}

int main(int argo, char* argv[]) {
    float a[120000] __attribute__((aligned(64)));
    float b[120000] __attribute__((aligned(64)));
    float c[120000] __attribute__((aligned(64)));

    double t_init = omp_get_wtime();

    #pragma omp parallel for schedule(static, SIZE / omp_get_max_threads())
    for (int i = 0; i < SIZE; i++) {
        a[i] = 0;
        b[i] = i;
        c[i] = i;
    }

    #pragma omp parallel for schedule(static, SIZE / omp_get_max_threads())
    for (int i = 0; i < SIZE; i++) {
        a[i] = b[i] + c[i];
    }

    printf("Normal: \n");
    time_stats(omp_get_wtime() - t_init);

    t_init = omp_get_wtime();

    #pragma omp parallel for simd aligned(a:32) aligned(b:32) aligned(c:32)
    for (int i = 0; i < SIZE; i++) {
        a[i] = 0;
        b[i] = i;
        c[i] = i;
    }

    #pragma omp parallel for simd aligned(a:32) aligned(b:32) aligned(c:32)
    for (int i = 0; i < SIZE; i++) {
        a[i] = b[i] + c[i];
    }

    printf("Vectorized: \n");
    time_stats(omp_get_wtime() - t_init);
    

    return 0;
}