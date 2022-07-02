#include <immintrin.h>
#include <stdio.h>

int main() {
    __m256d vec1 = _mm256_setr_pd(1.0, 2.0, 3.0, 4.0);
    __m256d vec2 = _mm256_setr_pd(1.0, 2.0, 3.0, 4.0);
    __m256d neg = _mm256_setr_pd(1, -1.0, 1.0, -1.0);

    __m256d vec3 = _mm256_mul_pd(vec1, vec2);

    printf("Prima mul: \n");
    for (int i = 0; i < 4; i++) {
        printf("%f ", vec3[i]);
    }
    printf("\n");

    vec2 = _mm256_permute_pd(vec2, 0x5);

    printf("Prima permute: \n");
    for (int i = 0; i < 4; i++) {
        printf("%f ", vec2[i]);
    }
    printf("\n");

    vec2 = _mm256_mul_pd(vec2, neg);

    printf("Seconda mul: \n");
    for (int i = 0; i < 4; i++) {
        printf("%f ", vec2[i]);
    }
    printf("\n");

    __m256d vec4 = _mm256_mul_pd(vec1, vec2);

    printf("Terza mul: \n");
    for (int i = 0; i < 4; i++) {
        printf("%f ", vec4[i]);
    }
    printf("\n");

    vec1 = _mm256_hsub_pd(vec3, vec4);

    printf("Prima hsub: \n");
    for (int i = 0; i < 4; i++) {
        printf("%f ", vec4[i]);
    }
    printf("\n");

    double* res = (double*)&vec1;

    printf("Risultato: \n");
    printf("%lf %lf %lf %lf\n", res[0], res[1], res[2], res[3]);
    return 0;
}