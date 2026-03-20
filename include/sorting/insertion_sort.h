#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "sorting/sort_algorithm.h"

class InsertionSort : public SortAlgorithm
{
private:
    int i;
    int j;
    int key;

public:
    InsertionSort(std::vector<int>& m_arr);

    bool step() override;

    VisualState& InsertionSort::getState() override;
};

#endif