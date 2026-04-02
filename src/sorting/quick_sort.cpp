#include "sorting/quick_sort.h"

void QuickSort::run(std::vector<int>& m_m_arr)
{
    int n = m_m_arr.size();

    quickSort(m_m_arr, 0, n - 1);
}

int QuickSort::partition(std::vector<int>& m_arr, int low, int high) 
{ 
    // choose the pivot
    int pivot = m_arr[high];

    // Trigger a key set event.
    if (onEvent) onEvent({OpType::Key, high, -1, 0});
  
    // undex of smaller element and indicates 
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse m_arr[low..high] and move all smaller
    // elements on left side. Elements from low to 
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++) {

        // Trigger a ComparePair event.
        if (onEvent) onEvent({OpType::Compare, j, -1, 0});

        if (m_arr[j] < pivot) 
        {
            i++;
            std::swap(m_arr[i], m_arr[j]);

            // Trigger a swap event.
            if (onEvent) onEvent({OpType::Swap, i, j, 0});
        }
    }
    
    // move pivot after smaller elements and
    // return its position
    std::swap(m_arr[i + 1], m_arr[high]);

    // Trigger a swap event.
    if (onEvent) onEvent({OpType::Swap, i + 1, high, 0});

    return i + 1;
}

// the QuickSort function implementation
void QuickSort::quickSort(std::vector<int>& m_arr, int low, int high)
{
  
    if (low < high) {

        // Mark the active partition.
        if(onEvent) onEvent({OpType::MarkLeftRange, low, high, 0});
      
        // pi is the partition return index of pivot
        int pi = partition(m_arr, low, high);

        // recursion calls for smaller elements
        // and greater or equals elements
        quickSort(m_arr, low, pi - 1);
        quickSort(m_arr, pi + 1, high);
    }
}