#include "utils/init_vector.h"

// Initialize vector with random numbers.
void initVector(std::vector<int>& arr, std::mt19937& gen)
{
    // Define the number distribution.
    std::uniform_int_distribution<> distrib(1, 500);

    // Fill the array with random numbers.
    for (int& num : arr)
    {
        num = distrib(gen);
    }
}