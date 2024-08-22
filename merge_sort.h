#pragma once

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "tape_impl.h"

class MergeSort {
public:
    void operator()(TapeImpl& in_tape, TapeImpl& out_tape, TapeImpl& tmpTape1, TapeImpl& tmpTape2, const size_t limit); 
private:
    void merge(std::vector<int32_t> &buf, TapeImpl& tmp1, TapeImpl& tmp2);
    void swapTwoTapes(TapeImpl& t1, TapeImpl& t2);
};