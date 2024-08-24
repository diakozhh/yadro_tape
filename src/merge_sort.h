#pragma once

#include "tape_impl.h"

class MergeSort {
public:
    void operator()(TapeImpl& in_tape, TapeImpl& out_tape, const size_t limit); 
private:
    void merge(std::vector<int32_t> &buf, TapeImpl& tmp1, TapeImpl& tmp2);
    void swapTwoTapes(TapeImpl& t1, TapeImpl& t2);

    int merge_count = 0;
};