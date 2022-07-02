#include <immintrin.h>
#include <stdio.h>

int main() {
    float* vet_a = (float*)aligned_alloc(sizeof(float) * 8, 32);
    float* vet_b = (float*)aligned_alloc(sizeof(float) * 8, 32);
    float* vet_c = (float*)aligned_alloc(sizeof(float) * 8, 32);

    for (int i = 0; i < 8; i++) {
        vet_a[i] = 0;
        vet_b[i] = 2;
        vet_c[i] = 1;
    }

    __m256 vet_a_256 = _mm256_load_ps(vet_a);
    __m256 vet_b_256 = _mm256_load_ps(vet_b);
    __m256 vet_c_256 = _mm256_load_ps(vet_c);

    /* Compute the difference between the two vectors */
    //! res = a * b + c
    __m256 result = _mm256_fmadd_ps(vet_a_256, vet_b_256, vet_c_256);

    /* Display the elements of the result vector */
    float* f = (float*)&result;

    printf("Risultato: \n");
    for (int i = 0; i < 8; i++) {
        printf("%01.2f ", f[i]);
    }
    printf("\n");
    
    return 0;
}