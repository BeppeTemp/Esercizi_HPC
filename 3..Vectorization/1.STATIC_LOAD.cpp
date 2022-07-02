#include <immintrin.h>
#include <stdio.h>

int main() {
    // __m256 vet_a = _mm256_set_ps(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
    // __m256 vet_a = _mm256_setr_ps(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
    __m256 vet_a = _mm256_set_m128(_mm_set_ps(1.0, 2.0, 3.0, 4.0), _mm_set_ps(5.0, 6.0, 7.0, 8.0));

    // __m256 vet_b = _mm256_set_ps(8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0);
    __m256 vet_b = _mm256_setzero_ps();
    // __m256 vet_b = _mm256_set1_ps(5.0);

    /* Compute the difference between the two vectors */
    __m256 result = _mm256_sub_ps(vet_a, vet_b);

    /* Display the elements of the result vector */
    float* f = (float*)&result;

    printf("Risultato: \n");
    for (int i = 0; i < 8; i++) {
        printf("%01.2f ", f[i]);
    }
    printf("\n");

    return 0;
}