#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define VALUE 60

void time_stats(double seconds) {
    printf("Execution times:\n");
    printf("    * %.0f μs \n", seconds * 1000 * 1000);
    printf("    * %.2f ms \n", seconds * 1000);
    printf("    * %.2f s \n", seconds);
    printf("\n");
}

int fib_seq(int n) {
    if (n < 2)
        return n;
    int x = fib_seq(n - 1);
    int y = fib_seq(n - 2);
    return x + y;
}

int fib_par(int n) {
    if (n < 2)
        return n;

    // sta fuori dal task quindi quando entra è firstprivate
    int x, y;

    #pragma omp task shared(x) if (n > 30)
    { x = fib_par(n - 1); }

    #pragma omp task shared(y) if (n > 30)
    { y = fib_par(n - 2); }

    // Serve aspettare che finiscano entrambi prima di ritornare valore
    #pragma omp taskwait

    return x + y;
}

int main(int argc, char* argv[]) {
    double t_init = omp_get_wtime();

    #pragma omp parallel
    #pragma omp  single
    { 
        printf("Res_Par: %d \n", fib_par(VALUE)); 
    }

    printf("Sequential: \n");
    time_stats(omp_get_wtime() - t_init);

    t_init = omp_get_wtime();

    printf("\n");

    printf("Res_Seq: %d\n", fib_seq(VALUE));
    printf("Parallel: \n");
    time_stats(omp_get_wtime() - t_init);
}