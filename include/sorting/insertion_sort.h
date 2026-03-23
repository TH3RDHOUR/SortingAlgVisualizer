#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "sorting/sort_algorithm.h"

class InsertionSort : public SortAlgorithm
{
public:
    void run(std::vector<int>& m_arr) override;
};

#endif