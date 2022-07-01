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
    int* a = (int*)malloc(sizeof(int) * SIZE);
    int* b = (int*)malloc(sizeof(int) * SIZE);
    int* c = (int*)malloc(sizeof(int) * SIZE);

    double t_init = omp_get_wtime();
    
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < SIZE; i++) {
            a[i] = 0;
            b[i] = i;
            c[i] = i;
        }

        #pragma omp for
        for (int i = 0; i < SIZE; i++) {
            a[i] = b[i] + c[i];
        }
    }

    printf("Standard: \n");
    time_stats(omp_get_wtime() - t_init);

    t_init = omp_get_wtime();

    //! la clausola nowait rimuove le barriere implicite funziona con for, sections e single
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < SIZE; i++) {
            a[i] = 0;
            b[i] = i;
            c[i] = i;
        }

        #pragma omp for nowait
        for (int i = 0; i < SIZE; i++) {
            a[i] = b[i] + c[i];
        }
    }
    //! Dopo le PR ci sono delle barriere implicite

    printf("With nowait but without barrier at the end: \n");
    time_stats(omp_get_wtime() - t_init);

    t_init = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < SIZE; i++) {
            a[i] = 0;
            b[i] = i;
            c[i] = i;
        }

        #pragma omp for nowait
        for (int i = 0; i < SIZE; i++) {
            a[i] = b[i] + c[i];
        }

        //! In teoria inutile perché presente alla fine della parallel region
        #pragma omp barrier
    }

    printf("With nowait but with barrier at the end: \n");
    time_stats(omp_get_wtime() - t_init);

    return 0;
}