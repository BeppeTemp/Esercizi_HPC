#include <immintrin.h>
#include <stdio.h>
int main(int argc, char const* argv[]) {

    // Single-precision permutation
    __m256 flt_pack_in = _mm256_set_ps(4.0, 3.0, 2.0, 1.0, 4.0, 3.0, 2.0, 1.0);

    __m256 flt_pack_out = _mm256_permute_ps(flt_pack_in, 0b10011000);

    float* flt_ptr = (float*)&flt_pack_out;
    printf("float:\t\t%f, %f, %f, %f, %f, %f, %f, %f\n", flt_ptr[0], flt_ptr[1], flt_ptr[2], flt_ptr[3], flt_ptr[4], flt_ptr[5], flt_ptr[6], flt_ptr[7]);

    // Double-precision permutation
    __m256d dbl_pack_in = _mm256_set_pd(6.0, 5.0, 6.0, 5.0);

    __m256d dbl_pack_out = _mm256_permute_pd(dbl_pack_in, 0b0101);

    double* dpl_ptr = (double*)&dbl_pack_out;
    printf("double:\t\t%lf, %lf, %lf, %lf\n", dpl_ptr[0], dpl_ptr[1], dpl_ptr[2], dpl_ptr[3]);
    
    return 0;
}