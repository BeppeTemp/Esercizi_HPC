#include <omp.h>
#include <iostream>

#define SIZE 500000

using namespace std;

void time_stats(double seconds) {
    printf("Execution times:\n");
    printf("    * %.0f μs \n", seconds * 1000 * 1000);
    printf("    * %.2f ms \n", seconds * 1000);
    printf("    * %.2f s \n", seconds);
    printf("\n");
}

double f(double x) {
    return (4.0 / (1.0 + x * x));
}

double CalcPi(int n) {
    const double fH = 1.0 / (double)n;
    double fSum = 0.0;
    double fX;

    #pragma omp parallel for private(fX) reduction(+:fSum)
    for (int i = 0; i < n; i++) {
        fX = fH * ((double)i + 0.5);
        fSum += f(fX);
    }
    return fH * fSum;
}

int main(int argc, char* argv[]) {
    double t_init = omp_get_wtime();

    printf("Result: %f\n", CalcPi(5000000));
    time_stats(omp_get_wtime() - t_init);
    return 0;
}