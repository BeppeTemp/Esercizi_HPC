#include <immintrin.h>
#include <stdio.h>
int main(int argc, char const* argv[]) {
    // Single-precision shuffle
    __m256 f256_vec_0 = _mm256_set_ps(8, 7, 6, 5, 4, 3, 2, 1);
    __m256 f256_vec_1 = _mm256_set_ps(16, 15, 14, 13, 12, 11, 10, 9);

    __m256 f256_result = _mm256_shuffle_ps(f256_vec_0, f256_vec_1, 0b00010001);

    float* flo = (float*)&f256_result;

    //! Leggi il ctrl a coppie di due (sinistra destra) da destra a sinistra prendi
    //! l'elemento in posizione del valore ctrl e mettilo in posizione del ctrl

    //! 01  00  | 01  00  | 01  00 | 01  00


    printf("float:\t\t%f, %f, %f, %f, %f, %f, %f, %f\n", flo[0], flo[1], flo[2], flo[3], flo[4], flo[5], flo[6], flo[7]);  
    
    // Double-precision shuffle
    __m256d d256_vec_0 = _mm256_set_pd(1, 2, 3, 4);
    __m256d d256_vec_1 = _mm256_set_pd(5, 6, 7, 8);

    __m256d d256_result = _mm256_shuffle_pd(d256_vec_0, d256_vec_1, 0b0110);

    double* dou = (double*)&d256_result;

    printf("double:\t\t%lf, %lf, %lf, %lf\n", dou[0], dou[1], dou[2], dou[3]);

    // 32-bit integer shuffle
    __m256i epi32_256_vec_0 = _mm256_set_epi32(1, 2, 3, 4, 5, 6, 7, 8);
    __m256i epi32_256_result = _mm256_shuffle_epi32(epi32_256_vec_0, 0b00010111);

    int* i = (int*)&epi32_256_result;

    printf("int:\t\t%d, %d, %d, %d, %d, %d, %d, %d\n", i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7]);  
    
    // 8-bit integer shuffle
    __m256i epi8_256_vec_0 = _mm256_set_epi8(1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16);
    __m256i epi8_256_control_vec = _mm256_set_epi8(0, 0, 1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10, 11, -11, 12, -12, 13, -13, 14, -14, 15, -15);

    __m256i epi8_256_result = _mm256_shuffle_epi8(epi8_256_vec_0, epi8_256_control_vec);

    char* c = (char*)&epi8_256_result;

    printf(
        "char:\t\t%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,"
        "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",
        c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11], c[12], c[13], c[14], c[15], c[16], c[17], c[18], c[19], c[20], c[21], c[22], c[23], c[24], c[25], c[26], c[27], c[28], c[29], c[30], c[31]);

    return 0;
}