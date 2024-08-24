#pragma once

class Tape {
public:
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual int32_t readElement() = 0;
    virtual void writeElement(int32_t elem) = 0;
    virtual size_t getPosition() = 0;
    virtual bool isEnd() = 0;
    virtual void rewind() = 0;
    virtual ~Tape() = default;
};