#ifndef INIT_VECTOR_H
#define INIT_VECTOR_H

#include <random>
#include "rendering/visual_state.h"

void initVector(std::vector<int>& arr, std::mt19937& gen, VisualState& state);

#endif