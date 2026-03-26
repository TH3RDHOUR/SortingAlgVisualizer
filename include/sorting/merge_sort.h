#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "sorting/sort_algorithm.h"

class MergeSort : public SortAlgorithm
{
public:
    void run(std::vector<int>& m_arr) override;

    void mergeSort(std::vector<int>& m_arr, int left, int right);
    void merge(std::vector<int>& m_arr, int left, int mid, int right);
};

#endif