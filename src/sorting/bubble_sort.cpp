#include "sorting/bubble_sort.h"
#include "sorting/sort_algorithm.h"

// Constructor.
BubbleSort::BubbleSort(std::vector<int>& array)
        : SortAlgorithm(array), i(0), j(0)
{
    // Resize & set roles vector to the size of bar vector.
    state.roles.resize(arr.size());
    state.resetRoles(array.size());
}

// Overloaded method
bool BubbleSort::step()
{
    state.resetRoles(arr.size());

    // Mark all sorted bars starting from size - i to size().
    for (int k = (arr.size() - i); k < arr.size(); k++)
    {
        state.markSorted(k);
    }

    // Sorting is finished.
    if (i >= arr.size() - 1)
    {
        // Mark the final bar as sorted.
        state.markSorted(0);
        return false;
    }

    // Mark both indicies that are being compared.
    state.markComparingPair(j, j + 1);

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

// Getters.
// Return roles for each bar for coloring.
std::vector<BarRole>& BubbleSort::getRoles() { return state.roles; }