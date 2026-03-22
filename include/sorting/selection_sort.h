#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include "sorting/sort_algorithm.h"

class SelectionSort : public SortAlgorithm
{
public:
    void run(std::vector<int>& m_arr) override;
};

#endif