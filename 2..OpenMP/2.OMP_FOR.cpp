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

    //! Ogni thread ha size/12 elementi da computare
    //! I dati restano dove devono, ottimo per NUMA, ma non è buono per il LB
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

    printf("Static: \n");
    time_stats(omp_get_wtime() - t_init);

    t_init = omp_get_wtime();

    //! Ogni thread ha un tot di elementi da computare e appena finisce ne riceve altri
    //! Impossibile tenere traccia di dove vanno i dati, da non usare in NUMA, buono per LB con i giusti chunk
    #pragma omp parallel for schedule(dynamic, DYNAMIC_GUIDED_CHUNK)
    for (int i = 0; i < SIZE; i++) {
        a[i] = 0;
        b[i] = i;
        c[i] = i;
    }

    #pragma omp parallel for schedule(dynamic, DYNAMIC_GUIDED_CHUNK)
    for (int i = 0; i < SIZE; i++) {
        a[i] = b[i] + c[i];
    }

    printf("Dynamic: \n");
    time_stats(omp_get_wtime() - t_init);

    t_init = omp_get_wtime();

    //! Ogni thread ha un tot di elementi da computare e appena finisce ne riceve altri ma la quantità che ne riceve si riduce
    //! Impossibile tenere traccia di dove vanno i dati, da non usare in NUMA, buono per LB con i giusti chunk
    #pragma omp parallel for schedule(guided, DYNAMIC_GUIDED_CHUNK)
    for (int i = 0; i < SIZE; i++) {
        a[i] = 0;
        b[i] = i;
        c[i] = i;
    }

    #pragma omp parallel for schedule(guided, DYNAMIC_GUIDED_CHUNK)
    for (int i = 0; i < SIZE; i++) {
        a[i] = b[i] + c[i];
    }

    printf("Guided: \n");
    time_stats(omp_get_wtime() - t_init);

    //! È interessante la cosa che guided e dynamic hanno tempi di esecuzione variabili

    return 0;
}