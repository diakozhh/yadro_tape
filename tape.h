#pragma once

// possible make with templates
class Tape {
public:
    // methods with delay 
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual int readElement() = 0;
    virtual void writeElement(int elem) = 0;
    virtual int getPosition() = 0;
    virtual bool isEnd() = 0;
    virtual void rewind() = 0;
    //virtual void moveToStart() = 0;
    virtual ~Tape() = default;
};