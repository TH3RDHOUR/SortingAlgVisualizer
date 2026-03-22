#include "sorting/bubble_sort.h"

void BubbleSort::run(std::vector<int>& m_arr)
{
    int n = m_arr.size();

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            // Trigger a compare event.
            if (onEvent) onEvent({OpType::Compare, j, j + 1, 0});

            if (m_arr[j] > m_arr[j + 1])
            {
                // Actually swap the array values.
                std::swap(m_arr[j], m_arr[j + 1]);

                // Trigger a swap event.
                if (onEvent) onEvent({OpType::Swap, j, j + 1, 0});
            }
        }
        // Trigger sorted event for the last element in this pass
        if (onEvent) onEvent({OpType::Sorted, n - 1 - i, -1, 0});
    }
}