#include "sorting_factory/create_algorithm.h"
#include "sorting/bubble_sort.h"
#include "sorting/selection_sort.h"
#include "sorting/insertion_sort.h"

std::unique_ptr<SortAlgorithm> createAlgorithm(int selectedAlg)
{
    switch(selectedAlg)
    {
        case 0:
            return std::make_unique<BubbleSort>();
        case 1:
            return std::make_unique<SelectionSort>();
        case 2:
             return std::make_unique<InsertionSort>();
    }
    
    return nullptr;
}