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

    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < SIZE; i++) {
        sum += b[i] + c[i];
    }

    printf("Parallel: \n");
    time_stats(omp_get_wtime() - t_init);
    printf("res = %d\n\n", sum);
    
    t_init = omp_get_wtime();

    for (int i = 0; i < SIZE; i++) {
        {
            b[i] = 1;
            c[i] = 1;
        }
    }

    sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += b[i] + c[i];
    }

    printf("Sequential: \n");
    time_stats(omp_get_wtime() - t_init);
    printf("res = %d\n", sum);

    return 0;
}