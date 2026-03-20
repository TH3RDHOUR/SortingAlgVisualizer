#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include "sorting/sort_algorithm.h"

class SelectionSort : public SortAlgorithm
{
private:
    int i;
    int j;
    int min_idx;

public:
    SelectionSort(std::vector<int>& m_arr);

    bool step() override;

    VisualState& SelectionSort::getState() override;
};

#endif