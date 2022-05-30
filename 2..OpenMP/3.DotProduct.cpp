#include <omp.h>
#include <iostream>

#define SIZE 500000

using namespace std;

void time_stats(double seconds) {
    printf("Execution times:\n");
    printf("    * %.0f μs \n", seconds * 1000 * 1000);
    printf("    * %.2f ms \n", seconds * 1000);
    printf("    * %.2f s \n", seconds );
    printf("\n");
}

int main(int argc, char* argv[]) {
    float *vet_a, *vet_b;

    vet_a = (float*)malloc(sizeof(float) * SIZE);
    vet_b = (float*)malloc(sizeof(float) * SIZE);

    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        vet_a[i] = 1.0;
        vet_b[i] = 1.0;
    }

    int thread = omp_get_max_threads();

    float tot = 0;
    float* th_tot = (float*)calloc(thread, sizeof(float));

    double t_init = omp_get_wtime();

    #pragma omp parallel num_threads(thread)
    {
        int th_id = omp_get_thread_num();

        #pragma omp for
        for (int i = 0; i < SIZE; i++) {
            th_tot[th_id] += (vet_a[i] * vet_b[i]);
        }

        // #pragma for reduction (+:tot)
        // for (int i = 0; i < thread; i++){
        //     tot += th_tot[i];
        // }
    }

    for (int i = 0; i < thread; i++){
        tot += th_tot[i];
    }

    printf("Result: %.2f\n", tot);
    time_stats(omp_get_wtime() - t_init);
    return 0;
}