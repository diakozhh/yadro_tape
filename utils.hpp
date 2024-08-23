#pragma once 

#include <fstream>
#include <iostream>
#include <utility>

namespace utils{
    void convertTextIntoBinary(const std::string& input_filename, const std::string &tmp_filename) {
        try{
            std::ifstream input(input_filename);
    		std::ofstream out(tmp_filename, std::ios::binary);
            int32_t x;
    		while (!input.eof()) {
                int32_t x;
                input >> x;
    			out.write((char*)&x, sizeof(x));
    		}
            input.close();
    		out.close();
        }
        catch(...){
            throw;
        }
    }

    void convertBinaryIntoText(const std::string& input_filename, const std::string &tmp_filename) {
        std::ifstream input(input_filename, std::ios::binary);
		std::ofstream out(tmp_filename);
		int32_t x;
		while(input.read((char*)&x, sizeof(x))){

			out << x << " ";
		}
		input.close();
		out.close();
    }
    void createBinaryFile(const std::string& input_filename) {
        std::ofstream out(input_filename);
        out.close();
    }
}