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
    double* a =  (double*)malloc(SIZE * sizeof(double));

    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        a[i] = 1;
    }

    int tot = 0;
    int nthreads = omp_get_max_threads();
    double* s_priv = (double*)calloc(nthreads * 8, sizeof(float));;

    double t_init = omp_get_wtime();
    
    #pragma omp parallel num_threads(nthreads) 
    {
        int t = omp_get_thread_num(); 
    
        #pragma omp for
        for(int i = 0; i < SIZE; i++){
            s_priv[t * 8] += a[i];
        }
    }

    for(int i = 0; i < nthreads; i++) { 
        tot += s_priv[i * 8];
    }

    printf("Result: %d\n", tot);
    time_stats(omp_get_wtime() - t_init);
    return 0;
}