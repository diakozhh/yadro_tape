#pragma once

#include <algorithm>
#include <iostream>
#include "tape_impl.h"
#include <utility>

class MergeSort {
public:    
// limit - bytes proverka na > 8 
    void operator()(TapeImpl& in_tape, TapeImpl& out_tape, TapeImpl& tmpTape1, TapeImpl& tmpTape2, const size_t limit) {
        
        std::vector<int32_t> buf;
        merge_count = 0;
        while(!in_tape.isEnd()) {
            buf.reserve(limit / sizeof(int32_t));
            std::cout <<std::endl;
            merge_count++;
            for(size_t i = 0; i < (limit / sizeof(int32_t)) && !in_tape.isEnd(); i++){
                buf.push_back(in_tape.readElement());
                in_tape.moveRight();
            }
            std::sort(buf.begin(), buf.end());
            merge(buf, tmpTape1, tmpTape2);
            buf.clear();
        }
        //if(merge_count % 2 == 1)
        swapTwoTapes(out_tape, tmpTape1);
        while(!out_tape.isEnd()){
            std::cout << out_tape.readElement() << " ";
            out_tape.moveRight();
        }
/*
        // merge
        while(!tmpTape1.isEnd() && !tmpTape2.isEnd()){
            if(tmpTape1.readElement() < tmpTape2.readElement()){
                out_tape.writeElement(tmpTape1.readElement());

                out_tape.moveRight();
                tmpTape1.moveRight();
                // moveRight()
            }
            else {
                out_tape.writeElement(tmpTape2.readElement());

                out_tape.moveRight();
                tmpTape2.moveRight();
                // moveRight()
            }
        }
        while(!tmpTape1.isEnd()){
            out_tape.writeElement(tmpTape1.readElement());

            out_tape.moveRight();
            tmpTape1.moveRight();
        }
        while(!tmpTape2.isEnd()){
            out_tape.writeElement(tmpTape2.readElement());

            out_tape.moveRight();
            tmpTape2.moveRight();
        }
*/    
    }
private:
    int merge_count = 0;

    void merge(std::vector<int32_t> &buf, TapeImpl& tmp1, TapeImpl& tmp2) { 
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
    void swapTwoTapes(TapeImpl& t1, TapeImpl& t2){
        t1.swap(t2);
        t1.rewind();
        t2.rewind();
    }
};