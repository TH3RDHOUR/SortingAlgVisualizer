#ifndef SORT_ALGORITHM_H
#define SORT_ALGORITHM_H

#include "rendering/visual_state.h"
#include "core/sort_op.h"

class SortAlgorithm
{
protected:
    std::vector<int>& m_arr;

public:
    // Constructor.
    SortAlgorithm(std::vector<int>& array) : m_arr(array) {}

    // Virtual method to be used by children classes.
    virtual bool step(SortOp& op) = 0;

    // Destructor.
    virtual ~SortAlgorithm() = default;
};

#endif