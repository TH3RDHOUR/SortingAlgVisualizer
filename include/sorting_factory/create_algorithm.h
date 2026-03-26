#ifndef CREATE_ALGORITHM_H
#define CREATE_ALGORITHM_H

#include "sorting/sort_algorithm.h"
#include <memory>

std::unique_ptr<SortAlgorithm> createAlgorithm(int selectedAlg);

#endif