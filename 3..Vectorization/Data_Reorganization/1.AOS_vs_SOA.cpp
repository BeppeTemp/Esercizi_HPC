#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

struct AOS_Element {
    int x;
    int y;
    int z;
};
struct AOS_Element el_aos[1024];

struct SOA_Element {
    int x[1024];
    int y[1024];
    int z[1024];
};
struct SOA_Element el_soa;

void time_stats(double seconds) {
    printf("Execution times:\n");
    printf("    * %.0f μs \n", seconds * 1000 * 1000);
    printf("    * %.2f ms \n", seconds * 1000);
    printf("    * %.2f s \n", seconds);
    printf("\n");
}

int main(int argo, char* argv[]) {
    double t_init = omp_get_wtime();

    for (int i = 0; i < 1024; i++) {
        el_aos[i].x = i;
        el_aos[i].y = i;
        el_aos[i].z = i;
    }

    printf("AOS: \n");
    time_stats(omp_get_wtime() - t_init);

    t_init = omp_get_wtime();

    for (int i = 0; i < 1024; i++) {
        el_soa.x[i] = i;
        el_soa.y[i] = i;
        el_soa.z[i] = i;
    }

    printf("SOA: \n");
    time_stats(omp_get_wtime() - t_init);

    return 0;
}