#include <immintrin.h>
#include <stdio.h>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

#define SIZE 16

void time_stats(float micro_seconds) {
    cout << "Execution times:" << endl;
    printf("    * %.0f μs \n", micro_seconds);
    printf("    * %.2f ms \n", micro_seconds / 1000);
    printf("    * %.2f s \n", micro_seconds / 1000 / 1000);
    printf("    * %.0f minutes and %d seconds\n", ((micro_seconds / 1000) / 1000) / 60, (int)((micro_seconds / 1000) / 1000) % 60);
}

int main() {
    float* a_vet = (float*)aligned_alloc(32, SIZE * sizeof(float));
    float* b_vet = (float*)aligned_alloc(32, SIZE * sizeof(float));

#pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        a_vet[i] = 1;
        b_vet[i] = 1;
    }

    float* res_vet = (float*)malloc(SIZE * sizeof(float));

    auto start = high_resolution_clock::now();

    for (int i = 0; i < SIZE / 8; i++) {
        __m256 a_ps = _mm256_load_ps(a_vet + (32) * i);
        __m256 b_ps = _mm256_load_ps(b_vet + (32) * i);

        __m256 res_ps = _mm256_add_ps(a_ps, b_ps);

        for (int j = 0; j < 8; j++) {
            printf("rs: %d ", i * 8 + j);
            printf("rt: %d ", j);
            res_vet[(i * 8) + j] = res_ps[j];
        }
    }
    printf("\n");

    auto stop = high_resolution_clock::now();

    for (int i = 0; i < SIZE; i++) {
        printf("%2.1f ", res_vet[i]);
    }
    printf("\n\n");

    time_stats(duration_cast<microseconds>(stop - start).count());

    return 0;
}