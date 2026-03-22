/*
This class is the main base class for all algorithms
*/
#ifndef SORT_ALGORITHM_H
#define SORT_ALGORITHM_H

#include <vector>
#include <functional>
#include "core/sorting_event.h"

class SortAlgorithm
{

public:
    // Callback function for sending events.
    std::function<void(const SortEvent&)> onEvent;

    // Virtual method to run the algorithm & track visualizations in ops.
    virtual void run(std::vector<int>& arr) = 0;

    // Destructor.
    virtual ~SortAlgorithm() = default;
};

#endif