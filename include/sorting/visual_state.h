#ifndef VISUAL_STATE_H
#define VISUAL_STATE_H

#include <vector>

enum class BarRole
{
    Default,
    Comparing,
    Sorted,
    Pivot
};

struct VisualState
{
    std::vector<BarRole> roles;

    // Reset all roles to default.
    void resetRoles(int size)
    {
        for (int i = 0; i < size; i++)
        {
            if (roles[i] != BarRole::Sorted)
            {
                roles[i] = BarRole::Default;
            }
        }
    }

    // Returns a const reference to avoid changing it.
    const std::vector<BarRole>& getRoles() const
    {
        return roles;
    }

    void markComparing(int num)
    {
        roles[num] = BarRole::Comparing;
    }

    // Mark two bars as comparing if it is not the last element.
    void markComparingPair(int index1, int index2) {
        if (index1 < roles.size()) roles[index1] = BarRole::Comparing;
        if (index2 < roles.size()) roles[index2] = BarRole::Comparing;
    }

    // Mark the bar as sorted
    void markSorted(int num)
    {
        roles[num] = BarRole::Sorted;
    }

    // Mark the bar as default.
    void markDefault(int num)
    {
        roles[num] = BarRole::Default;
    }
};

#endif