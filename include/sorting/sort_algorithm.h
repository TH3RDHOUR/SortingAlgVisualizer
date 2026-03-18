#ifndef SORT_ALGORITHM_H
#define SORT_ALGORITHM_H

#include "visual_state.h"

class SortAlgorithm
{
protected:
    std::vector<int>& arr;
    VisualState state;

public:
    // Constructor.
    SortAlgorithm(std::vector<int>& array) : arr(array) {}

    // Virtual method to be used by children classes.
    virtual bool step() = 0;
    // Get the roles vector for visualization.
    virtual std::vector<BarRole>& getRoles() = 0;

    // Destructor.
    virtual ~SortAlgorithm() = default;
};

#endif