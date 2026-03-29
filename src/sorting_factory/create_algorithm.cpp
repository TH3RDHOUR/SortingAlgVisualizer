#include <sorting_factory/create_algorithm.h>
#include "sorting/bubble_sort.h"
#include "sorting/selection_sort.h"
#include "sorting/insertion_sort.h"
#include "sorting/merge_sort.h"

std::unique_ptr<SortAlgorithm> createBubble()
{
    return std::make_unique<BubbleSort>();
}

std::unique_ptr<SortAlgorithm> createInsertion()
{
    return std::make_unique<InsertionSort>();
}

std::unique_ptr<SortAlgorithm> createSelection()
{
    return std::make_unique<SelectionSort>();
}

std::unique_ptr<SortAlgorithm> createMerge()
{
    return std::make_unique<MergeSort>();
}

// std::unique_ptr<SortAlgorithm> createQuick()
// {
//     return std::make_unique<QuickSort>();
// }

const AlgorithmInfo algorithms[] = 
{
    {
        "Bubble Sort",
        "Bubble sort is a simple sorting algorithm that repeatedly compares adjacent elements in a list and swaps them if they are in the wrong order, continuing this process until the list is sorted.",
        "O(n)", "O(n²)", "O(n²)", "O(1)",
        true, true,
        createBubble
    },
    {
        "Insertion Sort",
        "Insertion sort is a simple sorting algorithm that builds a sorted array one element at a time by repeatedly inserting each new element into its correct position within the already sorted portion of the array.",
        "O(n)", "O(n²)", "O(n²)", "O(1)",
        false, true,
        createInsertion
    },
    {
        "Selection Sort",
        "Selection sort is a simple sorting algorithm that repeatedly selects the smallest element from an unsorted portion of a list and moves it to the front until the entire list is sorted.",
        "O(n²)", "O(n²)", "O(n²)", "O(1)",
        false, true,
        createSelection
    },
    {
        "Merge Sort",
        "Merge sort is a divide-and-conquer sorting algorithm that recursively splits a list into smaller sublists, sorts them, and then merges them back together to produce a sorted list.",
        "O(n log n)", "O(n log n)", "O(n log n)", "O(n)",
        true, false,
        createMerge
    },
    {
        "Quick Sort",
        "Quicksort is a fast, general-purpose sorting algorithm that uses a divide-and-conquer approach to sort elements by partitioning them around a pivot value.",
        "O(n log n)", "O(n log n)", "O(n²)", "O(log n)",
        false, true,
        //createQuick
    }
};

int getNumAlgs()
{
    return sizeof(algorithms) / sizeof(AlgorithmInfo);
}