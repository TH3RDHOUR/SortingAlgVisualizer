/*
This file establishes the struct to hold the operations done by each algorithm.
*/
#ifndef SORT_OP_H
#define SORT_OP_H

enum class OpType {
    Compare,
    ComparePair,
    Swap,
    Shift,
    Overwrite,
    Sorted,
    Pivot,
    Key,
    KeyPickup,
    KeyPlace,
    MarkLeftRange,
    MarkRightRange,
};

struct SortEvent {
    OpType type;
    int a = -1;
    int b = -1;
    int value = 0;
};

#endif