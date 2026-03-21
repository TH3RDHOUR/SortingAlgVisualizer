#include "sorting/insertion_sort.h"
#include "sorting/sort_algorithm.h"

InsertionSort::InsertionSort(std::vector<int>& arr)
            : SortAlgorithm(arr), i((arr.size() > 1) ? 1 : 0), j(0)
{
    // Resize & set roles vector to the size of bar vector.
    // state.roles.resize(m_arr.size());
    // state.resetRoles(m_arr.size());

    key = arr[i];
}

bool InsertionSort::step(SortOp& op)
{
    int n = m_arr.size();

    //state.resetRoles(n);

    if (i >= n)
    {
        // Ensure the final bars are marked as sorted.
        for (int k = 0; k < n; k++)
        {
            //state.markSorted(k);
        }
        return false;
    }

    // Mark all sorted bars (last i elements).
    for (int k = 0; k <= i; k++)
    {
        //state.markSorted(k);
    }

    if (j >= 0 && m_arr[j] > key)
    {
        // Mark both indicies that are being compared.
        //state.markComparing(j);

        m_arr[j + 1] = m_arr[j];

        if (j + 1 == i)
        {
            //state.markSorted(i);
        }

        //state.markKey(j + 1, key);
        j--;
    }
    else
    {
        m_arr[j + 1] = key;
        //state.markKey(j + 1, key);
        i++;
        if (i < n)
        {
            key = m_arr[i];
            j = i - 1;
        }
    }

    return true;
}