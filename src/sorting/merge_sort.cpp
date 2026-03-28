/*
Merge sort is a divide and conquer algorithm that recursively divides the vector in half
until you are left with single element vectors. Then it compares left and right vector's 
elements and places them into another vector in ascending order, it does this until we 
return to a vector the same size as the starting one, fully sorted.
*/
#include "sorting/merge_sort.h"

void MergeSort::run(std::vector<int>& m_arr)
{
    int n = m_arr.size();

    mergeSort(m_arr, 0, n - 1);
}

// Recursive calls to split the vector.
void MergeSort::mergeSort(std::vector<int>& m_arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(m_arr, left, mid);
    mergeSort(m_arr, mid + 1, right);
    merge(m_arr, left, mid, right);
}

// Merge all the separated vectors.
void MergeSort::merge(std::vector<int>& m_arr, int left, int mid, int right)
{
    // Mark the left and right half of the split vector.
    if(onEvent) onEvent({OpType::MarkLeftRange, left, mid, 0});
    if(onEvent) onEvent({OpType::MarkRightRange, mid + 1, right, 0});

    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors.
    std::vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = m_arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = m_arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge temp vectors back into m_arr[left...right]
    while (i < n1 && j < n2)
    {
        // Trigger a compare event on indicies.
        if (onEvent) onEvent({OpType::ComparePair, left + i, mid + 1 + j, 0});
        if (L[i] <= R[j])
        {
            // Trigger a compare event to highlight the "winner" from previous comparison.
            if (onEvent) onEvent({OpType::Compare, left + i, -1, 0});

            m_arr[k] = L[i];

            // Trigger an overwrite event
            //if (onEvent) onEvent({OpType::Overwrite, k, -1, L[i]});

            if (onEvent) onEvent({OpType::KeyPickup, k, -1, L[i]});
            if (onEvent) onEvent({OpType::KeyPlace, k, -1, L[i]});

            i++;
        }
        else
        {
            // Trigger a compare event to highlight the "winner" from previous comparison.
            if (onEvent) onEvent({OpType::Compare, mid + 1 + j, -1, 0});

            m_arr[k] = R[j];

            // Trigger an overwrite event
            //if (onEvent) onEvent({OpType::Overwrite, k, -1, R[j]});

            if (onEvent) onEvent({OpType::KeyPickup, k, -1, R[j]});
            if (onEvent) onEvent({OpType::KeyPlace, k, -1, R[j]});

            j++;
        }
        k++;
    }

    // Copy remaining elements of L[], if any
    while (i < n1)
    {
        m_arr[k] = L[i];

        // Trigger an overwrite event
        if (onEvent) onEvent({OpType::Overwrite, k, -1, L[i]});

        i++;
        k++;
    }

    // Copy remaining elements of R[], if any
    while (j < n2)
    {
        m_arr[k] = R[j];

        // Trigger an overwrite event
        if (onEvent) onEvent({OpType::Overwrite, k, -1, R[j]});

        j++;
        k++;
    }
}