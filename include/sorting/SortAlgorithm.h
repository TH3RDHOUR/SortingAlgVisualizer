#ifndef SORT_ALGORITHM_H
#define SORT_ALGORITHM_H

#include <vector>

class SortAlgorithm
{
protected:
    std::vector<int>& arr;

public:
    // Constructor.
    SortAlgorithm(std::vector<int>& array) : arr(array) {}

    // Virtual method to be used by children classes.
    virtual bool step() = 0;
    virtual void reset() = 0;

    // Destructor.
    virtual ~SortAlgorithm() = default;
};

#endif