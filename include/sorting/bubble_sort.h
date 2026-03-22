#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include "sorting/sort_algorithm.h"

class BubbleSort : public SortAlgorithm
{
public:
    void run(std::vector<int>& m_arr) override;
};

#endif