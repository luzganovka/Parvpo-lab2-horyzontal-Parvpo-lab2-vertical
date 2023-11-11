#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <immintrin.h>

#define ARRAY_SIZE 262144  // 1 MB = 1024 KB = 1024 * 256 integers

const int MAX_VALUE = 100;     // Maximum value for random integers

int main() {
    int array[ARRAY_SIZE];  // Dynamically allocate memory for the array
    int result[8];

    // Seed the random number generator
    std::srand(1337);

    // Fill the array with random integers
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = std::rand() % MAX_VALUE + 1;
    }

    // Start the timer
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    // Calculate the sum of all the numbers in the array
    int sum = 1;
    __m256i avx_a = _mm256_loadu_si256((__m256i*)(array));

    for (int i = 8; i < ARRAY_SIZE; i += 8) {
        __m256i avx_b = _mm256_loadu_si256((__m256i*)(array + i));
        avx_a = _mm256_add_epi32(avx_a, avx_b);
    }

    _mm256_storeu_si256((__m256i*)(result), avx_a);

    for (int i = 0; i < 8; ++i) {
        sum += result[i];
    }

       // Stop the timer
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    double elapsed_time = duration.count();

    std::cout << "Sum of all numbers: " << sum << std::endl;
    std::cout << "Elapsed time: " << elapsed_time << " milliseconds" << std::endl;

    // Free the dynamically allocated memory

    return 0;
}
