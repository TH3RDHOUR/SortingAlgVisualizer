#include "sorting/insertion_sort.h"
#include "sorting/sort_algorithm.h"

InsertionSort::InsertionSort(std::vector<int>& arr)
            : SortAlgorithm(arr), i(0), j(0)
{
    // Resize & set roles vector to the size of bar vector.
    state.roles.resize(m_arr.size());
    state.resetRoles(m_arr.size());
}

bool InsertionSort::step()
{
    state.resetRoles(m_arr.size());
    return true;
}

// Getters.
// Return roles for each bar for coloring.
std::vector<BarRole>& InsertionSort::getRoles() { return state.roles; }