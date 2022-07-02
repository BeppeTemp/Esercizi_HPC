#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 20
#define MASK_SIZE 10

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

    // for (int i = 0; i < MASK_SIZE; i++) {
    //     mask[i] = i;
    // }

    mask[0] = 1;
    mask[1] = 0;
    mask[2] = 1;
    mask[3] = 0;
    mask[4] = 2;
    mask[5] = 0;
    mask[6] = 2;
    mask[7] = 0;
    mask[8] = 3;
    mask[9] = 0;

    //! Sequential version
    double t_init = omp_get_wtime();

    for (int i = 0; i < MASK_SIZE; i++) {
        int j = mask[i];

        //! La differenza con la gather è tutta qua (è una MERGE SCATTER)
        res[j] += vet_start[i];
    }

    time_stats(omp_get_wtime() - t_init);
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", vet_start[i]);
    }
    printf("\n");
    for (int i = 0; i < MASK_SIZE; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    free(res);
    res = (int*)calloc(sizeof(int), SIZE);
    printf("--------------------------\n");

    //! Parallel version
    t_init = omp_get_wtime();

    #pragma omp parallel for schedule(static) num_threads(5)
    for (int i = 0; i < MASK_SIZE; i++) {
        int j = mask[i];

        #pragma omp critical(j)
            res[j] += vet_start[i];
    }

    time_stats(omp_get_wtime() - t_init);
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", vet_start[i]);
    }
    printf("\n");
    for (int i = 0; i < MASK_SIZE; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    return 0;
}