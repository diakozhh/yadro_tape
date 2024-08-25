#pragma once

#include "tape_impl.h"

class MergeSort {
public:
    void operator()(TapeImpl& in_tape, TapeImpl& out_tape, const size_t limit); 
private:
    /**
     * @brief Merge sort
     * 
     * @param buf Temporary buffer for storing items from the tape
     * @param tmp1 Firs tape
     * @param tmp2 Second tape
     */
    void merge(std::vector<int32_t> &buf, TapeImpl& tmp1, TapeImpl& tmp2);
    /**
     * @brief simulate physical repositioning of tapes
     * 
     * @param t1 First tape
     * @param t2 Second tape
     */
    void swapTwoTapes(TapeImpl& t1, TapeImpl& t2);

    int merge_count = 0;
};