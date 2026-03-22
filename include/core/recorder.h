/*
This file establishes a recorder that keeps track of all accumulated operations,
each operation is an individual step in the sort that needs to be visualized.
*/
#ifndef RECORDER_H
#define RECORDER_H

#include <vector>
#include "sorting_event.h"

class Recorder
{
    private:
        std::vector<int>& m_arr;
        std::vector<SortEvent>& m_events;

    public:
        Recorder(std::vector<int>& arr, std::vector<SortEvent>& events)
            : m_arr(arr), m_events(events) {}

        void compare(int i, int j)
        {
            m_events.push_back({OpType::Compare, i, j, 0});
        }

        void swap(int i, int j)
        {
            m_events.push_back({OpType::Swap, i, j, 0});
        }

        void overwrite(int index, int value)
        {
            m_events.push_back({OpType::Overwrite, index, -1, value});
        }

        void markSorted(int i)
        {
            m_events.push_back({OpType::Sorted, i, -1, 0});
        }
};

#endif