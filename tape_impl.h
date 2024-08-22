#pragma once

#include <vector>
#include <utility>
#include <stdint.h>
#include <fstream>
#include "tape.h"
#include "config_parser.h"

class TapeImpl : public Tape {
public:
    //TapeImpl() = delete;
    /*
    TapeImpl(TapeImpl&& other)
    {
        io_stream_ = std::move(other.io_stream_);
        position_ = std::move(other.position_);
        other.tape_config_ = std::move(other.tape_config_);
    }
    */

    TapeImpl& operator=( TapeImpl&& other) 
    {
        if(this != &other) {
            io_stream_.close();
        }
        io_stream_ = std::move(other.io_stream_);
        
        return *this;
    }
    TapeImpl(std::fstream& io_stream);
    void moveLeft();
    void moveRight();
    int readElement();
    void writeElement(int elem);
    inline int getPosition() {
        return this->position_;
    }
    
    bool isEnd() {
        //std::cout << io_stream_.cur;
        return io_stream_.peek() == EOF;// || io_stream_.eof();
    }

    void swap(TapeImpl& tmp){
        std::swap(io_stream_, tmp.io_stream_);
        std::swap(position_, tmp.position_);
    }
    void rewind() {
        //std::this_thread::sleep_for(Config::getInstanceConfig().getDelayRewind());
    
        io_stream_.seekg(0, std::ios::beg);
        this->position_ = 0;
    }
    ~TapeImpl() {
        io_stream_.close();
    }
private:
    int position_;
    std::fstream& io_stream_;
};