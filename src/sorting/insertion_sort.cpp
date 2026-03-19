#include "sorting/insertion_sort.h"
#include "sorting/sort_algorithm.h"

InsertionSort::InsertionSort(std::vector<int>& arr)
            : SortAlgorithm(arr), i((arr.size() > 1) ? 1 : 0), j(0)
{
    // Resize & set roles vector to the size of bar vector.
    state.roles.resize(m_arr.size());
    state.resetRoles(m_arr.size());

    key = arr[i];
}

bool InsertionSort::step()
{
    int n = m_arr.size();

    state.resetRoles(n);

    if (j == (i - 1))
    {
        state.markKey(i);
    }

    // Mark all sorted bars (last i elements).
    for (int k = 0; k < i; k++)
    {
        state.markSorted(k);
    }

    if (i >= n)
    {
        // Ensure the final bars are marked as sorted.
        for (int k = 0; k < n; k++)
        {
            state.markSorted(k);
        }
        return false;
    }

    if (j >= 0 && m_arr[j] > key)
    {
        // Mark both indicies that are being compared.
        state.markComparingPair(j, j + 1);

        m_arr[j + 1] = m_arr[j];
        j--;
    }
    else
    {
        m_arr[j + 1] = key;
        state.markKey(j + 1);
        i++;
        key = m_arr[i];
        j = i - 1;
    }

    return true;
}

// Getters.
// Return roles for each bar for coloring.
std::vector<BarRole>& InsertionSort::getRoles() { return state.roles; }