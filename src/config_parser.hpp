#pragma once
#include <iostream>
#include <chrono>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

class Config {
private:
    Config()
    : delay_read(0)
    , delay_write(0)
    , delay_move(0)
    , delay_rewind(0)
    {}
public:
    inline std::chrono::milliseconds getDelayRead(){
        return std::chrono::milliseconds(this->delay_read);
    }
    
    inline std::chrono::milliseconds getDelayWrite(){
        return std::chrono::milliseconds(this->delay_write);
    }
    
    inline std::chrono::milliseconds getDelayMove(){
        return std::chrono::milliseconds(this->delay_move);
    }
    inline std::chrono::milliseconds getDelayRewind(){
        return std::chrono::milliseconds(this->delay_rewind);
    }
    static Config& getInstanceConfig(){
        static Config config;
        return config;
    }
    void readConfig(const std::string& config_path){
        try {
            boost::property_tree::ptree pt;
	        boost::property_tree::ini_parser::read_ini(config_path, pt);
	        delay_read = pt.get<int>("delays.delay_read");
	        delay_write = pt.get<int>("delays.delay_write");
	        delay_move = pt.get<int>("delays.delay_move");
            delay_rewind = pt.get<int>("delays.delay_rewind");
        }
        catch(const boost::property_tree::ini_parser_error& e) { 
            std::cerr << e.what() << std::endl;
            throw;
        }
    }

private:
    int delay_read;
    int delay_write;
    int delay_move;
    int delay_rewind;
};