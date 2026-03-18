#include "sorting/selection_sort.h"
#include "sorting/SortAlgorithm.h"

SelectionSort::SelectionSort(std::vector<int>& array)
            : SortAlgorithm(array), i(0), j(i + 1)
{
    // Resize & set roles vector to the size of bar vector.
    state.roles.resize(arr.size());
    state.resetRoles(array.size());
    
    min_idx = j;
}

bool SelectionSort::step()
{
    // Reset roles vector to all default.
    state.resetRoles(arr.size());

    // Mark all bars as sorted starting from 0 to i.
    for (int k = 0; k < i; k++)
    {
        state.markSorted(k);
    }

    // Sorting is finished.
    if (i >= arr.size() - 1)
    {
        state.markSorted(i);
        return false;
    }

    // Mark both indicies that are being compared.
    state.markComparingPair(min_idx, j);

    // j has reached the end, restart, increment i, & swap .
    if (j == arr.size())
    {
        std::swap(arr[min_idx], arr[i]);
        i++;
        j = i + 1;
        min_idx = i;
        return i <= arr.size() - 1;
    }
    // Found new minimum index value.
    else if (arr[j] < arr[min_idx])
    {
        min_idx = j;
    }
    j++;
    return i <= arr.size() - 1;
}

// Getters.
std::vector<BarRole>& SelectionSort::getRoles() { return state.roles; }