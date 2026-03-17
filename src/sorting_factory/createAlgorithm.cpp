#include "sorting_factory/createAlgorithm.h"
#include "sorting/bubble_sort.h"
#include "sorting/selection_sort.h"

SortAlgorithm* createAlgorithm(std::vector<int>& arr, int selectedAlg)
{
    switch(selectedAlg)
    {
        case 0:
            return new BubbleSort(arr);
        case 1:
            return new SelectionSort(arr);
    }
    return nullptr;
}