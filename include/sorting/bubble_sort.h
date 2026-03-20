#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include "sorting/sort_algorithm.h"

class BubbleSort : public SortAlgorithm
{
private:
    int i;
    int j;

public:
    BubbleSort(std::vector<int>& m_arr);

    // Main function to step through the algorithm.
    bool step() override;

    VisualState& BubbleSort::getState() override;
};

#endif