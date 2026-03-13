#include "sorting/bubble_sort.h"


bool bubbleSort(std::vector<int>& arr, int& i, int& j)
{
    // Sorting is finished.
    if (i >= arr.size() - 1)
    {
        return false;
    }
    // j has reached the end, restart & increment i.
    if (j == arr.size() - i - 1)
    {
        j = 0;
        i++;
        return i < arr.size() - 1;
    }
    // if we need to swap the elements.
    else if (arr[j] > arr[j + 1])
    {
        std::swap(arr[j], arr[j + 1]);
    }
    // Increment j & return bool of if i has reached the end of vector.
    j++;
    return i < arr.size() - 1;
}