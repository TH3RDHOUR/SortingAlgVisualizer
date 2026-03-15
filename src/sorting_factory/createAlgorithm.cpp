#include "sorting_factory/createAlgorithm.h"
#include "sorting/bubble_sort.h"

SortAlgorithm* createAlgorithm(std::vector<int>& arr, int selectedAlg)
{
    switch(selectedAlg)
    {
        case 0:
            return new BubbleSort(arr);
    }
    return nullptr;
}