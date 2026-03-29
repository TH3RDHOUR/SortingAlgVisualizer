#ifndef ALGORITHM_INFO_H
#define ALGORITHM_INFO_H

#include <memory>
#include "sorting/sort_algorithm.h"

struct SortAlgorithm;

struct AlgorithmInfo
{
    const char* name;
    const char* description;

    const char* bestCase;
    const char* avgCase;
    const char* worstCase;
    const char* spaceComp;

    bool stable;
    bool inPlace;

    std::unique_ptr<SortAlgorithm> (*create)();
};

extern const AlgorithmInfo algorithms[];
extern const int algorithmCount[];

const char* getAlgName(int i);
int getNumAlgs();

#endif