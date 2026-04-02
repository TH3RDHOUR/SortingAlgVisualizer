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
    Swapping,
    Sorted,
    Pivot,
    Key,
    LeftHalf,
    RightHalf
};

// Help with animating any movement of bars.
struct Animation
{
    int fromA;
    int toA;

    int fromB = -1;
    int toB = -1;

    int valueA;
    int valueB;

    float progress;
};

struct VisualState
{
    std::vector<BarRole> roles;

    // Variables for tracking key index & value.
    int keyIndex = 0;
    int keyValue = 0;
    bool hasKey = false;
    bool hasFloatingKey = false;
    int keyTargetIndex = 0; // Where key is hovering.
    int movingFromIndex = -1; // Hidden index for moving animation.
    int keyCurrentIndex = 0;

    // Keep track of all currently active animations.
    std::vector<Animation> activeAnimations;
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
            // Only reset temporary visual properties.
            if (roles[i] == BarRole::Comparing || roles[i] == BarRole::Key || roles[i] == BarRole::Swapping)
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

    void markComparing(int index)
    {
        if (index < roles.size()) 
            roles[index] = BarRole::Comparing;
    }

    // Mark two bars as comparing if it is not the last element.
    void markComparingPair(int index1, int index2) {
        if (index1 < roles.size() && roles[index1] != BarRole::Sorted) 
            roles[index1] = BarRole::Comparing;
        if (index2 < roles.size() && roles[index2] != BarRole::Sorted) 
            roles[index2] = BarRole::Comparing;
    }

    // Mark the bars during a swap to not lose coloring.
    void markSwapping(int index1, int index2)
    {
        if (index1 < roles.size() && roles[index1] != BarRole::Sorted)
            roles[index1] = BarRole::Swapping;
        if (index2 < roles.size() && roles[index2] != BarRole::Sorted)
            roles[index2] = BarRole::Swapping;
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
        if (num < roles.size() && roles[num] != BarRole::Sorted) 
            roles[num] = BarRole::Key;
    }

    // Mark the left half of the vector.
    void markLeftHalf(int start, int end)
    {
        for (int i = start; i <= end; i++)
        {
            if (roles[i] != BarRole::Sorted)
                roles[i] = BarRole::LeftHalf;
        }
    }

    // Mark the right half of the vector.
    void markRightHalf(int start, int end)
    {
        for (int i = start; i <= end; i++)
        {
            if (roles[i] != BarRole::Sorted)
                roles[i] = BarRole::RightHalf;
        }
    }
};

#endif