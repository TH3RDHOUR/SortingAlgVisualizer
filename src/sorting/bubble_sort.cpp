#include "sorting/bubble_sort.h"
#include "sorting/sort_algorithm.h"

// Constructor.
BubbleSort::BubbleSort(std::vector<int>& arr)
        : SortAlgorithm(arr), i(0), j(0)
{
    // Resize & set roles vector to the size of bar vector.
    state.roles.resize(m_arr.size());
    state.resetRoles(m_arr.size());
}

// Overloaded method
bool BubbleSort::step()
{
    int n = m_arr.size();

    state.resetRoles(n);

    // Mark all sorted bars (last i elements).
    for (int k = (n - i); k < n; k++)
    {
        state.markSorted(k);
    }

    // Sorting is finished.
    if (i >= n - 1)
    {
        // Ensure the final bars are marked as sorted.
        for (int k = 0; k < n; k++)
        {
            state.markSorted(k);
        }
        return false;
    }

    // INNER LOOP: Comparing & swapping j.
    if (j < n - i - 1)
    {
        // Mark both indicies that are being compared.
        state.markComparingPair(j, j + 1);

        // if we need to swap the elements.
        if (m_arr[j] > m_arr[j + 1])
        {
            std::swap(m_arr[j], m_arr[j + 1]);
        }   

        j++;
    }
    else
    {
        // Reset j & increment i.
        j = 0;
        i++;    
    }
    return true;
}

// Getters.
// Return roles for each bar for coloring.
std::vector<BarRole>& BubbleSort::getRoles() { return state.roles; }
VisualState& BubbleSort::getState() { return state; }