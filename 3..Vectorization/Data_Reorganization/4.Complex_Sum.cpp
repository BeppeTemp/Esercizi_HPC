#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 4554546

struct AOS_CN {
    int real;
    int imag;
};
struct AOS_CN el_aos_a[SIZE];
struct AOS_CN el_aos_b[SIZE];
struct AOS_CN el_aos_c[SIZE];

struct SOA_CN {
    int real[SIZE];
    int imag[SIZE];
};
struct SOA_CN el_soa_a;
struct SOA_CN el_soa_b;
struct SOA_CN el_soa_c;

void time_stats(double seconds) {
    printf("Execution times:\n");
    printf("    * %.0f μs \n", seconds * 1000 * 1000);
    printf("    * %.2f ms \n", seconds * 1000);
    printf("    * %.2f s \n", seconds);
    printf("\n");
}

int main(int argo, char* argv[]) {
    
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        el_aos_a[i].real = i;
        el_aos_a[i].imag = i;

        el_aos_b[i].real = i;
        el_aos_b[i].imag = i;

        el_soa_a.real[i] = i;
        el_soa_b.imag[i] = i;

        el_soa_b.real[i] = i;
        el_soa_b.imag[i] = i;
    }
    
    double t_init = omp_get_wtime();

    for (int i = 0; i < SIZE - 1; i++) {
        el_aos_c[i].real = el_aos_a[i].real * el_aos_b[i + 1].real - el_aos_a[i].imag * el_aos_b[i].imag;
        el_aos_c[i].imag = el_aos_a[i].real * el_aos_b[i + 1].imag + el_aos_a[i].imag * el_aos_b[i].real;
    }

    printf("AOS: \n");
    time_stats(omp_get_wtime() - t_init);

    t_init = omp_get_wtime();

    for (int i = 0; i < SIZE - 1; i++) {
        el_soa_c.real[i] = el_soa_a.real[i] * el_soa_b.real[i + 1] - el_soa_a.imag[i] * el_soa_b.imag[i];
        el_soa_c.imag[i] = el_soa_a.real[i] * el_soa_b.imag[i + 1] + el_soa_a.imag[i] * el_soa_b.real[i];
    }

    printf("SOA: \n");
    time_stats(omp_get_wtime() - t_init);

    //! Questi sono accessi più specifici o comunque non allineati quindi è meglio AoS

    return 0;
}