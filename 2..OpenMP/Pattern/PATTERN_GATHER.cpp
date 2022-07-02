#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 20000000
#define MASK_SIZE 10000000

using namespace std;

void time_stats(double seconds) {
    printf("Execution times:\n");
    printf("    * %.0f μs \n", seconds * 1000 * 1000);
    printf("    * %.2f ms \n", seconds * 1000);
    printf("    * %.2f s \n", seconds);
    printf("\n");
}

int main(int argo, char* argv[]) {
    int* vet_start = (int*)malloc(sizeof(int) * SIZE);
    int* res = (int*)calloc(sizeof(int), SIZE);
    int* mask = (int*)malloc(sizeof(int) * SIZE);

    for (int i = 0; i < SIZE; i++) {
        vet_start[i] = i;
    }

    for (int i = 0; i < MASK_SIZE; i++) {
        mask[i] = i;
    }

    //! Sequential version
    double t_init = omp_get_wtime();

    for (int i = 0; i < MASK_SIZE; i++) {
        int j = mask[i];

        //! La differenza con la scatter è tutta qua
        res[i] = vet_start[j];
    }

    time_stats(omp_get_wtime() - t_init);
    // for (int i = 0; i < SIZE; i++) {
    //     printf("%d ", vet_start[i]);
    // }
    // printf("\n");
    // for (int i = 0; i < MASK_SIZE; i++) {
    //     printf("%d ", res[i]);
    // }
    // printf("\n");

    //! Parallel version
    t_init = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < MASK_SIZE; i++) {
        int j = mask[i];
        res[i] = vet_start[j];
    }

    time_stats(omp_get_wtime() - t_init);
    // for (int i = 0; i < SIZE; i++) {
    //     printf("%d ", vet_start[i]);
    // }
    // printf("\n");
    // for (int i = 0; i < MASK_SIZE; i++) {
    //     printf("%d ", res[i]);
    // }
    // printf("\n");

    return 0;
}