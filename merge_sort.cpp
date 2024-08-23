#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "merge_sort.h"

void MergeSort::operator()(TapeImpl& in_tape, TapeImpl& out_tape, const size_t limit) {

    //Temporary fstream for merging
	std::fstream tmp("tmp/tmp_bin", std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);

    TapeImpl tmpTape2(tmp);

    std::vector<int32_t> buf;
    while(!in_tape.isEnd()) {
        buf.reserve(limit / sizeof(int32_t));
        for(size_t i = 0; i < (limit / sizeof(int32_t)) && !in_tape.isEnd(); i++){
            buf.push_back(in_tape.readElement());
            in_tape.moveRight();
        }
        std::sort(buf.begin(), buf.end());
        merge(buf, out_tape, tmpTape2);
        buf.clear();
    }
}

void MergeSort::merge(std::vector<int32_t> &buf, TapeImpl& tmp1, TapeImpl& tmp2) {
    size_t index = 0;
    while( index < buf.size() && !tmp1.isEnd() ) {
        int32_t elem = tmp1.readElement();
        if(buf[index] < elem){
            tmp2.writeElement(buf[index]);
            tmp2.moveRight();
            ++index;
        }
        else {
            tmp2.writeElement(elem);
            tmp2.moveRight();
            tmp1.moveRight();
        }
    }
    if(index == buf.size() ){
        while(!tmp1.isEnd()){
            tmp2.writeElement(tmp1.readElement());
            tmp2.moveRight();
            tmp1.moveRight();
        } 
    }
    
    else{
        while(index < buf.size()){
            tmp2.writeElement(buf[index]);
            tmp2.moveRight();
            ++index;
        }
    }
    swapTwoTapes(tmp1, tmp2);
}

void MergeSort::swapTwoTapes(TapeImpl& t1, TapeImpl& t2) {
    t1.swap(t2);
    t1.rewind();
    t2.rewind();
}