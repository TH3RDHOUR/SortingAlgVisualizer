#ifndef SORT_OP_H
#define SORT_OP_H

enum class OpType {
    Compare,
    Swap,
    Overwrite,
    Sorted,
    MarkPivot,
    MarkKey
};

struct SortOp {
    OpType type;
    int a = -1;
    int b = -1;
    int value = 0;
};

#endif