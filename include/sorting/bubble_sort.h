#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include "sorting/SortAlgorithm.h"
#include <iostream>
#include <vector>

class BubbleSort : SortAlgorithm
{
private:
    int i;
    int j;

public:
    BubbleSort(std::vector<int>& arr);

    bool step() override;
    void reset() override;

    int getCurrentIndex1();
    int getCurrentIndex2();
    int getSortedStart();
};

#endif