#pragma once

class Tape {
public:
    /**
     * @brief Shifting the tape to left by one position
     * 
     */
    virtual void moveLeft() = 0;
    
    /**
     * @brief Shifting the tape to right by one position
     * 
     */
    virtual void moveRight() = 0;
    
    /**
     * @brief Reading an element at current position
     * 
     * @return int32_t The element after reading
     */
    virtual int32_t readElement() = 0;
    
    /**
     * @brief Writing an element to current position
     * 
     * @param elem 
     */
    virtual void writeElement(int32_t elem) = 0;
    
    /**
     * @brief Getting current position
     * 
     * @return size_t 
     */
    
    virtual size_t getPosition() = 0;
    
    /**
     * @brief Checking end of the tape
     * 
     * @return true End of tape
     * @return false Not end of tape
     */
    virtual bool isEnd() = 0;
    
    /**
     * @brief Rewinding the tape to beginning
     * 
     */
    virtual void rewind() = 0;
    
    virtual ~Tape() = default;
};