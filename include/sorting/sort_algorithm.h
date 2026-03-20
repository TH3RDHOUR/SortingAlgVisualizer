#ifndef SORT_ALGORITHM_H
#define SORT_ALGORITHM_H

#include "visual_state.h"

class SortAlgorithm
{
protected:
    std::vector<int>& m_arr;
    VisualState state;

public:
    // Constructor.
    SortAlgorithm(std::vector<int>& array) : m_arr(array) {}

    // Virtual method to be used by children classes.
    virtual bool step() = 0;

    // Get the Visual State of the algorithm.
    virtual VisualState& getState() = 0;

    // Destructor.
    virtual ~SortAlgorithm() = default;
};

#endif