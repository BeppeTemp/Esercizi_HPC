#include <immintrin.h>
#include <stdio.h>
int main(int argc, char const* argv[]) {

    // Single-precision permutation
    __m256 flt_pack_in = _mm256_set_ps(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

    __m256 flt_pack_out = _mm256_permute_ps(flt_pack_in, 0b00000001);

    float* flt_ptr = (float*)&flt_pack_out;
    printf("float:\t\t%f, %f, %f, %f, %f, %f, %f, %f\n", flt_ptr[0], flt_ptr[1], flt_ptr[2], flt_ptr[3], flt_ptr[4], flt_ptr[5], flt_ptr[6], flt_ptr[7]);

    //! Prendi il valore in posizione espressa dal valore nel ctrl e lo metti
    //! nella posizione del valore della ctrl

    //! 01  00  00  00  | 01  00  00  00
    //! 8   7   6   5   | 4   3   2   1

    //! 8   7   6   7   | 4   3   2   3 
    
    return 0;
}