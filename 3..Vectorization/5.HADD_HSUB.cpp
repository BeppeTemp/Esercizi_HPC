#include <immintrin.h>
#include <stdio.h>

int main() {
    float* vet_a = (float*)aligned_alloc(sizeof(float) * 8, 32);
    float* vet_b = (float*)aligned_alloc(sizeof(float) * 8, 32);

    for (int i = 0; i < 8; i++) {
        vet_a[i] = 0;
        vet_b[i] = i + 1  ;
    }

    __m256 vet_a_256 = _mm256_load_ps(vet_a);
    __m256 vet_b_256 = _mm256_load_ps(vet_b);

    /* Compute the difference between the two vectors */
    __m256 result = _mm256_hadd_ps(vet_a_256, vet_b_256);

    /* Display the elements of the result vector */
    float* f = (float*)&result;

    printf("Risultato: \n");
    for (int i = 0; i < 8; i++) {
        printf("%01.2f ", f[i]);
    }
    printf("\n");

    //! 0 0 | 3 7 | 0 0 | 11 15 
    //! 0+0 0+0 | 1+2 3+4 | 0+0 0+0 | 5+6 7+8  
    
    return 0;
}