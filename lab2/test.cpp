#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#define ARRAY_SIZE 262144  // 1 MB = 1024 KB = 1024 * 256 integers

const int MAX_VALUE = 100;     // Maximum value for random integers

int main() {
    int array[ARRAY_SIZE];  // Dynamically allocate memory for the array

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

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        sum += array[i];
    }

    

       // Stop the timer
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    double elapsed_time = duration.count();

    //std::cout << "Sum of all numbers: " << sum << std::endl;
    std::cout << "Elapsed time: " << elapsed_time << " milliseconds" << std::endl;

    // Free the dynamically allocated memory

    return sum;
}
