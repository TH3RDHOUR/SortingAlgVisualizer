#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include "sorting/SortAlgorithm.h"

class BubbleSort : public SortAlgorithm
{
private:
    int i;
    int j;

public:
    BubbleSort(std::vector<int>& arr);

    // Main function to step through the algorithm.
    bool step() override;

    // Return the roles vector for visualizing algorithm.
    std::vector<BarRole>& getRoles() override;
};

#endif