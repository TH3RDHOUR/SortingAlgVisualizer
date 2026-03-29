#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "sorting/sort_algorithm.h"

class QuickSort : public SortAlgorithm
{
public:
    void run(std::vector<int>& m_arr) override;

    int partition(std::vector<int>& arr, int low, int high);
    void quickSort(std::vector<int>& arr, int low, int high);
};

#endif