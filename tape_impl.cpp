#include <iostream>
#include <chrono>
#include <thread>

#include "tape_impl.h"
#include "config_parser.h"

// TODO delays from config

TapeImpl::TapeImpl(std::fstream& io_stream) 
    : position_(0)
    , io_stream_(io_stream)
{
    io_stream_.seekg(std::ios::beg);
}


// 
void TapeImpl::moveLeft() {
    if(this->position_ == std::ios::beg)
        throw std::out_of_range("Out of tape's bound(on begin)");

    std::this_thread::sleep_for(Config::getInstanceConfig().getDelayMove());

    --position_;// -= sizeof(int32_t);
    io_stream_.seekp(position_*sizeof(int32_t), std::ios::beg);

}

void TapeImpl::moveRight() {
    //if(io_stream_.tellg() == io_stream_.end)
    //    throw std::out_of_range("Out of tape's bound(on end)");
    std::this_thread::sleep_for(Config::getInstanceConfig().getDelayMove());

    ++position_;// += sizeof(int32_t);
    io_stream_.seekp(position_*sizeof(int32_t), std::ios::beg);
}

int TapeImpl::readElement() {
    std::this_thread::sleep_for(Config::getInstanceConfig().getDelayRead());

    int return_elem;
    std::cout << "Before read: tellg()=" << io_stream_.tellg() << ", tellp()=" << io_stream_.tellp() << "\n";
    io_stream_.seekg(position_*sizeof(int32_t), std::ios::beg);
    io_stream_.read((char*)&return_elem, sizeof(int32_t));
    io_stream_.seekg(position_*sizeof(int32_t), std::ios::beg);
    std::cout << "after read'" << return_elem <<"': tellg()=" << io_stream_.tellg() << ", tellp()=" << io_stream_.tellp() << "\n";

    return return_elem;
}

void TapeImpl::writeElement(int elem) {
    std::this_thread::sleep_for(Config::getInstanceConfig().getDelayWrite());
    
    std::cout << "Before write: tellg()=" << io_stream_.tellg() << ", tellp()=" << io_stream_.tellp() << "\n";
    io_stream_.seekp(position_*sizeof(int32_t), std::ios::beg);
    io_stream_.write((const char*)&elem, sizeof(int32_t));
    io_stream_.seekp(position_*sizeof(int32_t), std::ios::beg);
    std::cout << "after write'" << elem <<"': tellg()=" << io_stream_.tellg() << ", tellp()=" << io_stream_.tellp() << "\n";
}
