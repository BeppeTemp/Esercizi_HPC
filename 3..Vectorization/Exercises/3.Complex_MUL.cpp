#include <immintrin.h>
#include <stdio.h>

int main() {
    __m256d vec1 = _mm256_setr_pd(4.0, 5.0, 13.0, 6.0);
    __m256d vec2 = _mm256_setr_pd(9.0, 3.0, 6.0, 7.0);
    __m256d neg = _mm256_setr_pd(1.0, -1.0, 1.0, -1.0);

    __m256d vec3 = _mm256_mul_pd(vec1, vec2);

    vec2 = _mm256_permute_pd(vec2, 0x5);

    vec2 = _mm256_mul_pd(vec2, neg);

    __m256d vec4 = _mm256_mul_pd(vec1, vec2);

    vec1 = _mm256_hsub_pd(vec3, vec4);

    double* res = (double*)&vec1;

    printf("%lf %lf %lf %lf\n", res[0], res[1], res[2], res[3]);
    return 0;
}