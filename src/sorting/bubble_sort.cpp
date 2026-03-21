#include "sorting/bubble_sort.h"
#include "sorting/sort_algorithm.h"

// Constructor.
BubbleSort::BubbleSort(std::vector<int>& arr)
        : SortAlgorithm(arr), i(0), j(0), swapPending(false) {}

// Overloaded method
bool BubbleSort::step(SortOp& op)
{
    int n = m_arr.size();

    // Sorting finished
    if (i >= n - 1)
        return false;

    // Inner loop finished, move to next pass
    if (j >= n - i - 1)
    {
        // Mark last element as sorted, reset j & increment i.
        op.type = OpType::Sorted;
        op.a = n - 1 - i;
        j = 0;
        i++;
        return true;
    }

    // Set operations to be compared.
    op.a = j;
    op.b = j + 1;

    // If elements are swapping or just comparing.
    if (m_arr[j] > m_arr[j + 1])
    {
        op.type = OpType::Swap;
        std::swap(m_arr[j], m_arr[j + 1]);
    }
    else
    {
        op.type = OpType::Compare;
    }

    // Move to next pair.
    j++;

    return true;
}