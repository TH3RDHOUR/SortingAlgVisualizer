/*
This file establishes the visual state of an algorithm, allows for changing the 
visual representation of bars for each value in the main vector.
*/
#ifndef VISUAL_STATE_H
#define VISUAL_STATE_H

#include <vector>

enum class BarRole
{
    Default,
    Comparing,
    Sorted,
    Pivot,
    Key
};

// Help animate the swapping.
struct SwapAnimation
{
    int indexA;
    int indexB;
    float progress; // 0.0 -> 1.0
};

struct VisualState
{
    std::vector<BarRole> roles;

    // Variables for tracking key index & value.
    int keyIndex = 0;
    int keyValue = 0;
    bool hasKey = false;

    // Keep track of all currently active swaps in algorithm.
    std::vector<SwapAnimation> activeSwaps;
    float swapSpeed = 5.0f;

    // Reset all roles to default.
    void resetRoles(int size)
    {
        if (roles.size() != size)
        {
            roles.resize(size, BarRole::Default);
        }

        for (int i = 0; i < size; i++)
        {
            roles[i] = BarRole::Default;
        }

        hasKey = false;
        keyIndex = 0;
        keyValue = 0;
    }

    void resetNonSorted(int size)
    {
        if (roles.size() != size)
        {
            roles.resize(size, BarRole::Default);
        }

        for (int i = 0; i < size; i++)
        {
            if (roles[i] != BarRole::Sorted)
            {
                roles[i] = BarRole::Default;
            }
        }
    }

    // Returns a const reference of roles vector.
    const std::vector<BarRole>& getRoles() const
    {
        return roles;
    }

    void markComparing(int num)
    {
        if (num < roles.size()) roles[num] = BarRole::Comparing;
    }

    // Mark two bars as comparing if it is not the last element.
    void markComparingPair(int index1, int index2) {
        if (index1 < roles.size()) roles[index1] = BarRole::Comparing;
        if (index2 < roles.size()) roles[index2] = BarRole::Comparing;
    }

    // Mark the bar as sorted
    void markSorted(int num)
    {
        if (num < roles.size()) roles[num] = BarRole::Sorted;
    }

    // Mark the bar as default.
    void markDefault(int num)
    {
        if (num < roles.size()) roles[num] = BarRole::Default;
    }

    // Mark the bar as the key index.
    void markKey(int num, int size)
    {
        keyIndex = num;
        keyValue = size;
        hasKey = true;
        if (num < roles.size()) roles[num] = BarRole::Key;
    }
};

#endif