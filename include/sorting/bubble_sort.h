#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include "sorting/SortAlgorithm.h"
#include <iostream>
#include <vector>

class BubbleSort : public SortAlgorithm
{
private:
    int i;
    int j;

public:
    BubbleSort(std::vector<int>& arr);

    bool step() override;

    int getCurrentIndex1() override;
    int getCurrentIndex2() override;
    int getSortedStart() override;
};

#endif