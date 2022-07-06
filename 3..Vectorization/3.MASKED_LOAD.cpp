#include <immintrin.h>
#include <stdio.h>

int main() {
    int* vet_a = (int*)aligned_alloc(sizeof(int) * 8, 32);
    int* vet_b = (int*)aligned_alloc(sizeof(int) * 8, 32);

    for (int i = 0; i < 8; i++) {
        vet_a[i] = 1;
        vet_b[i] = 0;
    }

    __m256i mask_a = _mm256_setr_epi32(-1, 0, 0, 0, 0, 0, 0, 0);

    __m256i vet_a_256 = _mm256_maskload_epi32(vet_a, mask_a);
    __m256i vet_b_256 = _mm256_load_si256((__m256i*) vet_b);
    
    /* Compute the difference between the two vectors */
    __m256i result = _mm256_sub_epi32(vet_a_256, vet_b_256);

    /* Display the elements of the result vector */
    int* f = (int*)&result;

    printf("Risultato: \n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", f[i]);
    }
    printf("\n");

    return 0;
}