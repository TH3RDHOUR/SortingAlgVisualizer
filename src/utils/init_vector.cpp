#include "utils/init_vector.h"

// Initialize vector with random numbers.
void initVector(std::vector<int>& arr, std::mt19937& gen, VisualState& state)
{
    state.resetRoles(arr.size());

    // Define the number distribution.
    std::uniform_int_distribution<> distrib(1, 500);

    // Fill the array with random numbers.
    for (int i = 0; i < arr.size(); ++i)
    {
        arr[i] = distrib(gen);
    }
}