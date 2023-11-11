#include <iostream>
#include <immintrin.h>

const int ARRAY_SIZE = 8;  // Number of elements in the arrays

int main() {

    int a[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8};
    int b[ARRAY_SIZE] = {2, 4, 6, 8, 10, 12, 14, 16};
    int result[ARRAY_SIZE];

    __m256i avx_a = _mm256_loadu_si256((__m256i*)(a));

    // Perform vectorized addition using AVX intrinsic functions
    for (int i = 0; i < ARRAY_SIZE; i += 8) {
        __m256i avx_b = _mm256_loadu_si256((__m256i*)(b + i));
        avx_a = _mm256_add_epi32(avx_a, avx_b);
        _mm256_storeu_si256((__m256i*)(result + i), avx_a);
    }

    // Calculate the sum of the resulting array
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        sum += result[i];
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}