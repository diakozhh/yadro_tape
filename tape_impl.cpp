#include <iostream>
#include <chrono>
#include <thread>
#include <utility>

#include "tape_impl.h"
#include "config_parser.hpp"

TapeImpl::TapeImpl(std::fstream& io_stream) 
    : position_(0)
    , io_stream_(io_stream)
{
    io_stream_.seekg(std::ios::beg);
}

void TapeImpl::moveLeft() {
    if(this->position_ == std::ios::beg)
        throw std::out_of_range("Out of tape's bound(on begin)");

    std::this_thread::sleep_for(Config::getInstanceConfig().getDelayMove());
    --position_;
    io_stream_.seekp(position_*sizeof(int32_t), std::ios::beg);

}

void TapeImpl::moveRight() {
    std::this_thread::sleep_for(Config::getInstanceConfig().getDelayMove());
    ++position_;
    io_stream_.seekp(position_*sizeof(int32_t), std::ios::beg);
}

int32_t TapeImpl::readElement() {
    std::this_thread::sleep_for(Config::getInstanceConfig().getDelayRead());

    int32_t return_elem;
    io_stream_.seekg(position_*sizeof(int32_t), std::ios::beg);
    io_stream_.read((char*)&return_elem, sizeof(int32_t));
    io_stream_.seekg(position_*sizeof(int32_t), std::ios::beg);

    return return_elem;
}

void TapeImpl::writeElement(int32_t elem) {
    std::this_thread::sleep_for(Config::getInstanceConfig().getDelayWrite());
    io_stream_.seekp(position_*sizeof(int32_t), std::ios::beg);
    io_stream_.write((const char*)&elem, sizeof(int32_t));
    io_stream_.seekp(position_*sizeof(int32_t), std::ios::beg);
}

void TapeImpl::swap(TapeImpl& tmp){
    std::swap(io_stream_, tmp.io_stream_);
    std::swap(position_, tmp.position_);
}

void TapeImpl::rewind() {
    std::this_thread::sleep_for(Config::getInstanceConfig().getDelayRewind());
    io_stream_.seekg(0, std::ios::beg);
    this->position_ = 0;
}
