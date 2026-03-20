#include "sorting/selection_sort.h"
#include "sorting/sort_algorithm.h"

SelectionSort::SelectionSort(std::vector<int>& arr)
            : SortAlgorithm(arr), i(0), j((arr.size() > 1) ? 1 : 0) // Edge case if arr.size is 0 or 1.
{
    // Resize & set roles vector to the size of bar vector.
    state.roles.resize(m_arr.size());
    state.resetRoles(m_arr.size());
    
    min_idx = j;
}

bool SelectionSort::step()
{
    int n = m_arr.size();
    // Reset roles vector to all default.
    state.resetRoles(n);

    // Mark all bars as sorted starting from 0 to i.
    for (int k = 0; k < i; k++)
    {
        state.markSorted(k);
    }

    // Sorting is finished.
    if (i >= n - 1)
    {
        for (int k = 0; k < n; k++)
        {
            state.markSorted(i);
        }
        return false;
    }

    // INNER LOOP: Compare & swap min_idx with j.
    // j is less than size, continue comparing & getting smallest index.
    if (j < n)
    {
        // Mark both indicies that are being compared.
        state.markComparingPair(min_idx, j);

        if (m_arr[j] < m_arr[min_idx])
        {
            min_idx = j;
        }

        j++;
    }
    // j has reached the end, swap & start over in new unsorted region.
    else
    {
        std::swap(m_arr[min_idx], m_arr[i]);
        i++;
        j = i + 1;
        min_idx = i;
    }
    return true;
}

// Getters.
VisualState& SelectionSort::getState() { return state; }