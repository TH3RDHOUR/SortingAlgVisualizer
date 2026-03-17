#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include "sorting/SortAlgorithm.h"
#include <iostream>
#include <vector>

class SelectionSort : public SortAlgorithm
{
private:
    int i;
    int j;
    int min_idx;

public:
    SelectionSort(std::vector<int>& arr);

    bool step() override;

    std::vector<BarRole>& getRoles() override;
};

#endif