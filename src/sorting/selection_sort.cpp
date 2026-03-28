/*
Selection sort traverses the unsorted region of the vector and finds the smallest element
each pass, then swaps that with the next index of the "sorted" portion of the vector.
*/
#include "sorting/selection_sort.h"

void SelectionSort::run(std::vector<int>& m_arr)
{
    int n = m_arr.size();

    for (int i = 0; i < n - 1; ++i)
    {
        int min_idx = i;

        // Trigger a key set event.
        if (onEvent) onEvent({OpType::Key, min_idx, -1, 0});

        for (int j = i + 1; j < n; ++j)
        {
            // Trigger a compare event.
            if (onEvent) onEvent({OpType::Compare, j, -1, 0});

            // If found a new smallest element, set as min_idx.
            if (m_arr[j] < m_arr[min_idx])
            {
                min_idx = j;
                // Trigger a key set event.
                if (onEvent) onEvent({OpType::Key, min_idx, -1, 0});
            }
        }

        // Swap current i index with smallest element.
        std::swap(m_arr[i], m_arr[min_idx]);

        // Trigger a swap event.
        if (onEvent) onEvent({OpType::Swap, i, min_idx, 0});

        // Trigger sorted event for the last element in this pass
        if (onEvent) onEvent({OpType::Sorted, i, -1, 0});
    }
}