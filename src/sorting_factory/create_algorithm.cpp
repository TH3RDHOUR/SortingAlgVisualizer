#include "sorting_factory/create_algorithm.h"
#include "sorting/bubble_sort.h"
#include "sorting/selection_sort.h"
#include "sorting/insertion_sort.h"

SortAlgorithm* createAlgorithm(std::vector<int>& arr, int selectedAlg)
{
    switch(selectedAlg)
    {
        case 0:
            return new BubbleSort(arr);
        // case 1:
        //     return new SelectionSort(arr);
        // case 2:
        //     return new InsertionSort(arr);
    }
    return nullptr;
}