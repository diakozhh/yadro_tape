#pragma once

#include <utility>
#include <fstream>
#include "tape.h"

class TapeImpl : public Tape {
public:
    TapeImpl(std::fstream& io_stream);
    void moveLeft() override;
    void moveRight() override;
    int32_t readElement() override;
    void writeElement(int32_t elem) override;
    inline int getPosition() override {
        return this->position_;
    }
    
    inline bool isEnd() override {
        return io_stream_.peek() == EOF;
    }

    void swap(TapeImpl& tmp);
    
    void rewind() override;

    ~TapeImpl() {
        io_stream_.close();
    }
private:
    int position_;
    std::fstream& io_stream_;
};