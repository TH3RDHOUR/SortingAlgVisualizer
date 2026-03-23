#include "sorting/insertion_sort.h"

void InsertionSort::run(std::vector<int>& m_arr)
{
    int n = m_arr.size();

    for (int i = 1; i < n; i++)
    {
        int key = m_arr[i];

        // Trigger a key set event.
        if (onEvent) onEvent({OpType::Key, i, -1, key});

        int j = i - 1;

        while (j >= 0 && m_arr[j] > key)
        {
            // Trigger a compare event.
            if (onEvent) onEvent({OpType::Compare, j, -1, 0});

            m_arr[j + 1] = m_arr[j];

            // Trigger a compare event.
            if (onEvent) onEvent({OpType::Overwrite, j + 1, -1, m_arr[j]});

            j--;
        }
        m_arr[j + 1] = key;

        // Trigger a swap event.
        if (onEvent) onEvent({OpType::Overwrite, j + 1, -1, key});

        // Trigger sorted event for the last element in this pass
        if (onEvent) onEvent({OpType::Sorted, i, -1, 0});
    }
}